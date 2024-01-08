all:
	gcc -o main main.c src/**/*.c -Wno-unused-result -Wno-stringop-overflow -lm -g

scp:
	gcc -o main main_scp.c src/**/*.c -Wno-unused-result -Wno-stringop-overflow -lm -g -O3
