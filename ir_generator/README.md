gcc parser/parser.tab.c parser/lex.yy.c \
 semantic_analyzer/semantic.c semantic_analyzer/symbol_table.c \
 ir_generator/intermediate.c \
 -Iir_generator -Isemantic_analyzer -o compiler -lfl

mac
gcc parser/parser.tab.c parser/lex.yy.c \
 semantic_analyzer/semantic.c semantic_analyzer/symbol_table.c \
 ir_generator/intermediate.c \
 -Iir_generator -Isemantic_analyzer -o ir_generator/ir_generator -L/opt/homebrew/opt/flex/lib -lfl
