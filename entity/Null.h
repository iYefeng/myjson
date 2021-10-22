#ifndef ENTITY_NULL_H
#define ENTITY_NULL_H

#include "Object.h"

typedef struct
{
    Object super; /* type N */
} Null;

void Null_ctor(Null *const self, int objtype);

Object *new_nil();

#endif // ENTITY_NULL_H