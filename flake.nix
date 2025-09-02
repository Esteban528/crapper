{
  description = "Minimal flake for developing and packaging in C";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forEachSupportedSystem = f:
        nixpkgs.lib.genAttrs supportedSystems
          (system: f {
            pkgs = import nixpkgs { inherit system; };
            inherit system;
          });
    in
    {
      # Development environment (nix develop)
      devShells = forEachSupportedSystem ({ pkgs, system }: {
        default = pkgs.mkShell {
          packages = with pkgs; [
            gcc14
            gnumake
            curl
            cmake
          ] ++ (if system == "aarch64-darwin" then [] else [ gdb ]);
        };
      });

      # Buildable package (nix build)
      packages = forEachSupportedSystem ({ pkgs, system }: {
        default = pkgs.stdenv.mkDerivation {
          pname = "crapper";
          version = "0.0.1";
          src = ./.;

          nativeBuildInputs = [ pkgs.cmake pkgs.gnumake pkgs.curl ];
          buildInputs = [ pkgs.gcc14 ];

          installPhase = ''
            mkdir -p $out/bin
            cp crapper $out/bin/
          '';
        };
      });
    };
}
