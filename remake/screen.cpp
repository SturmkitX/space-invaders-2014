#include "screen.h"
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>

Screen::Screen()
{
    mWindow = NULL;
    mRenderer = NULL;
    bgMusic = NULL;

    DEF_W = 800;
    DEF_H = 600;
    force_quit = false;
    fullScreenActive = last_screen_switch = 0;
}

Screen::~Screen()
{
    //momentan nimic
}

bool Screen::init()
{
    int initflag1, initflag2;

    //Init SDL video and sound
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL Init Error %s\n", SDL_GetError() );
        return false;
    }

    //Init image
    initflag1 = IMG_INIT_PNG | IMG_INIT_JPG;
    initflag2 = IMG_Init( initflag1 );

    if( (initflag1 & initflag2) != initflag1 )
    {
        printf( "PNG and JPG Init Fail %s\n", IMG_GetError() );
        return false;
    }

    //Init mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf( "Mixer Init Fail %s\n", Mix_GetError() );
        return false;
    }

    //Init mixer support (if necessary)
    initflag1 = MIX_INIT_MP3 | MIX_INIT_OGG;
    initflag2 = Mix_Init( initflag1 );

    if( (initflag1 & initflag2) != initflag1 )
    {
        printf( "MP3 and OGG support Init fail %s\n", Mix_GetError() );
        return 0;
    }

    //Init TTF
    if( TTF_Init() < 0 )
    {
        printf( "TTF Init Fail: %s\n", TTF_GetError() );
        return false;
    }

    //Init network
    if( SDLNet_Init() < 0 )
    {
        printf( "Network Init Fail %s\n", SDLNet_GetError() );
        return false;
    }

    //Get window
    SDL_GetDesktopDisplayMode( 0, &display );
    DESK_W = display.w;
    DESK_H = display.h;

    mWindow = SDL_CreateWindow( "Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, DEF_W, DEF_H,
                               SDL_WINDOW_SHOWN );

    if( mWindow == NULL )
    {
        printf("mWindow Init is NULL\n");
        return false;
    }

    //Get renderer
    mRenderer = SDL_GetRenderer( mWindow );
    if( mRenderer )
    {
        SDL_DestroyRenderer( mRenderer );
    }

    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_PRESENTVSYNC );
    if( mRenderer == NULL )
    {
        printf("mRenderer Init is NULL: %s\n", SDL_GetError());
        return false;
    }


    return true;
}

void Screen::close()
{
    //Destroy everything
    SDL_DestroyRenderer( mRenderer );
    SDL_DestroyWindow( mWindow );

    mWindow = NULL;
    mRenderer = NULL;

    Mix_CloseAudio();
    Mix_Quit();
    SDLNet_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

SDL_Window* Screen::getWindow()
{
    return mWindow;
}

SDL_Renderer* Screen::getRenderer()
{
    return mRenderer;
}

int Screen::getDesktopWidth()
{
    return DESK_W;
}

int Screen::getDesktopHeight()
{
    return DESK_H;
}

char* Screen::getPlayer()
{
    return playerName;
}

void Screen::setMusic()
{
    bgMusic = Mix_LoadMUS( "media/d_victor.mid" );
    Mix_PlayMusic( bgMusic, -1 );
}

void Screen::freeMusic()
{
    Mix_FreeMusic( bgMusic );
    music_path.clear();
}

void Screen::detect_music()
{
    DIR *dir;
    dirent *file_data;
    std::string nume_fisier, nume_complet;
    bool e_fisier;

    dir = opendir("muzica");
    if(dir == NULL)
    {
        printf( "Nu exista fisiere!\n" );
    }

    while(file_data = readdir(dir))
    {
        nume_fisier = file_data->d_name;
        nume_complet = "muzica/" + nume_fisier;
        e_fisier = file_data->d_type == DT_REG || file_data->d_type == DT_LNK;

        if(e_fisier && strcmp(nume_fisier.c_str(), "sound.ogg")
                        && (strstr(nume_fisier.c_str(), ".ogg") ||
                           strstr(nume_fisier.c_str(), ".wav") ||
                           strstr(nume_fisier.c_str(), ".mid") ||
                            strstr(nume_fisier.c_str(), ".mp3")))
        {
            music_path.push_back(nume_complet);
        }
    }

    closedir(dir);

    total_songs = music_path.size();
    printf("Music size: %d\n", music_path.size());
    for( int i=0; i<music_path.size(); i++ )
    {
        fprintf(stderr, "Music name: %s\n", music_path[i].c_str());
    }
    curr_song = 0;
    last_changed_mus = -5000;
    mus_volume = 90;
}

void Screen::switch_song(int valus)
{
    if( SDL_GetTicks() - last_changed_mus < 3000 ) return;

    curr_song += valus;

    if(curr_song == -1)
    {
        curr_song = total_songs - 1;
    }
    else
    if(curr_song == total_songs)
    {
        curr_song = 0;
    }

    printf( "%s\n", music_path[curr_song].c_str() );

    Mix_HaltMusic();
    Mix_FreeMusic( bgMusic );

    bgMusic = Mix_LoadMUS( music_path[curr_song].c_str() );
    Mix_PlayMusic( bgMusic, -1 );

    last_changed_mus = SDL_GetTicks();
}

void Screen::increaseVolume(int valus)
{
    mus_volume += valus;

    if(mus_volume < 0)
    {
        mus_volume = 0;
    }
    else
    if(mus_volume > 100)
    {
        mus_volume = 100;
    }

    printf( "Volum: %d\n", mus_volume );

    Mix_VolumeMusic( mus_volume );
}

void Screen::switchFullscreen()
{
    if( SDL_GetTicks() - last_screen_switch < 8000 ) return;

    if( fullScreenActive == 0 )
    {
        fullScreenActive = SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        fullScreenActive = 0;
    }

    SDL_SetWindowFullscreen( mWindow, fullScreenActive );
    last_screen_switch = SDL_GetTicks();
}
