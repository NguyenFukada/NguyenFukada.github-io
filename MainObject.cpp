#include "MainObject.h"

MainObject::MainObject()
{
    //ctor
    frame_ = 0;
    x_pos = 0;
    y_pos = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    on_ground = false;
}

MainObject::~MainObject()
{
    //dtor

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret == true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }
    return ret;
}
void MainObject::Set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2*width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3*width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4*width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5*width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6*width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7*width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;



    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if (status_ == Walk_Left)
    {
        LoadImg("Img//player_left.png",des);
    }
    else
    {
        LoadImg("Img//player_right.png",des);
    }

    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else
        {
            frame_ = 0 ;
        }

    if (frame_ >= 8) {frame_ = 0;}

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_obeject_,current_clip,&renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = Walk_Right;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = Walk_Left;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
          switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = Walk_Right;
                input_type_.right_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = Walk_Left;
                input_type_.left_ = 0;
            }
            break;
        }
    }
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val_ = 0;
    y_val_ += 0.8;

    if(y_val_ >= Max_Fall_Speed)
        {y_val_ = Max_Fall_Speed;}
    if(input_type_.left_ == 1)
    {
        x_val_ -= Player_Speed;
    }
    else if (input_type_.right_ == 1)
    {
        x_val_ += Player_Speed;
    }

    Check_To_Map(map_data);
}

void MainObject::Check_To_Map(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 =0;
    int y2 =0;

    // Check horizontal
    int height_min = height_frame_ < TITLE_SIZE ? height_frame_ : TITLE_SIZE;

    x1 = (x_pos + x_val_)/TITLE_SIZE;
    x2 = (x_pos + x_val_ + width_frame_-1)/TITLE_SIZE;

    y1 = (y_pos)/TITLE_SIZE;
    y2 = (y_pos + height_min-1)/TITLE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // mian object is moving to right
        {
            if (map_data.title[y1][x2] != Player_Title  || map_data.title[y2][x2] != Player_Title)
            {
                x_pos = x2*TITLE_SIZE;
                x_pos -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.title[y1][x1] != Player_Title || map_data.title[y2][x1] != Player_Title)
            {
                x_pos = (x1+1)*TITLE_SIZE;
                x_val_ = 0;
            }
        }
    }

    // Check Vertical

    int width_min = width_frame_ < TITLE_SIZE ? width_frame_ : TITLE_SIZE;
    x1 = (x_pos)/TITLE_SIZE;
    x2 = (x_pos + width_min)/TITLE_SIZE;

    y1 = (y_pos + y_val_)/TITLE_SIZE;
    y2 = (y_pos + y_val_ + height_frame_ -1)/TITLE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            if (map_data.title[y2][x1] != Player_Title  || map_data.title[y2][x2] != Player_Title)
            {
                y_pos = y2*TITLE_SIZE;
                y_pos -= (height_frame_+1);
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            if (map_data.title[y1][x1] != Player_Title  || map_data.title[y1][x2] != Player_Title)
            {
                y_pos = (y1+1)*TITLE_SIZE;
                y_val_ = 0;
            }
        }
    }


    x_pos += x_val_;
    y_pos = y_val_;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + width_frame_ > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame_ -1;
    }
}
