#include "Null.h"

// dump虚函数实现
static int Null_dumps_(Object const *const self, struct StringType *pstr)
{
    return String_append(pstr, "null");
}

// debug虚函数实现
static void Null_debug_(Object const *const self)
{
    printf("null");
}

// free虚函数实现
static void Null_free_(Object *self)
{
    if (NULL != self)
    {
        free((Null *)self);
    }
}

void Null_ctor(Null *const self, int objtype)
{
    static struct ObjectVtbl const vtbl = {
        &Null_dumps_,
        &Null_debug_,
        &Null_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
}

Object *new_nil()
{
    Null *a = malloc(sizeof(Null));
    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Null_ctor(a, 'N');
    return (Object *)a;
}