# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 17:02:14 by edribeir      #+#    #+#                  #
#    Updated: 2024/05/22 14:25:52 by edribeir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CFLAGS = -Wall -Werror -Wextra -g

WHITE_B = \033[1;37m
RED = \033[31m
PINK = \033[35m
GREEN = \033[32m
B_GREEN = \033[0;102m
YELLOW = \033[33m
BLUE = \033[96m
CYAN = \033[36m
BOLD = \033[1m
RESET = \033[0m

SOURCE = main.c \

OBJECTS = $(SOURCE:%.c=obj/%.o)

OBJ_DIR = obj

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(PINK)$(BOLD)\n	 R E A D Y! $(RESET)🎉\n"

obj/%.o:%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c -o $@ $^ 

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)$(WHITE_B) OFILES Cleansed! $(RESET) 🆗"

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "$(B_GREEN)$(WHITE_B) ALL Cleansed! $(RESET)	🆗"

re: fclean all

PHONY: all clean fclean re