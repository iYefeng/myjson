TARGET1 = test1
TARGET2 = checkjson

CCTOOL = gcc
CXXTOOL = g++
LINKTOOL = g++
ARTOOL = ar

INC = -I./third-party/uthash/include

OBJS =  $(patsubst %.c,%.o,$(wildcard entity/*.c))
OBJS += myjson.o json.tab.o json.lex.o

CCFLAGS += $(INC) 

.PHONY : all clean check

all:	$(TARGET1) $(TARGET2)

$(TARGET1):	$(OBJS) test1.o
	$(LINKTOOL) -o $(TARGET1) $(OBJS) test1.o

$(TARGET2):	$(OBJS) checkjson.o
	$(LINKTOOL) -o $(TARGET2) $(OBJS) checkjson.o

clean:
	rm $(TARGET1) $(TARGET2) json.tab.h $(OBJS) test1.o checkjson.o

check:	$(TARGET2)
	./checkjson ok1.json
	./checkjson ok2.json
	./checkjson ok3.json
	./checkjson ok4.json
	./checkjson ok5.json
	./checkjson ok6.json
	./checkjson ok7.json
	./checkjson ok9.json
	./checkjson ok10.json
	./checkjson ok11.json


%.lex.c:%.l
	@echo flex Compiling [$<]
	flex -o $@ $<

%.tab.c: %.y
	@echo bison Compiling [$<]
	bison -d $<

%.o: %.c
	@echo Compiling [$<]
	$(CCTOOL) -o $@  -c $< $(CCFLAGS) $(CCFLAGS)

