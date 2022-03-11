#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_obeject_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    //dtor
}
bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
        if (load_surface != NULL)
        {
            SDL_SetColorKey(load_surface, SDL_TRUE,SDL_MapRGB(load_surface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
            new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
            if (new_texture != NULL)
            {
                rect_.w = load_surface->w;
                rect_.h = load_surface->h;
            }
            SDL_FreeSurface(load_surface);
        }
    p_obeject_ = new_texture;
    return p_obeject_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des, p_obeject_,clip, &renderquad);
}
 void BaseObject::Free()
 {
     if (p_obeject_  != NULL)
     {
         SDL_DestroyTexture(p_obeject_);
         p_obeject_ = NULL;
         rect_.w = 0;
         rect_.h = 0;
     }
 }
