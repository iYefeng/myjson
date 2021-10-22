all:	myjson

myjson:	json.l json.y myjson.h entity/Object.c entity/Object.h \
	entity/Integer.c entity/Integer.h \
	myjson.c
	bison -d json.y
	flex -o json.lex.c json.l
	cc -o $@ json.tab.c json.lex.c entity/Object.c entity/Integer.c myjson.c 

clean:
	rm myjson json.tab.c json.tab.h json.lex.c