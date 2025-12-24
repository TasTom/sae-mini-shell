#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "commande.h"

int main(void)
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == -1){
            perror("gethostname");
            strcpy(hostname, "?");
    
    }
    char cwd[1024];

    while (1)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            strcpy(cwd, "?");
        }

        printf("%s:%s$ ", hostname, cwd);
        fflush(stdout);

        commande();
    }

    return 0;
}
