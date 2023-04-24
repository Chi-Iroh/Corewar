##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

SRC = 	main.c

OBJ =   $(SRC:.c=.o)

CC  =   gcc
DEBUG   =   -g3 -p -ggdb3 -DDEBUG_MODE

# To prevent Marvin from flagging my code due to optimizations
RELEASE = -O0 -fno-builtin
SANITIZE	=	-fsanitize=address,undefined \
-fsanitize-recover=address,undefined
ANALYZER	=

INCLUDE = ../include/
CFLAGS  +=  -Wall -Wextra -pedantic -fsigned-char       \
-funsigned-bitfields -Wno-unused-parameter -std=gnu2x -I $(INCLUDE)
LDFLAGS	+=	-L ../lib -lmy
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

$(NAME): $(OBJ)
	@echo -------------
	@echo CC : $(CC)
	@echo CFLAGS : $(CFLAGS)
	@echo LDFLAGS : $(LD_PRELOAD) $(LDFLAGS)
	@gcc $(OBJ) $(LD_PRELOAD) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@if [[ "$(ANALYZER)" != "" ]]; then\
		$(CC) -c $(CFLAGS) $< -o $@ 2>> ../analyzer.log;\
	else\
		$(CC) -c $(CFLAGS) $< -o $@;\
	fi

.PHONY: clean
clean:
	@rm -f *.gcno
	@rm -f *.gcda
	@rm -f vgcore.*
	@rm -f *.log
	@rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
