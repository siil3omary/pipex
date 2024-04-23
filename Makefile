
NAME        := pipex
BNAME       := pipex_bonus
CC        := cc
FLAGS    := -Wall -Wextra -Werror -g -fsanitize=address

SRCS        :=      srcs/pipex.c \
                          srcs/childs.c \
                          srcs/ft_split.c \
                          srcs/ft_strdup.c \
                          srcs/ft_strjoin.c \
                          srcs/ft_strlcpy.c \
                          srcs/ft_strlen.c \
                          srcs/utils3.c \
                          srcs/utils2.c \
                          srcs/utils.c \

BSRCS        :=      srcs_bonus/pipex_bonus.c \
						  srcs_bonus/childs_bonus.c \
						  srcs_bonus/ft_split.c \
						  srcs_bonus/ft_strdup.c \
						  srcs_bonus/ft_strjoin.c \
						  srcs_bonus/ft_strlcpy.c \
						  srcs_bonus/ft_strlen.c \
						  srcs_bonus/utils2_bonus.c \
						  srcs_bonus/utils3_bonus.c \
						  srcs_bonus/utils_bonus.c \
                          
OBJS        := $(SRCS:.c=.o)

BOBJS        := $(BSRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}



CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

${BNAME}:	${BOBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(BNAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${BNAME} ${BOBJS}
			@echo "$(GREEN)$(BNAME) created[0m ✔️"
all:		${NAME}

bonus:		${BNAME}

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME} ${BNAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


