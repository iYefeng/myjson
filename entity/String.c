#include "String.h"

const char String_hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static char *String_parse_hex4_(char *p, unsigned int *u)
{
    int i;
    *u = 0;
    for (i = 0; i < 4; i++)
    {
        char ch = *(++p);
        if (ch == '\0')
            return NULL;

        *u <<= 4;
        if (ch >= '0' && ch <= '9')
            *u |= ch - '0';
        else if (ch >= 'A' && ch <= 'F')
            *u |= ch - ('A' - 10);
        else if (ch >= 'a' && ch <= 'f')
            *u |= ch - ('a' - 10);
        else
            return NULL;
    }
    return p;
}

static char *String_encode_utf8_(char *c, unsigned int u)
{
    if (u <= 0x7F)
        *c++ = u & 0xFF;
    else if (u <= 0x7FF)
    {
        *c++ = 0xC0 | ((u >> 6) & 0xFF);
        *c++ = 0x80 | (u & 0x3F);
    }
    else if (u <= 0xFFFF)
    {
        *c++ = 0xE0 | ((u >> 12) & 0xFF);
        *c++ = 0x80 | ((u >> 6) & 0x3F);
        *c++ = 0x80 | (u & 0x3F);
    }
    else
    {
        *c++ = 0xF0 | ((u >> 18) & 0xFF);
        *c++ = 0x80 | ((u >> 12) & 0x3F);
        *c++ = 0x80 | ((u >> 6) & 0x3F);
        *c++ = 0x80 | (u & 0x3F);
    }
    return c;
}

// dump虚函数实现
static int String_dumps_(Object const *const self, struct StringType *pstr)
{
    int res, i;
    String *this = (String *)self;
    int length = this->size * 6 + 2;
    res = String_ensure_capacity(pstr, length);
    char *p = &(pstr->value[pstr->size]);
    *p++ = '"';
    for (i = 0; i < this->size; i++)
    {
        unsigned char ch = (unsigned char)this->value[i];
        switch (ch)
        {
        case '\"':
            *p++ = '\\';
            *p++ = '\"';
            break;
        case '\\':
            *p++ = '\\';
            *p++ = '\\';
            break;
        case '\b':
            *p++ = '\\';
            *p++ = 'b';
            break;
        case '\f':
            *p++ = '\\';
            *p++ = 'f';
            break;
        case '\n':
            *p++ = '\\';
            *p++ = 'n';
            break;
        case '\r':
            *p++ = '\\';
            *p++ = 'r';
            break;
        case '\t':
            *p++ = '\\';
            *p++ = 't';
            break;
        default:
            if (ch < 0x20)
            {
                *p++ = '\\';
                *p++ = 'u';
                *p++ = '0';
                *p++ = '0';
                *p++ = String_hex_digits[ch >> 4];
                *p++ = String_hex_digits[ch & 15];
            }
            else
                *p++ = ch;
        }
    }
    *p++ = '"';
    *p = '\0';
    pstr->size += p - &(pstr->value[pstr->size]);
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

    // 处理转义字符
    char *head, *p, *tmp;
    unsigned int u, u2;

    head = value;
    for (p = value; *p != '\0'; ++p)
    {
        switch (*p)
        {
        case '\\':
            switch (*(++p))
            {
            case '\"':
                *head++ = '\"';
                break;
            case '\\':
                *head++ = '\\';
                break;
            case '/':
                *head++ = '/';
                break;
            case 'b':
                *head++ = '\b';
                break;
            case 'f':
                *head++ = '\f';
                break;
            case 'n':
                *head++ = '\n';
                break;
            case 'r':
                *head++ = '\r';
                break;
            case 't':
                *head++ = '\t';
                break;
            case 'u':
                if (tmp = String_parse_hex4_(p, &u))
                {
                    p = tmp;
                    if (u >= 0xD800 && u <= 0xDBFF)
                    { /* surrogate pair */
                        if (*(++tmp) == '\\' && *(++tmp) == 'u' && !(tmp = String_parse_hex4_(tmp, &u2)))
                        {
                            p = tmp;
                            if (u2 >= 0xDC00 && u2 <= 0xDFFF)
                            {
                                u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
                            }
                        }
                    }
                    head = String_encode_utf8_(head, u);
                }
                else
                {
                    *head++ = '\\';
                    *head++ = 'u';
                }
                break;
            case '\0':
                *head++ = '\\';
                break;
            default:
                *head++ = '\\';
                *head++ = *p;
                break;
            }
            break;
        default:
            *head++ = *p;
            break;
        }
    }
    *head = '\0';

    self->size = head - value;
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