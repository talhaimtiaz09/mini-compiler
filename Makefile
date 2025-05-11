# Makefile: Step-by-step Mini Python Compiler build and run

CC = gcc
CFLAGS = -Wall -g

# Directories
LEXER_DIR = lexer
PARSER_DIR = parser
SEMANTIC_DIR = semantic_analyzer
IR_DIR = ir_generator
OPT_DIR = optimizer
CODEGEN_DIR = codegen
INTERFACE_DIR = interface

# Binaries
LEXER = $(LEXER_DIR)/lexer
PARSER = $(PARSER_DIR)/parser
SEMANTIC = $(SEMANTIC_DIR)/semantic_analyzer
IR_GEN = $(IR_DIR)/ir_generator
OPTIMIZER = $(OPT_DIR)/optimizer
CODEGEN = $(CODEGEN_DIR)/codegen
INTERFACE = compiler

# Step 1: Build Lexer
lexer: $(LEXER_DIR)/lexer.l
	@echo "🧱 Building Lexer..."
	cd $(LEXER_DIR) && flex lexer.l
	$(CC) $(CFLAGS) -o $(LEXER) $(LEXER_DIR)/lex.yy.c
	@echo "✅ Lexer built."

# Step 2: Build Parser
parser: lexer $(PARSER_DIR)/parser.y
	@echo "🧱 Building Parser..."
	cd $(PARSER_DIR) && bison -d parser.y
	$(CC) $(CFLAGS) -o $(PARSER) $(PARSER_DIR)/parser.tab.c $(PARSER_DIR)/lex.yy.c
	@echo "✅ Parser built."

# Step 3: Build Semantic Analyzer
semantic: $(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/symbol_table.c
	@echo "🧱 Building Semantic Analyzer..."
	$(CC) $(CFLAGS) -o $(SEMANTIC) $(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/symbol_table.c
	@echo "✅ Semantic Analyzer built."

# Step 4: Build IR Generator
ir: $(IR_DIR)/intermediate.c
	@echo "🧱 Building IR Generator..."
	$(CC) $(CFLAGS) -o $(IR_GEN) $(IR_DIR)/intermediate.c
	@echo "✅ IR Generator built."

# Step 5: Build Optimizer
optimizer: $(OPT_DIR)/optimizer.c
	@echo "🧱 Building Optimizer..."
	$(CC) $(CFLAGS) -o $(OPTIMIZER) $(OPT_DIR)/optimizer.c
	@echo "✅ Optimizer built."

# Step 6: Build Code Generator
codegen: $(CODEGEN_DIR)/codegen.c
	@echo "🧱 Building Code Generator..."
	$(CC) $(CFLAGS) -o $(CODEGEN) $(CODEGEN_DIR)/codegen.c
	@echo "✅ Code Generator built."

# Step 7: Build Interface
interface: $(INTERFACE_DIR)/main.c $(INTERFACE_DIR)/utils.c
	@echo "🧱 Building Compiler Interface..."
	$(CC) $(CFLAGS) -o $(INTERFACE) \
		$(INTERFACE_DIR)/main.c $(INTERFACE_DIR)/utils.c \
		$(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/symbol_table.c \
		$(IR_DIR)/intermediate.c \
		$(OPT_DIR)/optimizer.c \
		$(CODEGEN_DIR)/codegen.c
	@echo "✅ Interface built."

# All
all: lexer parser semantic ir optimizer codegen interface
	@echo "🎉 All components built successfully."

# Clean
clean:
	@echo "🧹 Cleaning up..."
	rm -f $(LEXER_DIR)/lex.yy.c
	rm -f $(PARSER_DIR)/parser.tab.*
	rm -f $(LEXER) $(PARSER) $(SEMANTIC) $(IR_GEN) $(OPTIMIZER) $(CODEGEN)
	rm -f $(INTERFACE)
	@echo "✅ Clean complete."

.PHONY: all clean lexer parser semantic ir optimizer codegen interface
