#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "Commonfunction.h"
#include "BaseObject.h"

#define Gravity 0.8
#define Max_Fall_Speed 10
#define Player_Speed 8
class MainObject : public BaseObject
{
    public:
        MainObject();
        ~MainObject();

    enum WalkType
    {
        Walk_Right = 0,
        Walk_Left = 1,
    };
    bool LoadImg(std :: string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void Set_clips();

    void DoPlayer(Map& map_data);
    void Check_To_Map(Map& map_data);
    protected:

    private:
        float x_val_;
        float y_val_;

        float x_pos;
        float y_pos;

        int width_frame_;
        int height_frame_;
        SDL_Rect frame_clip_[8];
        Input input_type_;
        int frame_;
        int status_;
        bool on_ground;
};

#endif // MAINOBJECT_H
