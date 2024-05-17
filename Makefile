# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 17:02:14 by edribeir      #+#    #+#                  #
#    Updated: 2024/05/17 17:02:18 by edribeir      ########   odam.nl          #
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

OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(PINK)$(BOLD)\n	 R E A D Y! $(RESET)🎉\n"

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^ 

clean:
	@rm -f $(OBJECTS)
	@echo "$(B_GREEN)$(WHITE_B) OFILES Cleansed! $(RESET) 🆗"

fclean:
	@rm -f $(NAME)
	@rm -f $(OBJECTS)
	@echo "$(B_GREEN)$(WHITE_B) ALL Cleansed! $(RESET)	🆗"

re: fclean all

PHONY: all clean fclean re