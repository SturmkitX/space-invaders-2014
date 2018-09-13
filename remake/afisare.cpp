#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <mysql.h>

#include "database.h"

MYSQL* connect_to_database()
{
    MYSQL *session = mysql_init(NULL);
    MYSQL *sess2 = mysql_real_connect( session, "localhost", "nava_app", "iamnava", "javau", 
        3306, NULL, CLIENT_IGNORE_SPACE );

    if (sess2 == NULL)
    {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(session));
        mysql_close(session);
    }
    else
    {
        fprintf(stderr, "Successfully connected to DB\n");
    }
        
    session = sess2;
    
    return session;
}

QUERY_VAR* execute_statement(const char *query, const QUERY_VAR *vars)
{
    MYSQL *session = connect_to_database();
    if (session == NULL)
    {
        return NULL;
    }

    MYSQL_STMT *stmt = mysql_stmt_init( session );
    if (stmt == NULL)
    {
        fprintf(stderr, "Error creating prepared statement: %s\n", mysql_error(session));
        return NULL;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
    {
        fprintf(stderr, "Error preparing statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        return NULL;
    }

    int args = mysql_stmt_param_count( stmt );
    MYSQL_BIND *binds = (MYSQL_BIND*) malloc( args * sizeof(MYSQL_BIND) );
    if (binds == NULL)
    {
        fprintf(stderr, "Error allocating memory for binds structure: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        return NULL;
    }

    for (int i=0; i<args; i++)
    {
        binds[i].buffer = vars[i].buffer;
        binds[i].buffer_length = vars[i].length;
    }

    if (mysql_stmt_bind_param( stmt, binds ) != 0)
    {
        fprintf(stderr, "Error binding params for statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        free( binds );
        return NULL;
    }

    if (mysql_stmt_execute( stmt ) != 0)
    {
        fprintf(stderr, "Error executing prepared statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        free( binds );
        return NULL;
    }

    if (mysql_stmt_store_result( stmt ) != 0)
    {
        fprintf(stderr, "Error storing results for prepared statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        free( binds );
        return NULL;
    }

    free( binds );
    args = mysql_stmt_field_count( stmt );
    binds = (MYSQL_BIND*) malloc( args * sizeof(MYSQL_BIND) );

    QUERY_VAR *results = (QUERY_VAR*) malloc( sizeof(QUERY_VAR) * mysql_stmt_row_count( stmt ) * args + 1 );
    int index = 0;
    if (mysql_stmt_bind_result( stmt, binds ) != 0)
    {
        fprintf(stderr, "Error binding results for statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close( stmt );
        free( binds );
        return NULL;
    }

    while ( mysql_stmt_fetch( stmt ) == 0 )
    {
        for (int i=0; i<args; i++)
        {
            results[index + i].buffer = binds[i].buffer;
            results[index + i].length = binds[i].buffer_length;
        }
        index += args;
    }

    // mark the end of the array
    results[index].buffer = NULL;
    results[index].length = 0;

    free ( binds );
    mysql_stmt_free_result( stmt );
    mysql_stmt_close( stmt );
    mysql_close( session );

    return results;
}

void add_score_db(char* nick, int score)
{
    // add a (name, score) pair to the persons table
    MYSQL *session = connect_to_database();
    if (session == NULL)
    {
        return;
    }
    
    mysql_close(session);
}

void get_score_db()
{
    
    // get the highest 8 scores from the table
    MYSQL *session = connect_to_database();
    if (session == NULL)
    {
        return;
    }

    MYSQL_STMT *stmt = mysql_stmt_init( session );
    if (stmt == NULL)
    {
        fprintf(stderr, "Error creating prepared statement: %s\n", mysql_error(session));
    }

    

    mysql_close(session);
}
