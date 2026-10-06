all:
	gcc -Wall -Wextra main.c utils.c display.c -o monopoly

clean:
	rm -f monopoly
