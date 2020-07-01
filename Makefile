# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/28 15:47:12 by blinnea           #+#    #+#              #
#    Updated: 2020/07/02 00:22:35 by blinnea          ###   ########.fr        #
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
LRM =		libroom
LCO =		libcoord
LMP =		libmap

# **************************************************************************** #
#                                 HEADERS                                      #
# **************************************************************************** #
LFT_H =		$(LFT)/include/$(LFT).h
LRM_H =		include/$(LRM).h
LCO_H =		include/$(LCO).h
LMP_H =		include/$(LMP).h

ALL_H = $(LFT_H) $(GNL_H) $(LRM_H) $(LCO_H) $(LMP_H)

# **************************************************************************** #
#                                 FILENAMES                                    #
# **************************************************************************** #

LRMFILES =	ro_new ro_atoroom ro_free ro_compare ro_connect ro_show
LRMCFILES = $(patsubst %, src/$(LRM)/%.c, $(LRMFILES))
LRMOFILES = $(patsubst %, obj/$(LRM)/%.o, $(LRMFILES))

LCOFILES =	co_equal
LCOCFILES =	$(patsubst %, src/$(LCO)/%.c, $(LCOFILES))
LCOOFILES =	$(patsubst %, obj/$(LCO)/%.o, $(LCOFILES))

LMPFILES =	mp_add mp_free mp_new mp_atolink mp_find mp_giveweight mp_show \
			mp_thinout
LMPCFILES = $(patsubst %, src/$(LMP)/%.c, $(LMPFILES))
LMPOFILES = $(patsubst %, obj/$(LMP)/%.o, $(LMPFILES))

ALL_O = $(LRMOFILES) $(LCOOFILES) $(LMPOFILES)

.PHONY:	obj $(LFT) clean fclean re all

all: obj $(LFT) main
	@echo "\n> $(GREEN)... was created$(DEFAULT)"

obj/main.o: main.c $(ALL_H)
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I $(GNL)/include -I include

main: obj/main.o $(ALL_O)
	@$(CC) $< $(ALL_O) -L$(LFT) -lft -o $@

# create obj directory
obj:
	@mkdir -p obj
	@mkdir -p obj/$(LRM)
	@mkdir -p obj/$(LCO)
	@mkdir -p obj/$(LMP)

# create $(LRMOFILES)
obj/$(LRM)/%.o: src/$(LRM)/%.c $(LFT_H) $(LRM_H) $(LCO_H) $(LFT)/$(LFT).a
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(LCOOFILES)
obj/$(LCO)/%.o: src/$(LCO)/%.c $(LCO_H) $(LFT)/$(LFT).a
	@$(CC) $(CF) -c $< -o $@ -I include
	@echo "$(GREENB) $(DEFAULT)\c"

# create $(LMPOFILES)
obj/$(LMP)/%.o: src/$(LMP)/%.c $(ALL_H) $(LFT)/$(LFT).a
	@$(CC) $(CF) -c $< -o $@ -I $(LFT)/include -I include -I $(GNL)/include
	@echo "$(GREENB) $(DEFAULT)\c"

# create libft.a
$(LFT):
	@make all -C $(LFT)

fclean: clean
	@rm -f main
	@echo "> $(RED)... fclean$(DEFAULT)"

clean:
	@make fclean -C $(LFT)
	@rm -f $(LRMOFILES) $(LCOOFILES) $(LMPOFILES) obj/main.o
	@rm -fd obj/$(LRM) obj/$(LCO) obj/$(LMP) obj
	@echo "> $(YELLOW)... clean$(DEFAULT)"

re: fclean all
