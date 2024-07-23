#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 00:16:52 by mmorot            #+#    #+#              #
#    Updated: 2024/07/23 02:24:52 by mmorot           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SHELL:=/bin/bash
NAME = philo

ARGS = $(filter-out $@, $(MAKECMDGOALS))

CC = gcc
RM = rm -f

# SANITIZE		=	-fsanitize=thread -g3

CFLAGS = ${SANITIZE} -Wall -Wextra -Werror

SDIR = src
BDIR = .build
HDIR = include

LIB_PATH :=
LIB_DIR :=
LIB_INCLUDE :=
LIB_FLAGS :=

SRCS :=

SFILES = $(SRCS:%=$(SDIR)/%)
OFILES = $(SRCS:%.c=$(BDIR)/%.o)


# COLORS

RED = \033[0;31m
GREEN = \033[0;95m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
ORANGE = \033[0;91m
CYAN = \033[0;36m
RESET = \033[0m

NAME_COLOR = $(GREEN)[$(YELLOW)$(NAME)$(RESET)$(GREEN)]$(RESET)


LIB_FLAGS := -l pthread

all: $(NAME)
	@mkdir -p $(@D)
	@if [ $$(find $(SFILES) -newer $(NAME)) ]; then \
		printf "$(NAME_COLOR) recompiling...$(RESET)\n"; \
	fi;
	@$(MAKE) -s $(NAME)

include config/lib.mk
include config/src.mk

$(NAME) : $(OFILES) | $(LIB_PATH)
	@$(CC) $(CFLAGS) -o $@ $(OFILES) $(LIB_FLAGS)
	@printf "$(NAME_COLOR) Compilation done$(RESET)\n";

$(BDIR)/%.o : $(SDIR)/%.c
	@mkdir -p $(@D)
	@printf "$(NAME_COLOR) Compiling$(GREEN) $< $(RESET)\n";
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDIR)/ $(LIB_INCLUDE)
	@printf "$(NAME_COLOR) \
	$@ $(RESET)\n";

clean	::
	@printf "$(NAME_COLOR) Cleaning$(RESET)\n";
	@$(RM) $(OFILES)

re	:: fclean
	@$(MAKE) -s all

fclean	:: clean
	@printf "$(NAME_COLOR) Removing exec $(NAME)$(RESET)\n";
	@$(RM) $(NAME)

force	::

start : all
	@printf "$(NAME_COLOR) $(GREEN)Starting...$(RESET)\n";
	@clear;
	@./$(NAME) $(ARGS)

hotloading : all
	@printf "$(NAME_COLOR) Hotloading$(RESET)\n";
	@printf "$(NAME_COLOR) PARAMS IS : $(ORANGE)$(ARGS)$(RESET)\n"
	@printf "$(NAME_COLOR) $(BLUE)$(SFILES)$(RESET)\n";
	@COUNT=0
	@while true; do \
		# sleep 1; \
		if [ $$(find $(SFILES) -newer $(NAME)) ]; then \
			printf "$(NAME_COLOR) $(ORANGE)Changes detected, recompiling...$(RESET)\n"; \
			printf "$(NAME_COLOR) $(ORANGE)Restarting the program...$(RESET)\n"; \
			touch $(NAME); \
			$(MAKE) -s start $(ARGS); \
		elif [[ $$COUNT -eq 0 ]]; then \
			touch $(NAME); \
			$(MAKE) -s start $(ARGS); \
			COUNT=1; \
		fi; \
	done

norm:
	@printf "$(NAME_COLOR) norminette$(RESET)\n"
	-@norminette $(SDIR)/%.c $(LIB_INCLUDE) $(HDIR) | grep Error
	@printf "$(NAME_COLOR) comment$(RESET)\n"
	-@cat $(SFILES) | grep "//"

.PHONY: all clean fclean re force start norm hotloading
