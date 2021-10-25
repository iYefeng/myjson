#include "Boolean.h"

// dump虚函数实现
static int Boolean_dumps_(Object const *const self, struct StringType *pstr)
{
    Boolean *this = (Boolean *)self;
    int res;
    switch (this->value)
    {
    case 1:
        res = String_append(pstr, "true");
        break;
    case 0:
        res = String_append(pstr, "false");
        break;
    default:
        res = String_append(pstr, "unknown");
        break;
    }
    return res;
}

// debug虚函数实现
static void Boolean_debug_(Object const *const self)
{
    Boolean *this = (Boolean *)self;
    switch (this->value)
    {
    case 1:
        printf("BOOL(true)");
        break;
    case 0:
        printf("BOOL(false)");
        break;
    default:
        printf("BOOL(unknown)");
        break;
    }
}

// free虚函数实现
static void Boolean_free_(Object *self)
{
    if (NULL != self)
    {
        free((Boolean *)self);
    }
}

// 构造函数
void Boolean_ctor(Boolean *const self, int objtype, int value)
{
    // Integer 类的虚表
    static struct ObjectVtbl const vtbl =
        {
            &Boolean_dumps_,
            &Boolean_debug_,
            &Boolean_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->value = value;
}

Object *new_boolean(char d)
{
    Boolean *a = malloc(sizeof(Boolean));

    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Boolean_ctor(a, 'B', d);
    return (Object *)a;
}