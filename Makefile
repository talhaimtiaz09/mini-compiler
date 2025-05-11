# Specify the exact order of subdirectories here
SUBDIRS := lexer parser ir_generator optimizer machine_code

.PHONY: all run clean

all:
	@echo "🔧 Building all subprojects in order..."
	@for dir in $(SUBDIRS); do \
		echo "📦 Building in $$dir..."; \
		$(MAKE) -C $$dir; \
		echo "✅ Built in $$dir"; \
	done
	@echo "✅ All projects built successfully!"

run:
	@echo "🚀 Running all subprojects in order..."
	@for dir in $(SUBDIRS); do \
		echo "▶️  Running in $$dir..."; \
		$(MAKE) -C $$dir run || echo "❌ Failed in $$dir"; \
		echo "✅ Finished $$dir"; \
	done
	@echo "✅ All projects executed!"

clean:
	@echo "🧹 Cleaning all subprojects..."
	@for dir in $(SUBDIRS); do \
		echo "🧼 Cleaning in $$dir..."; \
		$(MAKE) -C $$dir clean; \
		echo "✅ Cleaned $$dir"; \
	done
	@echo "✅ All projects cleaned!"