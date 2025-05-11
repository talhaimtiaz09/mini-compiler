# === Build the Parser ===
bison: parser.y
	@bison -d parser.y

parser.tab.c parser.tab.h: parser.y
	@bison -d parser.y
	@echo "✅ Bison files parser.tab.c and parser.tab.h built successfully!"

lex.yy.c: lexer.l
	@flex lexer.l
	@echo "✅ lex.yy.c built successfully!"

parser: parser.tab.c lex.yy.c
	@gcc parser.tab.c lex.yy.c -o parser -lfl
	@echo "✅ Parser built successfully!"


# === Semantic Analyzer ===
semantic_analyzer: semantic.c symbol_table.c ../parser/parser.tab.c ../lexer/lex.yy.c
	@gcc semantic.c symbol_table.c ../parser/parser.tab.c ../lexer/lex.yy.c -o semantic_analyzer -I parser -lfl
	@echo "✅ Built semantic_analyzer successfully."

run-semantic: semantic_analyzer
	@./semantic_analyzer < ../parser/tokens.txt
	@echo "✅ Semantic analysis complete."


# === Intermediate Code Generator ===
icg: icg.c icg_utils.c
	@gcc icg.c icg_utils.c -o icg
	@echo "✅ Built ICG (Intermediate Code Generator) successfully."

run: icg
	@./icg < ../parser/tokens.txt
	@echo "✅ ICG generation complete. Output written to icg_output.txt"


# === Clean ===
clean:
	@rm -f parser semantic_analyzer icg
	@rm -f parser.tab.c parser.tab.h lex.yy.c
	@rm -f icg_output.txt
	@echo "🧹 Cleaned all build files."
