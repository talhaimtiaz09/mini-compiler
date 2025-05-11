# Target to build the code optimizer
optimizer: optimizer.c
	@gcc optimizer.c -o optimizer
	@echo "✅ Built optimizer successfully."

# Target to run the optimizer
run: optimizer
	@./optimizer
	@echo "✅ Code optimization complete. Output written to optimized_ir.txt"

# Optional clean rule
clean:
	@rm -f optimizer optimized_ir.txt optimized_output.txt
	@echo "🧹 Cleaned optimizer build and output files."
