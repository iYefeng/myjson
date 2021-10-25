#include "Array.h"

// dump虚函数实现
static int Array_dumps_(Object const *const self, struct StringType *pstr)
{
    int i;
    int res;
    Array *this = (Array *)self;

    int extralen = (this->size - 1) * 2 + 2;
    res = String_ensure_capacity(pstr, extralen);
    if (res != 0)
    {
        return res;
    }

    res = String_append(pstr, "[");
    if (res != 0)
    {
        return res;
    }
    for (i = 0; i < this->size; ++i)
    {
        res = Object_dumps((Object *)this->list[i], pstr);
        if (res != 0)
        {
            return res;
        }
        if (i < this->size - 1)
        {
            res = String_append(pstr, ", ");
            if (res != 0)
            {
                return res;
            }
        }
    }
    res = String_append(pstr, "]");
    if (res != 0)
    {
        return res;
    }
    return res;
}

// debug虚函数实现
static void Array_debug_(Object const *const self)
{
    int i;
    Array *this = (Array *)self;
    printf("ARRAY[");
    for (i = 0; i < this->size; ++i)
    {
        Object_debug((Object *)this->list[i]);
        if (i < this->size - 1)
        {
            printf(",");
        }
    }
    printf("]");
}

// free虚函数实现
static void Array_free_(Object const *const self)
{
    int i;
    if (NULL != self)
    {
        Array *this = (Array *)self;
        for (i = 0; i < this->size; ++i)
        {
            if (NULL != this->list[i])
            {
                Object_free(this->list[i]);
            }
        }
        free(this->list);
        free(this);
    }
}

void Array_ctor(Array *const self, int objtype, Object *elem)
{
    static struct ObjectVtbl const vtbl = {
        &Array_dumps_,
        &Array_debug_,
        &Array_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->capacity = 10;
    self->list = (Object **) malloc(sizeof(Object *) * self->capacity);
    if (!self->list)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    self->size = 0;
    if (NULL != elem)
    {
        self->list[self->size] = elem;
        ++(self->size);
    }
}

Object *new_array(Object *elem)
{
    Array *arr = malloc(sizeof(Array));
    if (!arr)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Array_ctor(arr, 'A', elem);
    return (Object *)arr;
}

Object *add_element(Array *self, Object *elem)
{
    if (self->capacity == self->size)
    {
        self->capacity *= 2;
        self->list = (Object **) realloc(self->list, sizeof(Object *) * self->capacity);
        if (!self->list)
        {
            yyerror(NULL, "out of space");
            exit(0);
        }
    }
    self->list[self->size] = elem;
    ++(self->size);
    return (Object *)self;
}