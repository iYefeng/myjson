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

int main(int argc, char **argv)
{
    Object *json;
    String *strjson;
    int res;

    printf("[TEST01]------------------------\n");
    res = loads("{\"name\":\"yefeng\"}\n", &json);
    printf("res = %d\n", res);
    Object_debug(json);
    printf("\n");
    Object_free(json);

    printf("[TEST02]------------------------\n");
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
    // Object_debug(json);
    strjson = (String *)new_string_empty(1000);
    res = dumps(json, strjson);
    printf("dump res= %d\n", res);
    if (res == 0) {
        printf("json decode SUCCESS: %s\n", strjson->value);
    }
    
    Object_free(json);
    Object_free(strjson);


    printf("[TEST03]------------------------\n");
    res = loads("{'id\':\"1234567890\"}\n", &json);
    printf("res = %d\n", res);

    // Object_debug(json);
    strjson = (String *)new_string_empty(1000);
    res = dumps(json, strjson);
    printf("dump res= %d\n", res);
    if (res == 0) {
        printf("json decode SUCCESS: %s\n", strjson->value);
    }
    
    Object_free(json);
    Object_free(strjson);

    return 0;
}