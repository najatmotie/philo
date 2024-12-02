NAME = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

SRC = main.c check.c time.c init.c create.c routine.c

OBJ = ${SRC:.c=.o}

${NAME} : ${OBJ} philo.h
	cc ${CFLAGS} ${OBJ} -o ${NAME}

all : ${NAME}

clean : 
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all