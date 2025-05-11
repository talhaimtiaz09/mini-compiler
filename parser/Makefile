bison: parser.y
	@bison -d parser.y
# Target to build the parser
parser: parser.tab.c lex.yy.c
	@gcc -DPARSER parser.tab.c lex.yy.c -o parser -L/opt/homebrew/opt/flex/lib -lfl
	@echo "✅ Parser built successfully!"

# Target to generate the lexer (lex.yy.c) from lexer.l
lex.yy.c: ../lexer/lexer.l
	@flex ../lexer/lexer.l
	@echo "✅ lex.yy.c built successfully!"

# Target to generate the Bison parser files
parser.tab.c parser.tab.h: parser.y
	@bison -d parser.y
	@echo "✅ Bison files parser.tab.c and parser.tab.h built successfully!"

# Target to run the parser and output the tokens to tokens.txt
run: parser
	@./parser < ../testcases/example1.pycsrc > tokens.txt
	@echo "✅ Tokens written to tokens.txt"

# Clean up generated files
clean:
	@rm -f parser.tab.c parser.tab.h lex.yy.c parser tokens.txt
	@echo "✅ Cleaned up generated files!"




# cd ../parser
# bison -d parser.y # Generate parser.tab.c and parser.tab.h
# flex ../lexer/lexer.l # Regenerate lex.yy.c based on lexer.l
# gcc parser.tab.c lex.yy.c -o parser -lfl # Compile the parser and link with Flex
