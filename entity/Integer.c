#include "Integer.h"

// new 
Object *new_int(int d)
{
    Integer *a = malloc(sizeof(Integer));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->super.objtype = 'I';
    a->value = d;
    return (Object *)a;
}


