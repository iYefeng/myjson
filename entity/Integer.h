#ifndef ENTITY_INTEGER_H
#define ENTITY_INTEGER_H

#include "Object.h"

/* Integer类 继承 Object类 */
typedef struct
{
    Object super; /* type I */
    long value;
} Integer;

// 构造函数
void Integer_ctor(Integer *const self, int objtype, long value);

Object *new_int(long d);

#endif // ENTITY_INTEGER_H