# Target to build the code optimizer
mcg: machine_code_generator.c
	@gcc machine_code_generator.c -o machine_code_generator
	@echo "✅ Built machine_code_generator successfully."

# Target to run the optimizer
run: machine_code_generator
	@./machine_code_generator
	@echo "✅ Code optimization complete. Output written to optimized_output.txt"

# Optional clean rule
clean:
	@rm -f machine_code_generator optimized_output.txt machine_code.txt
	@echo "🧹 Cleaned optimizer build and output files."
