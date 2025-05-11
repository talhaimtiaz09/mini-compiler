gcc \
 parser/parser.tab.c parser/lex.yy.c \
 semantic_analyzer/semantic.c semantic_analyzer/symbol_table.c \
 ir_generator/intermediate.c \
 optimizer/optimizer.c \
 codegen/codegen.c \
 -Iir_generator -Isemantic_analyzer -Ioptimizer -Icodegen \
 -o compiler -lfl
