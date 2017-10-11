%option noyywrap

%{
#include <iostream>
#include <assert.h>
#include <string.h>
#include <map>
#include "hvac.hpp"
#include "hvac.tab.hpp"

#define DEBUG_LEXER 1
%}

%%
[0-9]+ {
  yylval = node(atoi(yytext));
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as NUMBER: " << yylval << std::endl;
#endif
  return NUMBER;
}

(start|stop) {
  if (strcmp(yytext, "start") == 0) {
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as START" << std::endl;
#endif
    return START;
  }
  if (strcmp(yytext, "stop") == 0) {
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as STOP" << std::endl;
#endif
    return STOP;
  }
  assert(0);
}

[a-zA-Z][a-zA-Z0-9]*    {
  yylval = node(std::string(yytext));
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as WORD:" << yylval << std::endl;
#endif
  return WORD;
}

[ \t]+ {
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as WS" << std::endl;
#endif
  return WS;
}

\r?\n {
#if DEBUG_LEXER == 1
  std::cout << "lexed " << yytext << " as EOL" << std::endl;
#endif
  return EOL;
}

. {
  std::cout << "syntax error '" << yytext << "'" << std::endl;
  assert(0);
}

%%
