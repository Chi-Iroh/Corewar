##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

ANALYZER	=
SRC_COMPILE	=
MAKE_FLAGS	= -s -j --no-print-directory

.PHONY: all
all:
	@$(MAKE) $(MAKE_FLAGS) -C lib/ $(SRC_COMPILE)
	@$(MAKE) $(MAKE_FLAGS) -C asm/ $(SRC_COMPILE)
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ $(SRC_COMPILE)

.PHONY: all
re: fclean all

.PHONY: debug redebug
debug: SRC_COMPILE += debug
debug: all
redebug: fclean debug

.PHONY: sanitize resanitize
sanitize: SRC_COMPILE += sanitize
sanitize: all
resanitize: fclean sanitize

.PHONY: reset_analyzer
reset_analyzer:
	@rm -f analyzer.log
	@echo Removing old analyzer.log

.PHONY: analyzer reanalyzer
analyzer: ANALYZER += on
analyzer: SRC_COMPILE += analyzer
analyzer: reset_analyzer all
reanalyzer: fclean analyzer

.PHONY: clean_tests
clean_tests:
	@$(MAKE) $(MAKE_FLAGS) -C asm/ clean_tests
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ clean_tests

.PHONY: tests
tests: make_lib clean_tests
	@$(MAKE) $(MAKE_FLAGS) -C asm/ tests
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ tests

.PHONY: run_tests
run_tests: tests
	@$(MAKE) $(MAKE_FLAGS) -C asm/ run_tests
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ run_tests

.PHONY: clean_lib
clean_lib:
	@$(MAKE) $(MAKE_FLAGS) -C lib/ clean

.PHONY: clean_source
clean_source:
	@rm -f *.gcno
	@rm -f *.gcda
	@rm -f vgcore.*
	@rm -f valgrind*.log.core.*
	@rm -f *.log

.PHONY: clean
clean: clean_lib clean_source
	@$(MAKE) $(MAKE_FLAGS) -C asm/ clean
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ clean

.PHONY: fclean_lib
fclean_lib:
	@$(MAKE) $(MAKE_FLAGS) -C lib/ fclean

.PHONY: fclean
fclean: fclean_lib clean_source
	@$(MAKE) $(MAKE_FLAGS) -C asm/ fclean
	@$(MAKE) $(MAKE_FLAGS) -C corewar/ fclean
