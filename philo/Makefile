# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dreijans <dreijans@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/12 21:01:52 by dreijans      #+#    #+#                  #
#    Updated: 2023/12/13 06:48:53 by djoyke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=thread
OBJ			= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR		= obj
SRC			= \
			main.c\
			

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
		$(CC) $(OBJ) -o $(NAME) $(LIBS)
		@ echo "${PURPLE} ---> Made!${DONE}"

$(OBJDIR)/%.o: %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^
		
$(OBJDIR)/%.o:
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^
		
run:	$(NAME)
	@ ./$(NAME)

flags:
	$(NAME) $(CFLAGS) 
	@ ./$(NAME) with flags

norm:
	@ norminette

clean:
		@$(MAKE) clean -C
		@rm -rf $(OBJDIR)

fclean: clean
		@$(MAKE) fclean -C
		@rm -f $(NAME)
		@echo "${YELLOW} // philo fCleaned!${RESET}"

re:		fclean all

.PHONY: all clean fclean re norminette
