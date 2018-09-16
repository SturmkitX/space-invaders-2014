#ifndef _DATABASE_H
#define _DATABASE_H

#define MAX_NAME_LEN 45

typedef struct
{
    char name[MAX_NAME_LEN];
    int score;
} SCORE_VAR;

typedef struct
{
    int size;
    SCORE_VAR *data;
} SCORE_ARRAY;

int add_score_db(char*, int);

SCORE_ARRAY* get_score_db();

#endif  // _DATABASE_H
