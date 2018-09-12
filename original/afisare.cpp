#include "levels.h"
#include <cstdio>
#include <windows.h>
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

    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = "open";
    ShExecInfo.lpFile = "conus.jar";
    ShExecInfo.lpParameters = comanda.str().c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
    //execl("conus.jar", comanda.str().c_str(), 0);
}
