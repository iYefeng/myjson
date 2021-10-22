#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>

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
    void (*free)(Object const *const self);
};

// 构造函数
void Object_ctor(Object *const self, int objtype);

static inline void Object_dump(Object const *const self)
{
    (*self->vptr->dump)(self);
}

static inline void Object_free(Object const *const self)
{
    (*self->vptr->free)(self);
}



#endif // ENTITY_OBJECT_H