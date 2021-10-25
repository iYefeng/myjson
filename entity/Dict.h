#ifndef ENTITY_DICT_H
#define ENTITY_DICT_H

#include "Object.h"
#include "Pair.h"

typedef struct
{
    Object super; /* type D */
    Pair *hash_table;
    int size;
} Dict;

// 构造函数
void Dict_ctor(Dict * const self, int objtype, Pair *pair);

Object *new_dict(Pair *pair);
Object *add_pair(Dict *self, Pair *pair);

#endif // ENTITY_DICT_H