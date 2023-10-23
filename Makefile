all:
	gcc -o main main.c src/**/*.c -O3 -Wno-unused-result -Wno-stringop-overflow  -lm -g
