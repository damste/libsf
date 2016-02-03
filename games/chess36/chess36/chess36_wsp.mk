.PHONY: clean All

All:
	@echo ----------Building project:[ chess36 - Debug ]----------
	@"$(MAKE)" -f "chess36.mk"
clean:
	@echo ----------Cleaning project:[ chess36 - Debug ]----------
	@"$(MAKE)" -f "chess36.mk" clean
