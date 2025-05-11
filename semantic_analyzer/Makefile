

bison: parser.y
	@bison -d parser.y

# Target to generate the lexer (lex.yy.c) from lexer.l
lex.yy.c: lexer.l
	@flex lexer.l
	@echo "✅ lex.yy.c built successfully!"


# Target to build the parser
parser: parser.tab.c lex.yy.c
	@gcc parser.tab.c lex.yy.c -o parser -L/opt/homebrew/opt/flex/lib -lfl
	@echo "✅ Parser built successfully!"

# Target to generate the Bison parser files
parser.tab.c parser.tab.h: parser.y
	@bison -d parser.y
	@echo "✅ Bison files parser.tab.c and parser.tab.h built successfully!"

semantic_analyzer: semantic.c symbol_table.c lex.yy.c
	@gcc semantic.c symbol_table.c parser.tab.c lex.yy.c -o semantic_analyzer -I parser -L/opt/homebrew/opt/flex/lib -lfl
	@echo "✅ Built semantic_analyzer successfully."

run: semantic_analyzer
	@./semantic_analyzer < ../testcases/example1.py
	@echo "✅ Semantic analysis complete."

clean:
	@rm -f semantic_analyzer parser parser.tab.c parser.tab.h lex.yy.c
	@echo "🧹 Cleaned build files."


# semantic_analyzer: semantic.c symbol_table.c ../parser/parser.tab.c ../parser/lex.yy.c
# 	@gcc -DSEMANTIC semantic.c symbol_table.c ../parser/parser.tab.c ../parser/lex.yy.c -o semantic_analyzer -I../parser -L/opt/homebrew/opt/flex/lib -lfl
# 	@echo "✅ Built semantic_analyzer successfully."

# run: semantic_analyzer
# 	@./semantic_analyzer < ../testcases/example1.py
# 	@echo "✅ Semantic analysis complete."

# clean:
# 	@rm -f semantic_analyzer
# 	@echo "🧹 Cleaned build files."
