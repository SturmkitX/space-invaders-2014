#ifndef _DATABASE_H
#define _DATABASE_H

typedef struct
{
    void *buffer;
    unsigned long length;
} QUERY_VAR;

void add_score_db(char*, int);

void get_score_db();

#endif  // _DATABASE_H
