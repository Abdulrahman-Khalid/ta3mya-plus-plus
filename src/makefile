SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES)) ta3mya.tab.o lex.yy.o
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

CC=g++
CXX=g++
CXXFLAGS=-g -Wall -Wextra -ansi -std=gnu++17
CFLAGS=-std=gnu++17

# pass DEBUG_LEX=1 to enable lex debugging
ifeq ($(DEBUG_LEX),1)
	FLEX_FLAGS+=-d
	CXXFLAGS+=-DDEBUG_LEX
endif

# pass DEBUG_YACC=1 to enable yacc debugging
ifeq ($(DEBUG_YACC),1)
	BISON_FLAGS+=--debug
	CXXFLAGS+=-DYYDEBUG=1
endif

.PHONY: all clean

all: ta3myac

clean:
	$(RM) *.o *~ lex.yy.c ta3mya.tab.c ta3mya.tab.h ta3mya.output ta3myac $(DEPENDS)

ta3myac: $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o ta3myac -lfl

lex.yy.c: ta3mya.l
	flex $(FLEX_FLAGS) ta3mya.l

ta3mya.tab.c: ta3mya.y
	bison $(BISON_FLAGS) -d -v ta3mya.y

-include $(DEPENDS)

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@
