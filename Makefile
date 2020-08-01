# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/31 15:42:54 by blinnea           #+#    #+#              #
#    Updated: 2020/08/01 13:33:36 by blinnea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 17:37:07 by blinnea           #+#    #+#              #
#    Updated: 2020/07/31 15:43:12 by blinnea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=/bin/zsh
# **************************************************************************** #
#                                 COLOURS                                      #
# **************************************************************************** #
DEFAULT = \033[0m
YELLOW = \033[1;33m
GREEN = \033[1;32m
RED = \033[1;31m
GREENB = \033[42m

# **************************************************************************** #
#                               COMPILER OPTIONS                               #
# **************************************************************************** #
CC = clang
CF = -Wall -Wextra -Werror -m64

NAME = lem-in
LFT = libft

# **************************************************************************** #
#                                 HEADERS                                      #
# **************************************************************************** #
LFT_H =		$(LFT)/include/$(LFT).h
LEN_H =		include/lem_in.h
ROM_H =		include/room.h

# **************************************************************************** #
#                                 FILENAMES                                    #
# **************************************************************************** #
LENC =		$(shell find src/lem_in -name '*.c')
ROMC =		$(shell find src/room -name '*.c')
LENO =		$(addprefix obj/, $(LENC:src/lem_in/%.c=%.o))
ROMO =		$(addprefix obj/, $(ROMC:src/room/%.c=%.o))

ALLO =		$(LENO) $(ROMO)

.PHONY: $(LFT) clean fclean re all

all: $(NAME)
	@echo "\n> $(GREEN)$(NAME) created$(DEFAULT)"

obj:
	@mkdir -p obj

$(NAME): src/lem_in.c $(LFT)/$(LFT).a $(ALLO) $(LFT_H) $(ROM_H) $(LEN_H)
	@$(CC) $(CF) $< $(ALLO) -L$(LFT) -lft -I include -I $(LFT)/include -o $(NAME)

obj/%.o: src/lem_in/%.c $(LFT_H) $(ROM_H) $(LEN_H) | obj
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

obj/%.o: src/room/%.c $(LFT_H) $(ROM_H) | obj
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

$(LFT)/$(LFT).a: $(LFT)

$(LFT):
	@make -C $(LFT)

clean:
	@make fclean -C libft
	@rm -f $(ALLO)
	@rm -fd obj
	@echo "> $(YELLOW)$(NAME) clean$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "> $(RED)$(NAME) fclean$(DEFAULT)"

re: fclean all
