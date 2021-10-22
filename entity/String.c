#include "String.h"

// dump虚函数实现
static void String_dump_(Object const *const self)
{
    printf("STRING(%s)", ((String *)self)->value);
}

// free虚函数实现
static void String_free_(Object const *const self)
{
    if (NULL != self)
    {
        String *this = (String *)self;
        if (NULL == this->value) {
            free(this->value);
        }
        free(this);
    }
}

// 构造函数
void String_ctor(String *const self, int objtype, char *value)
{
    static struct ObjectVtbl const vtbl = {
        &String_dump_,
        &String_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->value = value;
}

Object *new_string(char *d)
{
    String *a = malloc(sizeof(String));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    String_ctor(a, 'S', d);
    return (Object *)a;
}