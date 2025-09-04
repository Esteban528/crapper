#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <crapper_info.h>

int8_t strmatch(char* st1, char* st2){
  return strcmp(st1,st2) == 0;
}

void info_help(){
  printf("curl wrapper to api testing\n");
  putchar('\n');
  printf("usage: crapper [options...]\n");
  printf("-V,  --version \t\t\tShow the crapper version\n");
  printf("-h,  --help \t\t\tShow help\n");
}

void process_option(char* option) {
//printf("%s:\n", option);
  if(strmatch(option, "version")){
    printf("crapper %s", VERSION);
    printf(" (%s)", ARCHITECTURE);
    printf("\n");
  }else if(strmatch(option, "help")){
    info_help();
  } 
}

void process_shortcut(char* sc){
  uint8_t len = strlen(sc);
  for (uint8_t i = 0; i < len; i++){
    char c = (*sc);
    if (c == 'V')
      process_option("version");
    else if (c == 'h')
      process_option("help");
    else
      printf("crapper: option %s not found, try 'crapper --help'\n", sc);
    sc++;
  }
}

int main(int8_t argc, char* argv[]) {
  if (argc <= 1) {
    printf("crapper: try 'crapper --help'\n");
    exit(1);
  }

  for(int8_t i = 1; i < argc; i++){
    if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '\0')
      process_option(argv[i]+2);
    else if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != '\0')
      process_shortcut(argv[i]+1);
    else 
      printf("crapper: option %s not found, try 'crapper --help'\n", argv[i]);
  }

	return 0;
}

