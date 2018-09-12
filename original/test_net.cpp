#include "levels.h"
#include <SDL_net.h>
#include <cstdio>
#include <cstring>

int prepareServer( IPaddress* ip )
{
    int result;
    result = SDLNet_ResolveHost( ip, NULL, 5678 );

    return result;
}

int prepareClient( IPaddress* ip )
{
    int result;
    result = SDLNet_ResolveHost( ip, "localhost", 5678 );

    return result;
}

void serverBehave( IPaddress* ip )
{
    TCPsocket meSock, outSock;
    outSock = NULL;
    meSock = SDLNet_TCP_Open( ip );

    while( !outSock )
    {
        outSock = SDLNet_TCP_Accept( meSock );
    }

    int l;
    char msg[] = "Ce faci ma cretinule?\n";
    l = strlen( msg ) + 1;
    SDLNet_TCP_Send( outSock, msg, l );

    SDLNet_TCP_Recv( outSock, msg, l );
    printf( "%s\n", msg );

    SDLNet_TCP_Close( outSock );
    SDLNet_TCP_Close( meSock );
}

void clientBehave(IPaddress* ip)
{
    TCPsocket outSock;
    outSock = SDLNet_TCP_Open( ip );

    int l = 30;
    char msg[20];

    SDLNet_TCP_Recv( outSock, msg, l );
    printf( "%s\n", msg );

    strcpy( msg, "Bine ba\n" );
    l = strlen( msg ) + 1;

    SDLNet_TCP_Send( outSock, msg, l );

    SDLNet_TCP_Close( outSock );
}

void test_net(Screen* mScreen, bool isServer)
{
    SDL_Renderer* rnd = mScreen->getRenderer();
    bool quit = false;
    SDL_Event e;

    /*************************
    *
    * Elemente de networking
    *
    *************************/

    IPaddress ip;
    if( isServer == true )
    {
        if( prepareServer( &ip ) == -1 )
        {
            printf( "Server creation error: %s\n", SDLNet_GetError() );
        }
    }
    else
    {
        if( prepareClient( &ip ) == -1 )
        {
            printf( "Server creation error: %s\n", SDLNet_GetError() );
        }
    }

    printf( "Server/Client creat cu succes\n" );

    /****************************
    *
    *
    ****************************/

    if( isServer == true )
    {
        serverBehave( &ip );
    }
    else
    {
        clientBehave( &ip );
    }

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }

    rnd = NULL;
}
