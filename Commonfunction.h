#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include <windows.h>
#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
static SDL_Window* g_windows = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// Screen
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int Render_Draw_Color = 0xff;

#define TITLE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define Player_Title 0

typedef struct Input
{
    int left_;
    int right_;
    int down_;
    int up_;
    int jump_;
};
typedef struct Map
{
  int start_x;
  int start_y;

  int max_x;
  int max_y;

  int title[MAX_MAP_Y][MAX_MAP_X];
  char* file_name;
};
class Commonfunction
{
    public:
        Commonfunction();
        virtual ~Commonfunction();

    protected:

    private:
};



#endif // COMMONFUNCTION_H
