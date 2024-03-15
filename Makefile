NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -rf

SRC_DIR = src/

SRC_BONUS_DIR = src_bonus/

LIBFT_DIR = libft/

OBJ_DIR = obj/

OBJ_DIR_BONUS = obj_bonus/

SRC = pipex.c parse_cmd.c utils.c

INCLUDE = inc/* Makefile libft/*.c

OBJ = ${addprefix ${OBJ_DIR},${SRC:.c=.o}}

OBJ_BONUS = ${addprefix ${OBJ_DIR_BONUS},${SRC:.c=.o}}

all: ${NAME}

${NAME}: ${OBJ}
		make -C $(LIBFT_DIR)
		${CC} ${CFLAGS} -o ${NAME} ${OBJ} -L ./libft -lft

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${INCLUDE}
		@mkdir -p ${OBJ_DIR}
		${CC} ${CFLAGS} -c -o $@ $<

${OBJ_DIR_BONUS}%.o: ${SRC_BONUS_DIR}%.c ${INCLUDE}
		@mkdir -p ${OBJ_DIR_BONUS}
		${CC} ${CFLAGS} -c -o $@ $<

clean:
		$(RM) ${OBJ} ${OBJ_BONUS}
		make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) ${NAME}
		make fclean -C $(LIBFT_DIR)

re: fclean all

bonus:	${OBJ_BONUS}
		make -C $(LIBFT_DIR)
		${CC} ${CFLAGS} -o ${NAME} ${OBJ_BONUS} -L ./libft -lft

.PHONY: all clean fclean re


