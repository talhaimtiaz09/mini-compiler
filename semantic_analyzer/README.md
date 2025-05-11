gcc ../parser/parser.tab.c ../parser/lex.yy.c semantic.c symbol_table.c -o ../parser/parser
./parser < ../testcases/example1.py

gcc semantic.c symbol_table.c ../parser/parser.tab.c ../parser/lex.yy.c -o semantic_analyzer -L/opt/homebrew/opt/flex/lib -lfl

gcc semantic.c symbol_table.c ../parser/parser.tab.c ../parser/lex.yy.c -o semantic_analyzer -lfl
