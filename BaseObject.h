#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "Commonfunction.h"


class BaseObject
{
    public:
        BaseObject();
        virtual ~BaseObject();
    void SetRect(const int& x, const int& y) {rect_.x = x,rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_obeject_;}


    virtual bool LoadImg(std::string path, SDL_Renderer* Screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
    protected:
       SDL_Texture* p_obeject_;
       SDL_Rect rect_;
    private:
};

#endif // BASEOBJECT_H
