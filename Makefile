CC = clang
FLAGS = -g 
# -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
#  -Wall -Werror -Wextra
all: main.o
	$(CC) $(FLAGS) $^ -lm -o task45.out
# all: max.o
# 	$(CC) $(FLAGS) $^ -lm -o task_max.out

main.o: main.cpp
	$(CC) $(FLAGS) -c $<
# max.o: max.c
# 	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.out *.o

vg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./task45.out --calculate in1.txt in2.txt

rebuild: clean all