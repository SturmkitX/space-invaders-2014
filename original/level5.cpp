#include "levels.h"
#include "body.h"

void level5(Screen* mScreen)
{
    SDL_Renderer* rnd = mScreen->getRenderer();
    SDL_Surface* textSurface;
    TTF_Font* font;
    bool quit = false;
    SDL_Event e;
    SDL_Color color;
    SDL_Point p;
    SDL_Rect textDim;
    SDL_Texture* text;
    Body host, client;
    bool toRender = true;

    host.create( rnd, "media/host.png" );
    client.create( rnd, "media/client.png" );
    font = TTF_OpenFont( "media/font.ttf", 36 );
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;

    host.setPosition( 20, 300 );
    client.setPosition( 300, 300 );
    textSurface = TTF_RenderText_Solid( font, "Apasa pe un buton", color );
    text = SDL_CreateTextureFromSurface( rnd, textSurface );
    SDL_QueryTexture( text, NULL, NULL, &(textDim.w), &(textDim.h) );
    textDim.x = 50;
    textDim.y = 250;

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else
            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState( &(p.x), &(p.y) );

                if( p.x>host.getX() && p.x<host.getX()+host.getWidth() )
                {
                    if(p.y>host.getY() && p.y<host.getY() + host.getHeight())
                    {
                        textSurface = TTF_RenderText_Solid( font, "Host e apasat", color );
                        text = SDL_CreateTextureFromSurface( rnd, textSurface );
                        SDL_QueryTexture( text, NULL, NULL, &(textDim.w), &(textDim.h) );

                        nave_net( mScreen, 1 );
                        toRender = true;
                    }
                }
                else
                if( p.x>client.getX() && p.x<client.getX()+client.getWidth() )
                {
                    if(p.y>client.getY() && p.y<client.getY() + client.getHeight())
                    {
                        textSurface = TTF_RenderText_Solid( font, "Client e apasat", color );
                        text = SDL_CreateTextureFromSurface( rnd, textSurface );
                        SDL_QueryTexture( text, NULL, NULL, &(textDim.w), &(textDim.h) );

                        nave_net( mScreen, 2 );
                        toRender = true;
                    }
                }
            }
        }

        if( toRender )
        {
            SDL_RenderClear( rnd );
            host.render( rnd );
            client.render( rnd );
            SDL_RenderCopy( rnd, text, NULL, &textDim );

            SDL_RenderPresent( rnd );

            toRender = false;
        }
    }

    host.free();
    client.free();
    TTF_CloseFont( font );
    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( text );
    rnd = NULL;
}
