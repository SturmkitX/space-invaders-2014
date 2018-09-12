#include "levels.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>

void rezultate(int tip, char* nick, int score)
{
    std::stringstream comanda;
    if( tip == 1 )
    {
        //operatie de adaugare
        comanda << "add ";
        comanda << nick << ' ';
        comanda << score;
        comanda << '\n';
        //printf( "%s", comanda.str().c_str() );

        //ShellExecute( NULL, "open", "conus.jar", comanda.str().c_str(), NULL, SW_HIDE );
    }
    else
    {
        //operatie de extragere
        comanda << "get ";
        comanda << score;
        comanda << '\n';

        //ShellExecute( NULL, "open", "conus.jar", comanda.str().c_str(), NULL, SW_HIDE );
    }

    char params[100];
    sprintf(params, "java -jar conus.jar %s", comanda.str().c_str());
    system(params);
}
