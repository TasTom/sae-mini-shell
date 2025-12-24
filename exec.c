#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "exec.h"

void exec_simple(char *argv[])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("fork");
    }
}

void exec_redirection_in(char *argv[], char *fichier)
{
    int fd = open(fichier, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd);
        wait(NULL);
    }
    else
    {
        perror("fork");
        close(fd);
    }
}

void exec_redirection_out(char *argv[], char *fichier)
{
    int fd = open(fichier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd);
        wait(NULL);
    }
    else
    {
        perror("fork");
        close(fd);
    }
}

void exec_redirection_append(char *argv[], char *fichier)
{
    int fd = open(fichier, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd);
        wait(NULL);
    }
    else
    {
        perror("fork");
        close(fd);
    }
}

void exec_pipe(char *argv1[], char *argv2[])
{
    int pipefd[2];
    
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(argv1[0], argv1);
        perror("execvp");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(argv2[0], argv2);
        perror("execvp");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}
