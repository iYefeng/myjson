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

struct json_state
{
    Object *obj;
};

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(struct json_state *pstate, char *s, ...);

void emit(struct json_state *pstate, Object *self);

// 读取文件，反序列化JSON
int load(FILE *fp, Object **obj);
// 反序列化json字符串
int loads(char const *const str, Object **obj);
// json序列化
int dumps(Object const *const obj, String *pstr);

#endif // MYJSON_H