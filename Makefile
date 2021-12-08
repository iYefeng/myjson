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
	@for file in ./test/* ; \
	do \
		./checkjson $$file ; \
		echo  ; \
	done


%.lex.c:%.l
	@echo flex Compiling [$<]
	flex -o $@ $<

%.tab.c %.tab.h:%.y
	@echo bison Compiling [$<]
	bison -d $<

%.o: %.c
	@echo Compiling [$<]
	$(CCTOOL) -o $@  -c $< $(CCFLAGS) $(CCFLAGS)

