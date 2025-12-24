CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = main.o lex.o builtins.o exec.o commande.o

all: minishell

minishell: $(OBJS)
	$(CC) $(CFLAGS) -o minishell $(OBJS)

clean:
	rm -f $(OBJS) minishell
