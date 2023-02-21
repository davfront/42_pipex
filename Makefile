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
BOLD				=	\033[1m
FAINT				=	\033[2m
EOC					=	\033[0m


# COMMANDS

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SILENTFLAG			= 	$(if $(filter s, $(MAKEFLAGS)),1,0)
ifeq ($(SILENTFLAG),1)
ECHO				=	\#
else
ECHO				=	echo
endif


# PROJECT

NAME				=	pipex

SRCS_DIR			=	./src
OBJS_DIR			=	./obj

SRCS_COMMON_FILES	=	\
						utils/pip_init.c\
						utils/pip_reset.c\
						utils/pip_error_exit.c\
						utils/pip_perror_exit.c\
						pip_parse_cmd_args.c\
						pip_execute.c\
						pip_pipe.c\

SRCS_FILES			=	$(SRCS_COMMON_FILES) pipex.c
SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

SRCS_BONUS_FILES	=	$(SRCS_COMMON_FILES) pipex_bonus.c
SRCS_BONUS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_BONUS_FILES))
OBJS_BONUS_FILES	=	$(SRCS_BONUS_FILES:.c=.o)
OBJS_BONUS			=	$(addprefix $(OBJS_DIR)/, $(OBJS_BONUS_FILES))

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
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(HEADER_INC) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(FT)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(OBJS) $(FT_FLAGS) -o $(NAME)
					@$(ECHO) "$(GREEN_BOLD)✓ $(NAME) is ready!$(EOC)"

.PHONY: bonus
bonus:				$(OBJS_BONUS) $(FT)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(OBJS_BONUS) $(FT_FLAGS) -o $(NAME)
					@touch $(SRCS_DIR)/pipex.c
					@$(ECHO) "$(GREEN_BOLD)✓ $(NAME) (bonus) is ready!$(EOC)"

$(FT):
					@$(ECHO) "$(CYAN)[enter directory]$(EOC) $(FT_DIR)"
					@$(MAKE) --no-print-directory -C $(FT_DIR)
					@$(ECHO) "$(CYAN)[leave directory]$(EOC) $(FT_DIR)"

.PHONY: clean
clean:
					@$(ECHO) "$(RED)[delete]$(EOC) $(OBJS_DIR)"
					@$(RM) $(OBJS_DIR)
					@$(ECHO) "$(RED)[delete]$(EOC) $(FT_DIR)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					@$(ECHO) "$(RED)[delete]$(EOC) $(FT)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) fclean
					@$(ECHO) "$(RED)[delete]$(EOC) $(NAME)"
					@$(RM) $(NAME)
					@$(ECHO) "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(EOC)"

.PHONY: re
re:					fclean
					@$(MAKE) --no-print-directory all
