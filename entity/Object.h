#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>

struct json_state;
extern void yyerror(struct json_state *pstate, char *s, ...);

struct StringType;
// 确保String存在足够内存
extern int String_ensure_capacity(struct StringType *const self, int extralen);
// 添加字符串到String
extern int String_append(struct StringType *const self, char *str);

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
    int (*dumps)(Object const *const self, struct StringType *pstr);
    void (*debug)(Object const *const self);
    void (*free)(Object const *const self);
};

// 构造函数
void Object_ctor(Object *const self, int objtype);

static inline int Object_dumps(Object const *const self, struct StringType *pstr)
{
    return (*self->vptr->dumps)(self, pstr);
}

static inline void Object_debug(Object const *const self)
{
    (*self->vptr->debug)(self);
}

static inline void Object_free(Object const *const self)
{
    (*self->vptr->free)(self);
}



#endif // ENTITY_OBJECT_H