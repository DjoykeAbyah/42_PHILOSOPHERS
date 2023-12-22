# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dreijans <dreijans@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/12 21:01:52 by dreijans      #+#    #+#                  #
#    Updated: 2023/12/22 23:33:06 by dreijans      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra
LDFLAGS		= 	-g -fsanitize=address
THFLAGS		=	-g -fsanitize=thread
OBJ			= 	$(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR		= 	obj
SRC			= 	main.c		\
				utils.c		\
				routine.c	\
				init.c		\
				
			
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

ifeq ($(DEBUG), 1)
    CFLAGS += $(LDFLAGS)
endif

ifeq ($(DEBUG), 2)
    CFLAGS += $(THFLAGS)
endif

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	@ echo "${PURPLE}made!${DONE}"

$(OBJDIR)/%.o: %.c
	@ mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $^
		
run: $(NAME)
	@ echo "${BLUE}made without flags${DONE}"
	@ ./$(NAME) 

flags:
	@ $(MAKE) fclean
	@ $(MAKE) DEBUG=1 all
	@ echo "${GREEN}made with address flags${DONE}"

thread-flags:
	@ $(MAKE) fclean
	@ $(MAKE) DEBUG=1 all
	@ echo "${GREEN}made with thread flags${DONE}"

norm:
	@ norminette

clean:
	@ rm -rf $(OBJDIR)

fclean: clean
	@ rm -f $(NAME)
	@ echo "${YELLOW}philo fcleaned!${DONE}"

re:	fclean all

.PHONY: all clean fclean re norminette run flags thread-flags

# NAME		= philo
# CC			= cc
# CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
# OBJ			= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
# OBJDIR		= obj
# SRC			= \
# 			main.c\


# ## COLOURS ##
# DONE		:= \033[0m
# RED			:= \033[1;91m
# GREEN		:= \033[1;92m
# YELLOW		:= \033[1;93m
# BLUE		:= \033[1;94m
# PURPLE		:= \033[1;95m
# CYAN		:= \033[1;96m
# WHITE		:= \033[1;97m
# BLACK		:= \033[1;90m

# all:	$(NAME)

# $(NAME): $(OBJ)
# 		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
# 		@ echo "${PURPLE} ---> Made!${DONE}"

# $(OBJDIR)/%.o: %.c
# 		@mkdir -p $(OBJDIR)
# 		$(CC) $(CFLAGS) -c -o $@ $^

# $(OBJDIR)/%.o:
# 		@mkdir -p $(OBJDIR)
# 		$(CC) $(CFLAGS) -c -o $@ $^

# run:	$(NAME)
# 	@ ./$(NAME)

# norm:
# 	@ norminette

# clean:
# 		@$(MAKE)
# 		@rm -rf $(OBJDIR)

# fclean: clean
# 		@$(MAKE)
# 		@rm -f $(NAME)
# 		@echo "${YELLOW} // philo fCleaned!${RESET}"

# re:		fclean all

# .PHONY: all clean fclean re norminette