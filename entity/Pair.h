#ifndef ENTITY_PAIR_H
#define ENTITY_PAIR_H

#include "Object.h"
#include "uthash.h"

typedef struct
{
    Object super; /* type P */
    char *key;
    Object *value;
    UT_hash_handle hh;         /* makes this structure hashable */
} Pair;

void Pair_ctor(Pair *const self, int objtype, char *key, Object *value);

Object *new_pair(char *key, Object *value);

#endif // ENTITY_PAIR_H