#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <mysql.h>

#include "database.h"

int add_score_db(char* nick, int score)
{
	// add a (name, score) pair to the persons table
	MYSQL *session = mysql_init(NULL);
	session = mysql_real_connect( session, "localhost", "nava_app", "iamnava", 
		"javau", 3306, NULL, CLIENT_IGNORE_SPACE );

	char query[100];
	sprintf( query, "INSERT INTO persons (Name, Age) VALUES (\'%s\', %d)", nick, score );
	mysql_real_query( session, query, strlen(query) );

	int affected = mysql_affected_rows( session );

	mysql_close( session );
	mysql_server_end();

	return affected;
}

SCORE_ARRAY* get_score_db()
{
	// get the highest 8 scores from the table
	MYSQL *session = mysql_init(NULL);
	session = mysql_real_connect( session, "localhost", "nava_app", "iamnava", 
		"javau", 3306, NULL, CLIENT_IGNORE_SPACE );

	const char *query = "SELECT Name, Age FROM persons ORDER BY Age DESC LIMIT 8";
	mysql_real_query( session, query, strlen(query) );

	MYSQL_RES *res_buff = mysql_store_result( session );	// NULL in case of error or no data returned
	MYSQL_ROW row;

	SCORE_ARRAY *scores = (SCORE_ARRAY*) malloc( sizeof(SCORE_ARRAY) );
	scores->size = mysql_num_rows( res_buff );
	scores->data = (SCORE_VAR*) malloc( sizeof(SCORE_VAR) * scores->size );

	for ( int i=0; i < scores->size; i++ )
	{
		row = mysql_fetch_row( res_buff );
		strcpy( scores->data[i].name, row[0] );
		scores->data[i].score = atoi( row[1] );
	}

	mysql_free_result( res_buff );
	mysql_close( session );
	mysql_server_end();

	return scores;
}
