#ifndef MYJSON_H
#define MYJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "entity/Object.h"
#include "entity/Integer.h"


typedef struct
{
    Object super; /* type F */
    double value;
} Double;

Object *new_double(double d);

typedef struct
{
    Object super; /* type B */
    char value;
} Boolean;

Object *new_boolean(int d);

typedef struct
{
    Object super; /* type S */
    char *value;
} String;

Object *new_string(char *d);

typedef struct
{
    Object super; /* type N */
} Null;

Object *new_null();

typedef struct
{
    Object super; /* type P */
    char *key;
    Object *value;
} Pair;

Object *new_pair(char *key, Object *value);

typedef struct
{
    Object super; /* type D */
    Pair **list;
    int capacity;
    int size;
} Dict;

Object *new_dict(Pair *pair);
Object *add_pair(Dict *self, Pair *pair);

typedef struct
{
    Object super; /* type A */
    Object **list;
    int capacity;
    int size;
} Array;

Object *new_array(Object *node);
Object *add_element(Array *self, Object *elem);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

#endif // MYJSON_H