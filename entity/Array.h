#ifndef ENTITY_ARRAY_H
#define ENTITY_ARRAY_H

#include "Object.h"

typedef struct
{
    Object super; /* type A */
    Object **list;
    int capacity;
    int size;
} Array;

// 构造函数
void Array_ctor(Array * const self, int objtype, Object *elem);

Object *new_array(Object *elem);
Object *add_element(Array *self, Object *elem);


#endif // ENTITY_ARRAY_H