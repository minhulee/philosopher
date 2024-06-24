NAME			=		philo
CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra

SRCS			=		./srcs/philo.c						\
						./srcs/0_parse/parse.c				\
						./srcs/1_pthread/pthread.c			\
						./srcs/2_run/run.c					\
						./srcs/2_run/eat.c					\
						./srcs/2_run/util.c					\
						./srcs/3_exit/exit.c			\

OBJ				=		$(SRCS:.c=.o)

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;

all : $(NAME)

$(NAME) : $(OBJ)
	@echo $(CURSIVE)$(YELLOW) "		- Making $(NAME) -" $(NONE)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo $(CURSIVE)$(YELLOW) "		- Compiling $(NAME) -" $(NONE)
	@echo $(GREEN) "		- Complete -"$(NONE)

%.o : %.c
	@echo $(CURSIVE)$(YELLOW) "		- Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -fr $(OBJ)
	@echo $(CURSIVE)$(BLUE) "		- clean OBJ files -" $(NONE)

fclean : clean
	@rm -fr $(NAME)
	@echo $(CURSIVE)$(PURPLE)"		- clean $(NAME) file -"$(NONE)

re  :
	@make fclean
	@make all

.PHONY: all make clean fclean bonus re