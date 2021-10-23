#include "Boolean.h"

// dump虚函数实现
static void Boolean_dump_(Object const *const self)
{
    Boolean *this = (Boolean *)self;
    switch (this->value)
    {
    case 1:
        printf("BOOL(True)");
        break;
    case 0:
        printf("BOOL(False)");
        break;
    default:
        printf("BOOL(UNKNOWN)");
        break;
    }
}

// free虚函数实现
static void Boolean_free_(Object const *const self)
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
            &Boolean_dump_,
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