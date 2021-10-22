/* 
 * json语法解析规则
 * 
 * author：fengye
 * date: 2021-10-21
 * email: fengye@sse.com.cn
 */

%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "myjson.h"
%}

%union {
  Object *obj;
  long intval;
  double floatval;
  char *strval;
}

/* declare tokens */
%token <intval> INTNUM
%token <floatval> APPROXNUM
%token <intval> BOOL
%token <strval> STRING
%token NUL

%token START_OBJECT
%token END_OBJECT
%token START_ARRAY
%token END_ARRAY
%token COMMA
%token COLON

%type <obj> json pairs pair elements element dict array 

%start json

%%
json: element                          { dump($1); }
;

element: dict                          { $$ = $1;               }
    | array                            { $$ = $1;               }
    | STRING                           { $$ = new_string($1);   }
    | APPROXNUM                        { $$ = new_double($1);   }
    | INTNUM                           { $$ = new_int($1);      }
    | BOOL                             { $$ = new_boolean($1);  }
    | NUL                              { $$ = new_null();       }
;

dict: START_OBJECT END_OBJECT        { $$ = new_dict(NULL);     }
    | START_OBJECT pairs END_OBJECT  { $$ = $2;                 }
;

pairs: pair                        { $$ = new_dict((Pair *)$1);          }
    | pairs COMMA pair             { $$ = add_pair((Dict *)$1, (Pair *)$3);      }
;

pair: STRING COLON element           { $$ = new_pair($1, $3);      }
;

array: START_ARRAY END_ARRAY           { $$ = new_array(NULL);         }
    | START_ARRAY elements END_ARRAY   { $$ = $2;                      }
;

elements: element                      { $$ = new_array($1);           }
    | elements COMMA element           { $$ = add_element((Array *)$1, $3);     }
;


%%
