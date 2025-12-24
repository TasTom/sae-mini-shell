#include <stdio.h>
#include <unistd.h>
#include <string.h>

int cmd_cd(char *argv[])
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "cd: argument manquant\n");
        return 1;
    }
    if (chdir(argv[1]) != 0)
    {
        perror("cd");
        return 1;
    }
    return 0;
}

int cmd_set(char *argv[])
{
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
    return 0;
}
