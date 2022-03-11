#include "Game_map.h"
#include "Commonfunction.h"
void GameMap::LoadMap(char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name,"rb");
    if (fp == NULL)
    {
        return;
    }

    game_map_.max_x = 0;
    game_map_.max_y = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for ( int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp,"%d",&game_map_.title[i][j]);
            int val = game_map_.title[i][j];
            if (val > 0)
            {
                if (j > game_map_.max_x)
                {
                    game_map_.max_x = j;
                }

                if (i > game_map_.max_y)
                {
                    game_map_.max_y = i;
                }
            }
        }
    }

    game_map_.max_x = (game_map_.max_x+1)*TITLE_SIZE;
    game_map_.max_y = (game_map_.max_y+1)*TITLE_SIZE;

    game_map_.start_x = 0;
    game_map_.start_y = 0;

    game_map_.file_name = name;
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TITLE;i++)
    {
        sprintf_s(file_img,"map/%d.png",i);

        fopen_s(&fp,file_img,"rb");
        if (fp == NULL)
        {
            continue;
        }

        fclose(fp);

        title_map[i].LoadImg(file_img,screen);
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x/TITLE_SIZE;
    x1 = (game_map_.start_x%TITLE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0: TITLE_SIZE);


    map_y = game_map_.start_y/TITLE_SIZE;
    y1 = (game_map_.start_x%TITLE_SIZE)*-1;
    y2 = y1+SCREEN_HEIGHT + (y1 == 0 ? 0 : TITLE_SIZE);

    for (int i = y1; i < y2 ; i += TITLE_SIZE)
    {
        map_x = game_map_.start_x/TITLE_SIZE;
        for (int j = x1; j < x2; j += TITLE_SIZE)
        {
            int val = game_map_.title[map_y][map_x];
            if (val > 0)
            {
                title_map[val].SetRect(j,i);
                title_map[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
Game_map::Game_map()
{
    //ctor
}

Game_map::~Game_map()
{
    //dtor
}
