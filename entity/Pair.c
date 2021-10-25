#include "Pair.h"

#include "String.h"

// dump虚函数实现
static int Pair_dumps_(Object const *const self, struct StringType *pstr)
{
    int res;
    Pair *this = (Pair *)self;

    int length = strlen(this->key) + 4;
    res = String_ensure_capacity(pstr, length);
    if (res != 0) {
        return res;
    }
    length = sprintf(&(pstr->value[pstr->size]), "\"%s\": ", this->key);
    pstr->size += length;
    
    res = Object_dumps(this->value, pstr);
    return res;
}


// debug虚函数实现
static void Pair_debug_(Object const *const self)
{
    Pair *this = (Pair *)self;
    printf("PAIR(");
    printf("KEY=%s, ", this->key);
    printf("VALUE=");
    Object_debug(this->value);
    printf(")");
}

// free虚函数实现
static void Pair_free_(Object * self)
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
        &Pair_dumps_,
        &Pair_debug_,
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
        yyerror(NULL, "out of space");
        exit(0);
    }
    Pair_ctor(a, 'P', key, value);
    return (Object *)a;
}