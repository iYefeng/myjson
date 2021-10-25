#include "String.h"

// dump虚函数实现
static int String_dumps_(Object const *const self, struct StringType *pstr)
{
    int res;
    // FIXME: \"转义处理
    int length = ((String *)self)->size + 2;
    res = String_ensure_capacity(pstr, length);
    length = sprintf(&(pstr->value[pstr->size]), "\"%s\"", ((String *)self)->value);
    pstr->size += length;
    return res;
}

// debug虚函数实现
static void String_debug_(Object const *const self)
{
    printf("STRING(%s)", ((String *)self)->value);
}

// free虚函数实现
static void String_free_(Object *self)
{
    if (NULL != self)
    {
        String *this = (String *)self;
        if (NULL == this->value)
        {
            free(this->value);
        }
        free(this);
    }
}

// 构造函数
void String_ctor(String *const self, int objtype, char *value)
{
    static struct ObjectVtbl const vtbl = {
        &String_dumps_,
        &String_debug_,
        &String_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;

    self->capacity = strlen(value) + 1;
    self->size = strlen(value);
    self->value = value;
}

void String_ctor_empty(String *const self, int objtype, int capacity)
{
    static struct ObjectVtbl const vtbl = {
        &String_dumps_,
        &String_debug_,
        &String_free_};
    Object_ctor(&self->super, objtype);
    self->super.vptr = &vtbl;

    self->capacity = capacity;
    self->size = 0;
    char *pstr = malloc(sizeof(char) * capacity);
    if (NULL == pstr)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    self->value = pstr;
    self->value[self->size] = '\0';
}

int String_ensure_capacity(String *const self, int extralen)
{
    if (extralen > (self->capacity - self->size - 1))
    {
        if (extralen > self->capacity)
        {
            self->capacity += extralen;
        }
        else
        {
            self->capacity *= 2;
        }
        self->value = realloc(self->value, sizeof(char) * self->capacity);
        if (NULL == self->value)
        {
            yyerror(NULL, "out of space");
            exit(0);
        }
    }
    return 0;
}

int String_append(String *const self, char *str)
{
    int length = strlen(str);
    if (length > (self->capacity - self->size - 1))
    {
        if (length > self->capacity)
        {
            self->capacity += length;
        }
        else
        {
            self->capacity *= 2;
        }
        self->value = realloc(self->value, sizeof(char) * self->capacity);
        if (NULL == self->value)
        {
            yyerror(NULL, "out of space");
            exit(0);
        }
    }
    strncpy(&(self->value[self->size]), str, length);
    self->size += length;
    self->value[self->size] = '\0';
    return 0;
}

Object *new_string(char *d)
{
    String *a = malloc(sizeof(String));
    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    String_ctor(a, 'S', d);
    return (Object *)a;
}

Object *new_string_empty(int capacity)
{
    String *a = malloc(sizeof(String));
    if (!a)
    {
        yyerror(NULL, "out of space");
        exit(0);
    }
    String_ctor_empty(a, 'S', capacity);
    return (Object *)a;
}