#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "builtins.h"
#include "exec.h"

void commande(void)
{
    char mot[200];
    LEX lex;
    char *argv[21];
    char *argv2[21];
    int argc = 0, argc2 = 0;
    int red_in = 0, red_out = 0, red_app = 0;
    int pipe_present = 0;
    char *file_in = NULL;
    char *file_out = NULL;

    while (1)
    {
        lex = getlex(mot);

        switch (lex)
        {
        case MOT:
            if (red_in && !file_in)
                file_in = strdup(mot);
            else if ((red_out || red_app) && !file_out)
                file_out = strdup(mot);
            else if (pipe_present)
                argv2[argc2++] = strdup(mot);
            else
                argv[argc++] = strdup(mot);
            break;

        case INF:
            red_in = 1;
            break;

        case SUP:
            red_out = 1;
            break;

        case SPP:
            red_app = 1;
            break;

        case TUB:
            pipe_present = 1;
            break;

        case NL:
        case FIN:
            goto end_parse;

        default:
            break;
        }
    }

end_parse:
    if (argc == 0)
        return;

    argv[argc] = NULL;
    if (pipe_present)
        argv2[argc2] = NULL;

    if (strcmp(argv[0], "cd") == 0)
    {
        cmd_cd(argv);
        return;
    }
    if (strcmp(argv[0], "set") == 0)
    {
        cmd_set(argv);
        return;
    }

    if (pipe_present)
    {
        exec_pipe(argv, argv2);
    }
    else if (red_in)
    {
        exec_redirection_in(argv, file_in);
    }
    else if (red_out)
    {
        exec_redirection_out(argv, file_out);
    }
    else if (red_app)
    {
        exec_redirection_append(argv, file_out);
    }
    else
    {
        exec_simple(argv);
    }

    for (int i = 0; i < argc; i++) free(argv[i]);
    for (int i = 0; i < argc2; i++) free(argv2[i]);
    free(file_in);
    free(file_out);
}
