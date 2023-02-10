# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 16:33:43 by dapereir          #+#    #+#              #
#    Updated: 2023/02/09 16:33:43 by dapereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# COLORS

RED					=	\033[0;31m
RED_BOLD			=	\033[1;31m
GREEN				=	\033[0;32m
GREEN_BOLD			=	\033[1;32m
YELLOW				=	\033[0;33m
YELLOW_BOLD			=	\033[1;33m
CYAN				=	\033[0;36m
CYAN_BOLD			=	\033[1;36m
EOC					=	\033[0m
BOLD				=	\033[1m


# COMMANDS

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf


# PROJECT

NAME				=	pipex

SRCS_DIR			=	./src
OBJS_DIR			=	./obj

SRCS_FILES			=	\
						utils/pip_open_file.c\
						utils/pip_close_file.c\
						utils/pip_error_exit.c\
						\
						input/pip_get_input.c\
						\
						pipex.c\

SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./include
HEADER				=	$(HEADER_DIR)/pipex.h
HEADER_INC			=	-I $(HEADER_DIR)

FT_DIR				=	./libft
FT					=	$(FT_DIR)/libft.a
FT_INC				=	-I $(FT_DIR)/include
FT_FLAGS			=	-L $(FT_DIR) -l ft

.PHONY: all
all:				$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(FT) $(HEADER)
					@mkdir -p $(@D)
					@echo "$(GREEN_BOLD)create %.o ➞$(EOC) $@"
					@$(CC) $(CFLAGS) $(HEADER_INC) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(FT)
					@echo "$(GREEN_BOLD)create exe ➞$(EOC) $@"
					@$(CC) $(CFLAGS) $(OBJS) $(FT_FLAGS) -o $(NAME)

$(FT):
					@echo "$(GREEN_BOLD)create lib ➞$(EOC) $@"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR)

.PHONY: clean
clean:
					@echo "$(RED_BOLD)delete %.o ➞$(EOC) $(OBJS_DIR)"
					@$(RM) $(OBJS_DIR)
					@echo "$(RED_BOLD)delete %.o ➞$(EOC) $(FT_DIR)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					@echo "$(RED_BOLD)delete lib ➞$(EOC) $(FT)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) fclean
					@echo "$(RED_BOLD)delete exe ➞$(EOC) $(NAME)"
					@$(RM) $(NAME)

.PHONY: re
re:					fclean
					@$(MAKE) --no-print-directory all
