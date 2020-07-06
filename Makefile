# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/28 15:47:12 by blinnea           #+#    #+#              #
#    Updated: 2020/07/06 19:55:37 by blinnea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=/bin/zsh
# **************************************************************************** #
#                                 COLOURS                                      #
# **************************************************************************** #
DEFAULT =	\033[0m
YELLOW =	\033[1;33m
GREEN =		\033[1;32m
RED =		\033[1;31m
GREENB =	\033[42m

# **************************************************************************** #
#                               COMPILER OPTIONS                               #
# **************************************************************************** #
CC =		gcc
CF =		-Wall -Wextra -Werror -ggdb

# **************************************************************************** #
#                               ABBREVIATIONS                                  #
# **************************************************************************** #
LFT =		libft

# **************************************************************************** #
#                                 HEADERS                                      #
# **************************************************************************** #
LFT_H =		$(LFT)/include/$(LFT).h
LRM_H =		include/libroom.h
LCO_H =		include/libcoord.h
LAM_H =		include/libam.h
ALG_H =		include/algo.h

ALL_H = $(LFT_H) $(LRM_H) $(LCO_H) $(LAM_H) $(ALG_H)

# **************************************************************************** #
#                                 FILENAMES                                    #
# **************************************************************************** #
LRMFILES =	$(shell find src/libroom -name '*.c')
LCOFILES =	$(shell find src/libcoord -name '*.c')
LAMFILES =	$(shell find src/libam -name '*.c')
ALGFILES =	$(shell find src/algo -name '*.c')

LRMOFILES =	$(addprefix obj/, $(LRMFILES:src/libroom/%.c=%.o))
LCOOFILES =	$(addprefix obj/, $(LCOFILES:src/libcoord/%.c=%.o))
LAMOFILES =	$(addprefix obj/, $(LAMFILES:src/libam/%.c=%.o))
ALGOFILES =	$(addprefix obj/, $(ALGFILES:src/algo/%.c=%.o))

ALL_O = $(LRMOFILES) $(LCOOFILES) $(LAMOFILES) $(ALGOFILES) obj/main.o

.PHONY: $(LFT) clean fclean re all

all: obj $(LFT) main
	@echo "\n> $(GREEN)... was created$(DEFAULT)"

obj/main.o: src/main.c $(ALL_H)
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include

main: $(ALL_O) $(LFT)/$(LFT).a
	@$(CC) $(CF) $(ALL_O) -L$(LFT) -lft -o $@

# create obj directory
obj:
	@mkdir -p obj

# create $(LRMOFILES)
obj/%.o: src/libroom/%.c $(LFT_H) $(LRM_H) $(LCO_H)
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(LCOOFILES)
obj/%.o: src/libcoord/%.c $(LCO_H)
	@$(CC) $(CF) -c $< -o $@ -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(LAMOFILES)
obj/%.o: src/libam/%.c $(LRM_H) $(LFT_H)
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(ALGOFILES)
obj/%.o: src/algo/%.c $(LRM_H) $(LFT_H)
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create libft.a
$(LFT):
	@make all -C $(LFT)

fclean: clean
	@rm -f main
	@echo "> $(RED)... fclean$(DEFAULT)"

clean:
	@make fclean -C $(LFT)
	@rm -f $(ALL_O)
	@rm -fd obj
	@echo "> $(YELLOW)... clean$(DEFAULT)"

re: fclean all
