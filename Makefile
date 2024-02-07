NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -rf

SRC_DIR = src/

LIBFT_DIR = libft/

OBJ_DIR = obj/

SRC = pipex.c parse_cmd.c utils.c

INCLUDE = inc/pipex.h Makefile libft/*.c

OBJ = ${addprefix ${OBJ_DIR},${SRC:.c=.o}}


all: ${NAME}

${NAME}: ${OBJ}
		make -C $(LIBFT_DIR)
		${CC} ${CFLAGS} -o ${NAME} ${OBJ} -L ./libft -lft

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${INCLUDE}
		@mkdir -p ${OBJ_DIR}
		${CC} ${CFLAGS} -c -o $@ $<

clean:
		$(RM) ${OBJ}
		make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) ${NAME}
		make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


