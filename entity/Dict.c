#include "Dict.h"

#include "String.h"

// dump虚函数实现
static int Dict_dumps_(Object const *const self, struct StringType *pstr)
{
    int i;
    int res;
    Pair *current_pair, *tmp = NULL;
    Dict *this = (Dict *)self;

    int extralen = this->size * 2 + 2;
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

    current_pair = this->hash_table;
    if (NULL != current_pair)
    {
        Object_dumps((Object *)current_pair, pstr);
        if (res != 0)
        {
            return res;
        }
        for (current_pair = current_pair->hh.next; current_pair != NULL; current_pair = current_pair->hh.next)
        {
            res = String_append(pstr, ", ");
            if (res != 0)
            {
                return res;
            }
            Object_dumps((Object *)current_pair, pstr);
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
    Pair *current_pair = NULL;
    Pair *tmp = NULL;
    Dict *this = (Dict *)self;
    printf("DICT{");

    current_pair = this->hash_table;
    if (NULL != current_pair)
    {
        Object_debug((Object *)current_pair);
        for (current_pair = current_pair->hh.next; current_pair != NULL; current_pair = current_pair->hh.next)
        {
            printf(",");
            Object_debug((Object *)current_pair);
        }
    }

    printf("}");
}

// free虚函数实现
static void Dict_free_(Object *self)
{
    int i;
    Pair *current_pair, *tmp = NULL;

    if (NULL != self)
    {
        Dict *this = (Dict *)self;

        if (NULL != this->hash_table)
        {
            HASH_ITER(hh, this->hash_table, current_pair, tmp)
            {
                HASH_DEL(this->hash_table, current_pair); /* delete it (users advances to next) */
                Object_free((Object *)current_pair);
            }
        }

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
    self->hash_table = NULL;
    self->size = 0;

    if (NULL != pair)
    {
        HASH_ADD_KEYPTR(hh, self->hash_table, pair->key, strlen(pair->key), pair);
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
    Pair *s = NULL;

    if (NULL == pair)
    {
        return (Object *)self;
    }

    HASH_FIND_STR(self->hash_table, pair->key, s); /* id already in the hash? */
    if (s == NULL)
    {
        HASH_ADD_KEYPTR(hh, self->hash_table, pair->key, strlen(pair->key), pair);
        ++(self->size);
    } else {
        Object *tmp = s->value;
        s->value = pair->value;
        pair->value = tmp;
        Object_free((Object *)pair);
    }
    return (Object *)self;
}
