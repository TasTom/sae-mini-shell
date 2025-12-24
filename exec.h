#ifndef EXEC_H
#define EXEC_H

void exec_simple(char *argv[]);
void exec_redirection_in(char *argv[], char *fichier);
void exec_redirection_out(char *argv[], char *fichier);
void exec_redirection_append(char *argv[], char *fichier);
void exec_pipe(char *argv1[], char *argv2[]);

#endif
