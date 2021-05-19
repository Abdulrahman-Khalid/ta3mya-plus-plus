OBJS=ta3mya.tab.o lex.yy.o main.o

CC=g++
CFLAGS=-g -Wall -ansi -pedantic -std=c++11

FLEX_FLAGS = 
BISON_FLAGS = 

# set DEBUG_LEX=1 to enable lex debugging
ifeq ($(DEBUG_LEX),1)
	FLEX_FLAGS+=-d
	CFLAGS+=-DDEBUG_LEX
endif

# set DEBUG_YACC=1 to enable yacc debugging
ifeq ($(DEBUG_YACC),1)
	BISON_FLAGS+=--debug
endif

ta3mya: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ta3mya -lfl

lex.yy.c: ta3mya.l
	flex $(FLEX_FLAGS) ta3mya.l

ta3mya.tab.c: ta3mya.y
	bison $(BISON_FLAGS) -d -v ta3mya.y

lex.yy.o yac.o main.o: heading.h
lex.yy.o main.o: ta3mya.tab.h

clean:
	-rm -f *.o *~ lex.yy.c ta3mya.tab.c ta3mya.tab.h ta3mya.output ta3mya
