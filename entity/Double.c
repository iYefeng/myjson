#include "Double.h"
#include "String.h"

/* Double 实现 */

// dump虚函数实现
static int Double_dumps_(Object const *const self, struct StringType *pstr)
{
    int res = String_ensure_capacity(pstr, 128);
    int length = sprintf(&(pstr->value[pstr->size]), "%lf", ((Double *)self)->value);
    pstr->size += length;
    return res;
}

// debug虚函数实现
static void Double_debug_(Object const *const self)
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
            &Double_dumps_,
            &Double_debug_,
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