/* 
 * json词法解析规则
 * 
 * author：fengye
 * date: 2021-10-21
 * email: fengye@sse.com.cn
 */

%option noyywrap nodefault yylineno case-insensitive

%{
# include "myjson.h"
# include "json.tab.h"
%}


%%

":"  {  return COLON; }
","  {  return COMMA; }
"["  {  return START_ARRAY;  }
"]"  {  return END_ARRAY;    }
"{"  {  return START_OBJECT; }
"}"  {  return END_OBJECT;   }

    /* number */
-?[0-9]+	            { yylval.intval = atol(yytext); return INTNUM; } 

-?[0-9]+"."[0-9]* |
-?"."[0-9]+	|
-?[0-9]+[Ee][-+]?[0-9]+	|
-?[0-9]+"."[0-9]*[Ee][-+]?[0-9]+ |
-?"."[0-9]*[Ee][-+]?[0-9]+	{ yylval.floatval = atof(yytext) ;
                                  return APPROXNUM; }

    /* booleans */
TRUE 	{ yylval.intval = 1; return BOOL; }
UNKNOWN	{ yylval.intval = -1; return BOOL; }
FALSE	{ yylval.intval = 0; return BOOL; }

null    { return NUL;  }

   /* strings */
\"(\\.|\"\"|[^"\n])*\"  { yylval.strval = strdup(yytext+1); yylval.strval[yyleng-2] = 0; return STRING; }
'(\\.|''|[^'\n])*'  { yylval.strval = strdup(yytext+1); yylval.strval[yyleng-2] = 0; return STRING; }

[A-Za-z0-9_]*	{ yylval.strval = strdup(yytext); return NAME; }

[ \t\n]         /* white space */

.	{ yyerror(NULL, "Mystery character %c\n", *yytext); }

%%
