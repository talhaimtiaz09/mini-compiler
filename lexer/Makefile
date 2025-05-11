lexer: lex.yy.c
	@gcc lex.yy.c -o lexer -L/opt/homebrew/opt/flex/lib -lfl

lex.yy.c: lexer.l
	@flex lexer.l

run: lexer
	@./lexer < ../testcases/example1.pycsrc > tokens.txt
	@echo "✅ Tokens written to tokens.txt"

clean:
	@rm -f lex.yy.c lexer tokens.txt
