##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

ANALYZER	=
SRC_COMPILE	=

.PHONY: all
all:
	@$(MAKE) -C asm/ $(SRC_COMPILE)
	@$(MAKE) -C corewar/ $(SRC_COMPILE)

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

.PHONY: clean
clean:
	@rm -f *.gcno
	@rm -f *.gcda
	@rm -f vgcore.*
	@rm -f *.log
	@$(MAKE) -C asm/ clean
	@$(MAKE) -C corewar/ clean

.PHONY: fclean
fclean: clean
	@$(MAKE) -C asm/ fclean
	@$(MAKE) -C corewar/ fclean
