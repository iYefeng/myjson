#include "Integer.h"
#include "String.h"

/* Integer 实现 */

// dump虚函数实现
static int Integer_dumps_(Object const *const self, struct StringType *pstr)
{
    int res = String_ensure_capacity(pstr, 20);
    int length = sprintf(&(pstr->value[pstr->size]), "%ld", ((Integer *)self)->value);
    pstr->size += length;
    return res;
}

// debug虚函数实现
static void Integer_debug_(Object const *const self)
{
    printf("INT(%ld)", ((Integer *)self)->value);
}

// free虚函数实现
static void Integer_free_(Object *self)
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
            &Integer_dumps_,
            &Integer_debug_,
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
