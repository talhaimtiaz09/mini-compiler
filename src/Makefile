# Makefile

CC = gcc
CFLAGS = -Wall -g

OBJS = main.o ast.o symtab.o codegen.o parser.tab.o lex.yy.o

all: mycompiler

mycompiler: $(OBJS)
	$(CC) -o mycompiler $(OBJS)

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ast.o: ast.c
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c
	$(CC) $(CFLAGS) -c symtab.c

codegen.o: codegen.c
	$(CC) $(CFLAGS) -c codegen.c

clean:
	rm -f *.o lex.yy.c parser.tab.c parser.tab.h mycompiler output/*.py
