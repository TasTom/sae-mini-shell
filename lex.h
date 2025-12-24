#ifndef LEX_H
#define LEX_H

typedef enum
{
    MOT,
    TUB,
    INF,
    SUP,
    SPP,
    NL,
    FIN
} LEX;

LEX getlex(char *mot);

#endif
