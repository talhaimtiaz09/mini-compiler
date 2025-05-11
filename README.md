# 📘 Compiler Construction Term Project — Mini Compiler for Python Subset

### Course: CC CS424L – Compiler Construction

### Project: Lexical Analyzer to Machine Code Generation

---

## 🔧 Overview

This project implements a **mini compiler** for a **subset of the Python language**, developed using **Flex**, **Bison**, and **C**. It covers all major phases of compiler construction—starting from **lexical analysis** to **machine code generation**—and is designed to compile moderately complex programs written in this Python subset.

---

## 🧱 Project Modules

### ✅ 1. **Language Definition**

- **Target Language**: Subset of Python
- **Supported Features**:

  - Variables and basic types (`int`, `float`, `string`)
  - Arithmetic and logical expressions
  - Control structures (`if`, `else`, `while`, `for`)
  - Functions (with parameters)
  - Arrays (1D)
  - Basic classes and objects (optional/bonus)

- **Grammar**: Written in BNF/EBNF format in `docs/grammar.txt`

---

### ✅ 2. **Lexical Analyzer (Lexer)**

- **Tool**: Flex
- **Responsibilities**:

  - Tokenizing keywords, identifiers, literals, operators
  - Removing whitespace and comments

- **Output**: Token stream with type, value, and line number
- **Source File**: `src/lexer.l`

---

### ✅ 3. **Syntax Analyzer (Parser)**

- **Tool**: Bison
- **Responsibilities**:

  - Parsing token stream based on defined grammar
  - Constructing Abstract Syntax Tree (AST)
  - Handling syntax errors gracefully

- **Source File**: `src/parser.y`

---

### ✅ 4. **Semantic Analyzer**

- **Language**: C
- **Responsibilities**:

  - Type checking
  - Symbol table management
  - Scope resolution
  - Function and variable validation

- **Files**: `src/semantic.c`, `include/semantic.h`

---

### ✅ 5. **Intermediate Code Generation**

- **Format**: Three Address Code (3AC)
- **Responsibilities**:

  - AST traversal
  - Generate IR using quadruples or triples

- **Files**: `src/intermediate.c`, `include/intermediate.h`
- **Output**: IR stored in `output/ir.txt`

---

### ✅ 6. **Code Optimization**

- **Techniques**:

  - Constant Folding
  - Dead Code Elimination
  - Common Subexpression Elimination
  - Loop Invariant Code Motion (optional)

- **Files**: `src/optimizer.c`, `include/optimizer.h`
- **Output**: Optimized IR in `output/optimized_ir.txt`

---

### ✅ 7. **Machine Code Generation**

- **Target**: x86-like assembly (simplified or virtual machine format)
- **Responsibilities**:

  - Translate IR into assembly code
  - Manage registers and memory

- **Files**: `src/codegen.c`, `include/codegen.h`
- **Output**: Assembly code in `output/machine_code.asm`

---

### ✅ 8. **Compiler Interface**

- **Type**: Command-Line Interface (CLI)
- **Features**:

  - Accepts source `.pycsrc` files
  - Options to print intermediate outputs (`--tokens`, `--ir`, `--asm`)
  - Step-by-step debug flags

- **Entry File**: `main.c`

---

## 📁 Recommended Directory Structure

```
mini-python-compiler/
│
├── lexer/                          # 🔹 Lexical Analysis
│   ├── lexer.l                     # Flex rules
│   ├── tokens.txt                  # Sample output (token stream)
│   └── README.md                   # Token specs and sample runs
│
├── parser/                         # 🔹 Syntax Analysis
│   ├── parser.y                    # Bison grammar
│   ├── ast.c / ast.h               # AST structure (optional)
│   └── README.md                   # Grammar notes and parse tree description
│
├── semantic_analyzer/             # 🔹 Semantic Analysis
│   ├── semantic.c
│   ├── semantic.h
│   ├── symbol_table.c
│   ├── symbol_table.h
│   └── README.md                   # Type rules, scope handling, symbol table format
│
├── ir_generator/                   # 🔹 Intermediate Code Generation
│   ├── intermediate.c
│   ├── intermediate.h
│   ├── ir.txt                      # Raw IR output
│   └── README.md                   # IR format and design rationale
│
├── optimizer/                      # 🔹 Code Optimization
│   ├── optimizer.c
│   ├── optimizer.h
│   ├── optimized_ir.txt            # Output after optimization
│   └── README.md                   # Optimization passes implemented
│
├── codegen/                        # 🔹 Machine Code Generation
│   ├── codegen.c
│   ├── codegen.h
│   ├── machine_code.asm            # Final output
│   └── README.md                   # Instruction format and architecture notes
│
├── interface/                      # 🔹 CLI & Compiler Driver
│   ├── main.c
│   ├── utils.c / utils.h           # Shared helper functions
│   └── README.md                   # CLI usage instructions
│
├── testcases/                      # 🔹 Test Programs in Python Subset
│   ├── example1.pycsrc
│   ├── example2.pycsrc
│   └── README.md                   # Test case documentation
│
├── docs/                           # 🔹 Documentation
│   ├── grammar.txt                 # Language grammar (BNF/EBNF)
│   ├── design_decisions.pdf        # Project design explanation
│   └── sample_walkthrough.pdf      # Full pipeline example (input → machine code)
│
├── report/                         # 🔹 Final Submission Report
│   └── compiler_report.pdf
│
├── Makefile                        # 🔹 Automated build instructions
└── README.md                       # 🔹 Project overview and setup guide
```

---

## 📋 Project Report Checklist

Include the following in your final PDF report:

1. Group Members and Roll Numbers
2. Compiler Name
3. Language Grammar
4. Tools and Technologies Used
5. Screenshots and Examples:

   - Token Stream
   - Parse Tree / AST
   - IR Code
   - Optimized IR
   - Final Machine Code

6. Challenges Faced and Solutions
7. Future Work / Improvements
