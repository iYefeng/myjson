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

int dumps(Object const *const obj, char *strjson)
{

    return 0;
}

int main(int argc, char **argv)
{
    Object *json;
    int res;
    
    res = loads("{\"name\":\"yefeng\"}\n", &json);
    printf("res = %d\n", res);
    Object_dump(json);
    printf("\n");
    Object_free(json);

    FILE *in_f;
    if (argc > 1)
    {
        if ((in_f = fopen(argv[1], "r")) == NULL)
        {
            perror(argv[1]);
            exit(1);
        }
    }
    else
    {
        in_f = stdin;
    }
    res = load(in_f, &json);
    printf("res = %d\n", res);
    Object_dump(json);
    printf("\n");
    Object_free(json);


    res = loads("{\"id\":\"1234567890\"}\n", &json);
    printf("res = %d\n", res);
    Object_dump(json);
    printf("\n");
    Object_free(json);

    return 0;
}