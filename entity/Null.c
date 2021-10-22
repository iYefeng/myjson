#include "Null.h"

// dump虚函数实现
static void Null_dump_(Object const *const self)
{
    printf("NULL");
}

// free虚函数实现
static void Null_free_(Object const *const self)
{
    if (NULL != self)
    {
        free((Null *)self);
    }
}

void Null_ctor(Null *const self, int objtype)
{
    static struct ObjectVtbl const vtbl = {
        &Null_dump_,
        &Null_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
}

Object *new_nil()
{
    Null *a = malloc(sizeof(Null));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    Null_ctor(a, 'N');
    return (Object *)a;
}