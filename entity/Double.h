#ifndef ENTITY_DOUBLE_H
#define ENTITY_DOUBLE_H

#include "Object.h"

typedef struct
{
    Object super; /* type F */
    double value;
} Double;

// 构造函数
void Double_ctor(Double *const self, int objtype, double value);

Object *new_double(double d);


#endif // ENTITY_DOUBLE_H