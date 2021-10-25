#include "myjson.h"


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
    Object_free((Object *)strjson);


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
    Object_free((Object *)strjson);

    return 0;
}