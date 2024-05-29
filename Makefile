NAME			=		philo
CC				=		cc
CFLAGS			=
PRINTF_DIR		=		lib/ft_printf
PRINTF_ARC		=		lib/ft_printf/libftprintf.a

LIBFT_DIR		=		./lib/libft
LIBFT_ARC		=		./lib/libft/libft.a

SRCS			=		./srcs/philo.c						\
						./srcs/0_philo_err/philo_err.c		\
						./srcs/1_parsing/parsing.c			\
						./srcs/2_thread/thread.c			\
						./srcs/2_thread/sleep.c

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
	@make -C $(LIBFT_DIR)
	@make -C $(PRINTF_DIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_ARC) $(PRINTF_ARC)
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
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	@echo $(CURSIVE)$(PURPLE)"		- clean $(NAME) file -"$(NONE)

re  :
	@make fclean
	@make all

.PHONY: all make clean fclean bonus re