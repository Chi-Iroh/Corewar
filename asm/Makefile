##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

SRC = 	main.c \
parser_check_instruction_syntax.c \
parser_check_word_syntax.c \
parser_free.c \
parser_linked_list.c

OBJ =   $(SRC:.c=.o)

CC  =   gcc
DEBUG   =   -g3 -p -ggdb3 -DDEBUG_MODE

# To prevent Marvin from flagging my code due to optimizations
RELEASE = -O0 -fno-builtin
SANITIZE	=	-fsanitize=address,undefined \
-fsanitize-recover=address,undefined
ANALYZER	=

INCLUDE_DIR	= ../include/
LIB_DIR	=	../lib/
CFLAGS  +=  -Wall -Wextra -pedantic -fsigned-char       \
-funsigned-bitfields -Wno-unused-parameter -std=gnu2x -I $(INCLUDE_DIR)
LDFLAGS	+=	-L $(LIB_DIR) -lmy
LD_PRELOAD	=

NAME    =   asm

.PHONY: all re
all: CFLAGS += $(RELEASE)
all: $(NAME)
re: fclean all

.PHONY: debug redebug
debug: CFLAGS += $(DEBUG)
debug: $(NAME)
redebug: fclean debug

.PHONY: sanitize resanitize
sanitize: CFLAGS += $(DEBUG) $(SANITIZE)
sanitize: LD_PRELOAD += -lasan -lubsan
sanitize: $(NAME)
resanitize: fclean sanitize

.PHONY: analyzer reanalyzer
analyzer: ANALYZER += on
analyzer: CFLAGS += $(DEBUG) -fanalyzer
analyzer: $(NAME)
reanalyzer: fclean analyzer

.PHONY: clean_tests
clean_tests:
	@echo [ASM] Removing criterion temporary files.
	@rm -f *.gcda
	@rm -f *.gcno

.PHONY: tests
tests: clean_tests
	@if [[ "$(shell find tests/ -type f -name '*.c')" == "" ]]; then	\
		echo "[ASM] No .c file in asm/tests/ directory - aborting.";	\
		exit 1;															\
	fi
	@echo [ASM] Building tests
	@gcc -g3 -o asm  $(shell ls *.c | grep -v main.c) tests/*.c 	\
		--coverage -lcriterion ../corewar/op.c -I $(INCLUDE_DIR) $(LDFLAGS)
	@echo "[ASM] Running tests :"
	@./asm
	@echo "[ASM] Writing line coverage log in asm/line_coverage.log."
	@gcovr --exclude tests/ > line_coverage.log
	@echo "[ASM] Writing branch coverage log in asm/branch_coverage.log."
	@gcovr --exclude tests/ --branches > branch_coverage.log

$(NAME): $(OBJ)
	@echo -------------
	@echo [ASM] CC : $(CC)
	@echo [ASM] CFLAGS : $(CFLAGS)
	@echo [ASM] LDFLAGS : $(LD_PRELOAD) $(LDFLAGS)
	@gcc $(OBJ) $(LD_PRELOAD) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@if [[ "$(ANALYZER)" != "" ]]; then\
		$(CC) -c $(CFLAGS) $< -o $@ 2>> ../analyzer.log;\
	else\
		$(CC) -c $(CFLAGS) $< -o $@;\
	fi

.PHONY: clean
clean: clean_tests
	@echo [ASM] Removing temporary and object files.
	@rm -f vgcore.*
	@rm -f *.log
	@rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	@echo [ASM] Removing binary.
	@rm -f $(NAME)
