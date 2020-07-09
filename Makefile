# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/28 15:47:12 by blinnea           #+#    #+#              #
#    Updated: 2020/07/09 15:17:41 by blinnea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=/bin/zsh
NAME = lem-in
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
WAY_H =		include/libway.h

ALL_H = $(LFT_H) $(LRM_H) $(LCO_H) $(LAM_H) $(ALG_H) $(WAY_H)

# **************************************************************************** #
#                                 FILENAMES                                    #
# **************************************************************************** #
LRMFILES =	$(shell find src/libroom -name '*.c')
LCOFILES =	$(shell find src/libcoord -name '*.c')
LAMFILES =	$(shell find src/libam -name '*.c')
ALGFILES =	$(shell find src/algo -name '*.c')
WAYFILES =	$(shell find src/libway -name '*.c')

LRMOFILES =	$(addprefix obj/, $(LRMFILES:src/libroom/%.c=%.o))
LCOOFILES =	$(addprefix obj/, $(LCOFILES:src/libcoord/%.c=%.o))
LAMOFILES =	$(addprefix obj/, $(LAMFILES:src/libam/%.c=%.o))
ALGOFILES =	$(addprefix obj/, $(ALGFILES:src/algo/%.c=%.o))
WAYOFILES =	$(addprefix obj/, $(WAYFILES:src/libway/%.c=%.o))

ALL_O = $(LRMOFILES) $(LCOOFILES) $(LAMOFILES) $(ALGOFILES) $(WAYOFILES) obj/main.o

.PHONY: $(LFT) clean fclean re all

all: $(NAME)
	@echo "\n> $(GREEN)... was created$(DEFAULT)"

obj/main.o: src/main.c obj $(ALL_H)
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include

$(NAME): $(ALL_O) $(LFT)
	@$(CC) $(CF) $(ALL_O) -L$(LFT) -lft -o $@

# create obj directory
obj:
	@mkdir -p obj

# create $(LRMOFILES)
obj/%.o: src/libroom/%.c obj $(LFT_H) $(LRM_H) $(LCO_H)
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(LCOOFILES)
obj/%.o: src/libcoord/%.c obj $(LCO_H)
	@$(CC) $(CF) -c $< -o $@ -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create libam object files
obj/%.o: src/libam/%.c obj $(LRM_H) $(LFT_H)
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create algo object files
obj/%.o: src/algo/%.c obj $(LAM_H) $(LFT_H) $(ALG_H)
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create libway object files
obj/%.o: src/libway/%.c obj $(LAM_H) $(LFT_H)
	@$(CC) $(CF) -c $< -o $@ -I include -I $(LFT)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create libft.a
$(LFT):
	@make all -C $(LFT)

fclean: clean
	@rm -f $(NAME)
	@echo "> $(RED)... fclean$(DEFAULT)"

clean:
	@make fclean -C $(LFT)
	@rm -f $(ALL_O)
	@rm -fd obj
	@echo "> $(YELLOW)... clean$(DEFAULT)"

re: fclean all
