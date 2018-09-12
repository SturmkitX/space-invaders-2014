#include "body.h"

Body::Body()
{
    rect.x = rect.y = rect.w = rect.h = 0;
    texture = NULL;
    rotation = 0.0;
    center.x = center.y = 0;
    flip = SDL_FLIP_NONE;
}

Body::~Body()
{
    //
}

void Body::create(SDL_Renderer* rnd, char *path)
{
    //The surface
    SDL_Surface* orig = IMG_Load( path );

    //Convert to texture
    texture = SDL_CreateTextureFromSurface( rnd, orig );
    SDL_QueryTexture( texture, NULL, NULL, &(rect.w), &(rect.h) );

    //Delete old surface
    SDL_FreeSurface( orig );
}

void Body::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
}

void Body::setRect(int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Body::setRect(SDL_Rect* r2)
{
    rect = *r2;
}

SDL_Rect* Body::getRect()
{
    return &rect;
}

int Body::getX()
{
    return rect.x;
}

int Body::getY()
{
    return rect.y;
}

void Body::setX(int x)
{
    rect.x = x;
}

void Body::setY(int y)
{
    rect.y = y;
}

void Body::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Body::translate(int x, int y)
{
    rect.x += x;
    rect.y += y;
}

int Body::getWidth()
{
    return rect.w;
}

int Body::getHeight()
{
    return rect.h;
}

void Body::render(SDL_Renderer* rnd)
{
    SDL_RenderCopyEx( rnd, texture, NULL, &rect, rotation, &center, flip );
}

void Body::render(SDL_Renderer* rnd, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopyEx( rnd, texture, src, dst, rotation, &center, flip );
}

void Body::setRotation( double ro )
{
    rotation = ro;
}

double Body::getRotation()
{
    return rotation;
}

void Body::rotateIt( double ro )
{
    rotation += ro;
}

SDL_Texture* Body::getTexture()
{
    return texture;
}

void Body::setCenter( int x, int y )
{
    center.x = x;
    center.y = y;
}

void Body::setCenter( SDL_Point* p )
{
    center = *p;
}

SDL_Point* Body::getCenter()
{
    return &center;
}

void Body::setTexture( SDL_Texture* tex )
{
    texture = tex;
}
