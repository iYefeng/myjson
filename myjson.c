#include "myjson.h"


Object *new_double(double d)
{
    Double *a = malloc(sizeof(Double));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'F';
    a->value = d;
    return (Object *)a;
}


Object *new_boolean(int d)
{
    Boolean *a = malloc(sizeof(Boolean));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'B';
    a->value = d;
    return (Object *)a;
}

Object *new_string(char *d)
{
    String *a = malloc(sizeof(String));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'S';
    a->value = d;
    return (Object *)a;
}

Object *new_null()
{
    Null *a = malloc(sizeof(Null));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'N';
    return (Object *)a;
}

Object *new_pair(char *key, Object *value)
{
    Pair *a = malloc(sizeof(Pair));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'P';
    // printf("String: %s\n", str);
    a->key = key;
    a->value = value;
    return (Object *)a;
}

Object *new_dict(Pair *pair)
{
    Dict *a = malloc(sizeof(Dict));
    a->list = malloc(sizeof(Object) * 100);
    a->capacity = 100;
    a->size = 0;

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }

    if (pair == NULL)
    {
        return (Object *)a;
    }

    a->super.objtype = 'D';
    a->list[a->size] = pair;
    --(a->capacity);
    ++(a->size);
    return (Object *)a;
}

Object *new_array(Object *obj)
{
    Array *a = malloc(sizeof(Array));
    a->list = malloc(sizeof(Object) * 100);
    a->capacity = 100;
    a->size = 0;

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    if (obj == NULL)
    {
        return (Object *)a;
    }

    a->super.objtype = 'A';
    a->list[a->size] = obj;
    --(a->capacity);
    ++(a->size);
    return (Object *)a;
}

Object *add_pair(Dict *self, Pair *pair)
{
    self->list[self->size] = pair;
    ++(self->size);
    --(self->capacity);
    return (Object *)self;
}

Object *add_element(Array *self, Object *elem)
{
    self->list[self->size] = elem;
    ++(self->size);
    --(self->capacity);
    return (Object *)self;
}

void dump(Object *obj)
{
    int i;

    if (!obj)
    {
        printf("NULL\n");
        return;
    }

    switch (obj->objtype)
    {
    case 'I':
        printf("INTEGER(%ld)", ((Integer *)obj)->value);
        break;
    case 'F':
        printf("DOUBLE(%f)", ((Double *)obj)->value);
        break;
    case 'B':
        printf("BOOL(%s)", ((Boolean *)obj)->value == 0 ? "False" : "True");
        break;
    case 'S':
        printf("STRING(%s)", ((String *)obj)->value);
        break;
    case 'N':
        printf("NULL");
        break;
    case 'P':
        printf("Pair(");
        printf("KEY=%s", ((Pair *)obj)->key);
        printf(", VALUE=");
        dump(((Pair *)obj)->value);
        printf(")\n");
        break;
    case 'D':
        printf("Dict: {");
        for (i = 0; i < ((Dict *)obj)->size; ++i)
        {
            dump((Object *)((Dict *)obj)->list[i]);
            printf(",");
        }
        printf("}\n");
        break;
    case 'A':
        printf("ARRAY: [");
        for (i = 0; i < ((Array *)obj)->size; ++i)
        {
            dump(((Array *)obj)->list[i]);
            printf(",");
        }
        printf("]\n");
        break;
    default:
        printf("bad objtype:[%c]", obj->objtype);
    }
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main()
{
    printf("> ");
    return yyparse();
}