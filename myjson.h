#ifndef MYJSON_H
#define MYJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "entity/Object.h"
#include "entity/Integer.h"
#include "entity/Double.h"
#include "entity/Boolean.h"
#include "entity/String.h"
#include "entity/Null.h"
#include "entity/Pair.h"
#include "entity/Dict.h"
#include "entity/Array.h"

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

#endif // MYJSON_H