#!/bin/bash

# run_tests.sh - Runs all the sample programs through the compiler

# Test 1: Factorial program
echo "Running factorial.my"
./src/mycompiler < test_programs/factorial.my > output/generated_code.py
python3 output/generated_code.py

# # Test 2: Fibonacci program
# echo "Running fibonacci.my"
# ./src/mycompiler < test_programs/fibonacci.my > output/generated_code.py
# python3 output/generated_code.py

# # Test 3: Sort program
# echo "Running sort.my"
# ./src/mycompiler < test_programs/sort.my > output/generated_code.py
# python3 output/generated_code.py
