#include <stdio.h>
#include "lex.h"

LEX getlex(char *mot)
{
    enum { Neutre, Spp, Equote, Emot } etat = Neutre;
    int c;
    char *w = mot;

    while ((c = getchar()) != EOF)
    {
        switch (etat)
        {
        case Neutre:
            switch (c)
            {
            case '<':
                return INF;
            case '>':
                etat = Spp;
                continue;
            case '|':
                return TUB;
            case '"':
                etat = Equote;
                continue;
            case ' ':
            case '\t':
                continue;
            case '\n':
                return NL;
            default:
                etat = Emot;
                *w++ = c;
                continue;
            }

        case Spp:
            if (c == '>')
                return SPP;
            ungetc(c, stdin);
            return SUP;

        case Equote:
            switch (c)
            {
            case '\\':
                *w++ = c;
                continue;
            case '"':
                *w = '\0';
                return MOT;
            default:
                *w++ = c;
                continue;
            }

        case Emot:
            switch (c)
            {
            case '|':
            case '<':
            case '>':
            case ' ':
            case '\t':
            case '\n':
                ungetc(c, stdin);
                *w = '\0';
                return MOT;
            default:
                *w++ = c;
                continue;
            }
        }
    }
    return FIN;
}
