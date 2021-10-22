#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

extern void yyerror(char *s, ...);

struct ObjectVtbl;

/* 基础类Object */
typedef struct
{
    struct ObjectVtbl const *vptr;
    int objtype;
} Object;

// Object的虚表
struct ObjectVtbl
{
    void (*dump)(Object const *const self);
};

void Object_ctor(Object *self, int objtype);
static inline void Object_dump(Object const *const self)
{
    (*self->vptr->dump)(self);
}

void dump(Object *obj);


#endif // ENTITY_OBJECT_H