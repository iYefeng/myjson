#include "Dict.h"

#include "String.h"

// dump虚函数实现
static int Dict_dumps_(Object const *const self, struct StringType *pstr)
{
    int i;
    int res;
    Dict *this = (Dict *)self;

    int extralen = (this->size - 1) * 2 + 2;
    res = String_ensure_capacity(pstr, extralen);
    if (res != 0)
    {
        return res;
    }

    res = String_append(pstr, "{");
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

    res = String_append(pstr, "}");
    if (res != 0)
    {
        return res;
    }

    return res;
}

// debug虚函数实现
static void Dict_debug_(Object const *const self)
{
    int i;
    Dict *this = (Dict *)self;
    printf("DICT{");
    for (i = 0; i < this->size; ++i)
    {
        Object_debug((Object *)this->list[i]);
        if (i < this->size - 1)
        {
            printf(",");
        }
    }
    printf("}");
}

// free虚函数实现
static void Dict_free_(Object const *const self)
{
    int i;
    if (NULL != self)
    {
        Dict *this = (Dict *)self;
        for (i = 0; i < this->size; ++i)
        {
            if (NULL != this->list[i]) {
                Object_free((Object *)this->list[i]);
            }
        }
        free(this->list);
        free(this);
    }
}

// 构造函数
void Dict_ctor(Dict *const self, int objtype, Pair *pair)
{
    static struct ObjectVtbl const vtbl =
        {
            &Dict_dumps_,
            &Dict_debug_,
            &Dict_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;
    self->capacity = 10;
    self->list = malloc(sizeof(Object) * self->capacity);
    if (!self->list)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    self->size = 0;
    if (NULL != pair)
    {
        self->list[self->size] = pair;
        ++(self->size);
    }
}

Object *new_dict(Pair *pair)
{
    Dict *dict = malloc(sizeof(Dict));
    if (!dict)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    Dict_ctor(dict, 'D', pair);
    return (Object *)dict;
}

Object *add_pair(Dict *self, Pair *pair)
{
    if (self->capacity == self->size)
    {
        self->capacity *= 2;
        self->list = realloc(self->list, self->capacity);
        if (!self->list)
        {
            yyerror(NULL, "out of space");
            exit(0);
        }
    }
    self->list[self->size] = pair;
    ++(self->size);
    return (Object *)self;
}
