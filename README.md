# myjson(自定义json解析器，采用flex，bison编写解析规则)

## json格式说明
1. 支持标准json解析，标准json定义参考[json.org](https://www.json.org/json-zh.html)
2. 支持解析json字符串key无引号，例如: {id:1234, name: "yefeng"}
3. 支持key, 字符串使用单引号，例如: {'id':1234, 'name': 'yefeng'}

## 解析器提供函数
1. 反序列化JSON字符串
```
int loads(char const *const str, Object **obj);
```

2. 序列化JSON，返回字符串
```
int dumps(Object const *const obj, char *strjson);
```

3. 读取文件，反序列化JSON
```
int load(FILE *fp, Object **obj);
```


## 测试
test.c适用于测试myjson解析库开发的用例。
```
make
cat test/ok9.json | ./checkjson
或
./checkjson test/ok9.json
或
make check
```


## 编译说明
```
git submodule init
git submodule update
make
make check
```