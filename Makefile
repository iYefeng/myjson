TARGET1 = myjson_test1

CCTOOL = gcc
CXXTOOL = g++
LINKTOOL = g++
ARTOOL = ar

OBJS =  $(patsubst %.c,%.o,$(wildcard entity/*.c))
OBJS += myjson.o json.tab.o json.lex.o

all:	$(TARGET1)

$(TARGET1):	$(OBJS) test.o
	$(LINKTOOL) -o $(TARGET1) $(OBJS) test.o

clean:
	rm $(TARGET1) json.tab.h $(OBJS) test.o

%.lex.c:%.l
	@echo flex Compiling [$<]
	flex -o $@ $<

%.tab.c: %.y
	@echo bison Compiling [$<]
	bison -d $<

%.o: %.c
	@echo Compiling [$<]
	$(CCTOOL) -o $@  -c $< $(CCFLAGS)

