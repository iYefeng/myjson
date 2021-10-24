#ifndef ENTITY_STRING_H
#define ENTITY_STRING_H

#include "Object.h"

typedef struct StringType
{
    Object super; /* type S */
    int capacity;
    int size;
    char *value;
} String;

// 构造函数
void String_ctor(String *const self, int objtype, char *value);
// 构造函数，创建有预留内存的空String
void String_ctor_empty(String *const self, int objtype, int capacity);

// 确保String存在足够内存
int String_ensure_capacity(String *const self, int extralen);

// 添加字符串到String
int String_append(String *const self, char *str);

Object *new_string(char *d);
Object *new_string_empty(int capacity);

#endif // ENTITY_STRING_H