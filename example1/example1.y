%{
#include <stdio.h>
#include <string.h>
#include "example1.h"

  void yyerror(const char *str);
  int yywrap();
  int yylex();
%}

%token NUMBER START STOP WORD EOL

%%

commands :
     /* empty */
     |
     commands command
     ;

command :
     start_command
     |
     stop_command
     ;

start_command :
     START WORD NUMBER EOL
     ;

stop_command :
     STOP WORD EOL
     ;

%%

void yyerror(const char *str)
{
  fprintf(stderr,"error: %s\n",str);
}

int main(int argc, char *argv[])
{
  yyparse();
  return 0;
} 
