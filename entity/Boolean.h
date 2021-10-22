#ifndef ENTITY_BOOLEAN_H
#define ENTITY_BOOLEAN_H

#include "Object.h"

typedef struct
{
    Object super; /* type B */
    char value;
} Boolean;

// 构造函数
void Boolean_ctor(Boolean *const self, int objtype, int value);

Object *new_boolean(char d);


#endif // ENTITY_BOOLEAN_H