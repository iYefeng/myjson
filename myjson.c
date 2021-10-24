#include "myjson.h"

void yyerror(struct json_state *pstate, char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

void emit(struct json_state *pstate, Object *self)
{
    pstate->obj = self;
}

int load(FILE *fp, Object **obj)
{
    int res;
    struct json_state state;
    yyrestart(fp);
    res = yyparse(&state);
    if (res == 0)
    {
        (*obj) = state.obj;
    }
    return res;
}

int loads(char const *const str, Object **obj)
{
    int res;
    struct json_state state;
    yy_scan_string(str);
    res = yyparse(&state);
    if (res == 0)
    {
        (*obj) = state.obj;
    }
    return res;
}

int dumps(Object const *const obj, String *pstr)
{
    return Object_dumps(obj, pstr);
}
