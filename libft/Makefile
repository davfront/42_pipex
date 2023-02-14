# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 11:45:20 by dapereir          #+#    #+#              #
#    Updated: 2023/02/14 13:41:17 by dapereir         ###   ########.fr        #
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
AR					=	ar rcs
RM					=	rm -f

SILENTFLAG			= 	$(if $(filter s, $(MAKEFLAGS)),1,0)
ifeq ($(SILENTFLAG),1)
ECHO				=	\#
else
ECHO				=	echo
endif

# PROJECT

NAME				=	libft.a

SRCS_DIR			=	./
OBJS_DIR			=	./obj

SRCS_FILES			=	char/ft_isalpha.c\
						char/ft_isdigit.c\
						char/ft_isalnum.c\
						char/ft_isascii.c\
						char/ft_isprint.c\
						char/ft_toupper.c\
						char/ft_tolower.c\
						\
						mem/ft_memset.c\
						mem/ft_bzero.c\
						mem/ft_memcpy.c\
						mem/ft_memmove.c\
						mem/ft_memchr.c\
						mem/ft_memcmp.c\
						mem/ft_calloc.c\
						mem/ft_free.c\
						\
						str/ft_strlen.c\
						str/ft_strlcpy.c\
						str/ft_strlcat.c\
						str/ft_strchr.c\
						str/ft_strrchr.c\
						str/ft_strncmp.c\
						str/ft_strnstr.c\
						str/ft_atoi.c\
						str/ft_strdup.c\
						str/ft_strndup.c\
						str/ft_substr.c\
						str/ft_strjoin.c\
						str/ft_strtrim.c\
						str/ft_split.c\
						str/ft_free_split.c\
						str/ft_itoa.c\
						str/ft_strmapi.c\
						str/ft_striteri.c\
						str/ft_streq.c\
						\
						write/ft_putchar_fd.c\
						write/ft_putchar.c\
						write/ft_putstr_fd.c\
						write/ft_putstr.c\
						write/ft_putendl_fd.c\
						write/ft_putendl.c\
						write/ft_putnbr_fd.c\
						write/ft_putnbr.c\
						\
						lst/ft_lstnew.c\
						lst/ft_lstadd_front.c\
						lst/ft_lstsize.c\
						lst/ft_lstlast.c\
						lst/ft_lstadd_back.c\
						lst/ft_lstdelone.c\
						lst/ft_lstclear.c\
						lst/ft_lstiter.c\
						lst/ft_lstmap.c\
						lst/ft_lst_by_index.c\
						\
						gnl/ft_gnl.c\
						\
						printf/ft_print_c.c\
						printf/ft_print_s.c\
						printf/ft_print_i.c\
						printf/ft_print_u.c\
						printf/ft_print_x.c\
						printf/ft_print_p.c\
						printf/ft_printf.c\

SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./include
HEADER				=	$(HEADER_DIR)/libft.h
HEADER_INC			=	-I $(HEADER_DIR)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(HEADER)
					@mkdir -p $(@D)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(HEADER_INC) -c $< -o $@

.PHONY: all
all:				$(NAME)

$(NAME):			$(OBJS)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(AR) $(NAME) $(OBJS)
					@$(ECHO) "$(GREEN_BOLD)✓ libft is ready!$(EOC)"
.PHONY: clean
clean:
					@$(ECHO) "$(RED)[delete]$(EOC) $(OBJS_DIR)"
					@$(RM) $(OBJS)

.PHONY: fclean
fclean:				clean
					@$(ECHO) "$(RED)[delete]$(EOC) $(NAME)"
					@$(RM) $(NAME)
					@$(ECHO) "$(RED_BOLD)✓ libft is fully cleaned!$(EOC)"

.PHONY: re
re:					fclean
					@$(MAKE) --no-print-directory all
