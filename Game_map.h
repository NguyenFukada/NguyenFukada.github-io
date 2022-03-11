#ifndef GAME_MAP_H
#define GAME_MAP_H
#define MAX_TITLE 20
#include "Commonfunction.h"
#include "BaseObject.h"

class titleMap: public BaseObject
{
public:
    titleMap() {;}
    ~titleMap() {;}

};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;};
private:
    Map game_map_;
    titleMap title_map[MAX_TITLE];
};
class Game_map
{
    public:
        Game_map();
        virtual ~Game_map();

    protected:

    private:
};

#endif // GAME_MAP_H
