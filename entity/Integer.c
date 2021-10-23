#include "Integer.h"

/* Integer 实现 */
// dump虚函数实现
static void Integer_dump_(Object const *const self)
{
    printf("INT(%ld)", ((Integer *)self)->value);
}

// free虚函数实现
static void Integer_free_(Object const *const self)
{
    if (NULL != self)
    {
        free((Integer *)self);
    }
}

void Integer_ctor(Integer *const self, int objtype, long value)
{
    // Integer 类的虚表
    static struct ObjectVtbl const vtbl =
        {
            &Integer_dump_,
            &Integer_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->value = value;
}

// new
Object *new_int(long d)
{
    Integer *a = malloc(sizeof(Integer));
    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Integer_ctor(a, 'I', d);
    return (Object *)a;
}
