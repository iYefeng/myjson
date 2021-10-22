#include "Pair.h"

// dump虚函数实现
static void Pair_dump_(Object const *const self)
{
    Pair *this = (Pair *)self;
    printf("PAIR(");
    printf("KEY=%s, ", this->key);
    printf("VALUE=");
    Object_dump(this->value);
    printf(")");
}

// free虚函数实现
static void Pair_free_(Object const *const self)
{
    if (NULL != self)
    {
        Pair *this = (Pair *)self;
        if (NULL == this->key) {
            free(this->key);
        }
        Object_free(this->value);
        free(this);
    }
}

void Pair_ctor(Pair *const self, int objtype, char *key, Object *value)
{
    static struct ObjectVtbl const vtbl = {
        &Pair_dump_,
        &Pair_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->key = key;
    self->value = value;
}

Object *new_pair(char *key, Object *value)
{
    Pair *a = malloc(sizeof(Pair));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    Pair_ctor(a, 'P', key, value);
    return (Object *)a;
}