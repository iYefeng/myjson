#include "myjson.h"

int main(int argc, char **argv)
{
    Object *json;
    String *strjson;
    char *filename;
    int res;

    FILE *in_f;
    if (argc > 1)
    {
        filename = argv[1];
        if ((in_f = fopen(argv[1], "r")) == NULL)
        {
            perror(argv[1]);
            exit(1);
        }
    }
    else
    {
        filename = "(stdin)";
        in_f = stdin;
    }
    res = load(in_f, &json);
    if (res == 0)
    {
        printf("[OK] string[%s] can be converted into json\n", filename);
        strjson = (String *)new_string_empty(1000);
        res = dumps(json, strjson);
        if (res == 0)
        {
            printf("json decode SUCCESS: \n%s\n", strjson->value);
            return 0;
        } else {
            printf("[ERROR] dumping json occurs error\n");
            return 1;
        }
    }
    else
    {
        printf("[ERROR] string cannot be converted into json\n");
        return 1;
    }

    Object_free(json);
    Object_free((Object *)strjson);
}