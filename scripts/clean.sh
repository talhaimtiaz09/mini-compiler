#!/bin/bash

# clean.sh - Cleans up generated files

make clean
rm -rf output/*.py output/tokens.txt output/ast.txt output/symtab_dump.txt output/intermediate.txt
