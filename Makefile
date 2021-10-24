all:	myjson

myjson:	json.l json.y \
	entity/Object.c entity/Object.h \
	entity/Integer.c entity/Integer.h \
	entity/Double.c entity/Double.h \
	entity/Boolean.c entity/Boolean.h \
	entity/String.c entity/String.h \
	entity/Null.c entity/Null.h \
	entity/Pair.c entity/Pair.h \
	entity/Dict.c entity/Dict.h \
	entity/Array.c entity/Array.h \
	myjson.h myjson.c test.c

	bison -d json.y
	flex -o json.lex.c json.l
	cc -o $@ json.tab.c json.lex.c entity/Object.c entity/Integer.c entity/Double.c entity/Boolean.c \
	entity/String.c entity/Null.c entity/Pair.c entity/Dict.c entity/Array.c myjson.c test.c

clean:
	rm myjson json.tab.c json.tab.h json.lex.c