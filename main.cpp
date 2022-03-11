#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Commonfunction.h"
#include "BaseObject.h"
#include "Game_map.h"
#include "MainObject.h"

BaseObject g_background;
bool initData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
   g_windows = SDL_CreateWindow("Game CPP",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
   if (g_windows == NULL)
   {
       success = false;
   }
   else
   {
       g_screen = SDL_CreateRenderer(g_windows,-1,SDL_RENDERER_ACCELERATED);
       if (g_screen == NULL)
       {
           success = false;
       }
       else
       {
           SDL_SetRenderDrawColor(g_screen,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
           int imgFlags = IMG_INIT_PNG;
           if( !(IMG_Init(imgFlags)) && imgFlags)
             success = false;
       }
   }
   return success;
}

bool LoadBackGround()
{
    bool ret = g_background.LoadImg("Img//background.png",g_screen);
    if (ret == false)
        return false;
    return true;
}
void Close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_windows);
    g_windows = NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{
    if (initData() == false)
        return - 1;
    if (LoadBackGround() == false)
        return -1;


    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("Img//player_right.png",g_screen);
    p_player.Set_clips();

    bool is_quit = false;
    while (!is_quit)
    {
        while(SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event,g_screen);
        }
        SDL_SetRenderDrawColor(g_screen,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen,NULL);
        game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();

        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        SDL_RenderPresent(g_screen);
    }

    Close();
    return 0;
}

