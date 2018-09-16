#include <mysql.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_NAME_LEN 45

int main()
{
	MYSQL *session = mysql_init(NULL);
	session = mysql_real_connect( session, "localhost", "nava_app", "iamnava", "javau", 3306, NULL, CLIENT_IGNORE_SPACE );

	printf("%d\n", session == NULL);

	const char *query = "SELECT Name, Age FROM persons ORDER BY Age DESC LIMIT 8";
	printf("%d %s\n", mysql_real_query( session, query, strlen(query) ), mysql_error( session ) );

	MYSQL_RES *res_buff = mysql_store_result( session );	// NULL in case of error or no data returned
	MYSQL_ROW row;

	while ( row = mysql_fetch_row( res_buff ) )
	{
		printf( "%s %d\n", row[0], atoi(row[1]) );
	}

	mysql_free_result( res_buff );
	mysql_close( session );
	mysql_server_end();

	return 0;
}
