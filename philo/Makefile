# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dreijans <dreijans@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/12 21:01:52 by dreijans      #+#    #+#                  #
#    Updated: 2023/12/30 19:40:32 by dreijans      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra
OBJ			= 	$(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR		= 	obj
SRC			= 	main.c			\
				utils.c			\
				routine.c		\
				init.c			\
				libft_utils.c	\
				error.c			\
					
## COLOURS ##
DONE		:= \033[0m
RED			:= \033[1;91m
GREEN		:= \033[1;92m
YELLOW		:= \033[1;93m
BLUE		:= \033[1;94m
PURPLE		:= \033[1;95m
CYAN		:= \033[1;96m
WHITE		:= \033[1;97m
BLACK		:= \033[1;90m

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@ echo "${PURPLE}made!${DONE}"

$(OBJDIR)/%.o: %.c
	@ mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

norm:
	@ norminette

clean:
	@ rm -rf $(OBJDIR)

fclean: clean
	@ rm -f $(NAME)
	@ echo "${YELLOW}philo fcleaned!${DONE}"

re:	fclean all

.PHONY: all clean fclean re norminette run flags thread-flags
