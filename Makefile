# | | ___ \ \ | |
# | | ) | | |\/ | _ | | / _
# ___ __| __/ | | | | ( | < __/
# _| _____| _| _| \__,_|_|\_\ \___|
# by jcluzet
################################################################################
# CONFIG #
################################################################################

NAME :=     pipex
CC :=   cc
FLAGS := -Wall -Wextra -Werror -g # Add debugging flags here
################################################################################
# PROGRAM'S SRCS #
################################################################################

SRCS := srcs/ft_putstr_fd.c \
        srcs/ft_strlcpy.c \
        srcs/ft_strlen.c \
        srcs/ft_strjoin.c \
        srcs/ft_putchar_fd.c \
        srcs/ft_strdup.c \
        srcs/ft_strnstr.c \
        srcs/ft_split.c \
        srcs/error.c \
        srcs/pipex.c \

OBJS := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
# Makefile objs #
################################################################################

CLR_RMV := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
CYAN := \033[1;36m
RM := rm -f

${NAME}:    ${OBJS}
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	${CC} ${FLAGS} -o ${NAME} ${OBJS}
	@echo "$(GREEN)$(NAME) created[0m ✔️"

all:	${NAME}

bonus:	all

clean:
	@ ${RM} *.o */*.o */*/*.o
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@ ${RM} ${NAME}
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

debug:  FLAGS := -Wall -Wextra -Werror -g3 --fsanitize=address -fsanitize=undefined
debug:  fclean all

.PHONY: all clean fclean re debug
