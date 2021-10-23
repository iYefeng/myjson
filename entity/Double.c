#include "Double.h"

/* Double 实现 */
// dump虚函数实现
static void Double_dump_(Object const *const self)
{
    printf("DOUBLE(%lf)", ((Double *)self)->value);
}

// free虚函数实现
static void Double_free_(Object const *const self)
{
    if (NULL != self)
    {
        free((Double *)self);
    }
}

// 构造函数
void Double_ctor(Double *const self, int objtype, double value)
{
    static struct ObjectVtbl const vtbl =
        {
            &Double_dump_,
            &Double_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->value = value;
}

Object *new_double(double d)
{
    Double *a = malloc(sizeof(Double));
    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Double_ctor(a, 'F', d);
    return (Object *)a;
}