all:
	gcc -o main main.c src/**/*.c -Wno-unused-result -Wno-stringop-overflow -lm -g
