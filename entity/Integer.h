#ifndef ENTITY_INTEGER_H
#define ENTITY_INTEGER_H

#include "entity/Object.h"

/* Integer类 继承 Object类 */
typedef struct
{
    Object super; /* type I */
    long value;
} Integer;



Object *new_int(int d);

#endif // ENTITY_INTEGER_H