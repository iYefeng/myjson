#ifndef ENTITY_STRING_H
#define ENTITY_STRING_H

#include "Object.h"

typedef struct
{
    Object super; /* type S */
    char *value;
} String;

// 构造函数
void String_ctor(String *const self, int objtype, char *value);

Object *new_string(char *d);

#endif // ENTITY_STRING_H