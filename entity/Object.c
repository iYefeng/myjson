#include "Object.h"
#include <assert.h>

/* Object 实现 */
// dump虚函数
static void Object_dump_(Object const *const self)
{
    assert(0); // 纯虚函数不能被调用
}

// free虚函数
static void Object_free_(Object const *const self)
{
    assert(0); // 纯虚函数不能被调用
}

// Object构造函数
void Object_ctor(Object *const self, int objtype)
{
    // Object 类的虚表
    static struct ObjectVtbl const vtbl =
        {
            &Object_dump_,
            &Object_free_};
    self->vptr = &vtbl;
    self->objtype = objtype;
}


