#define SDL_MAIN_USE_CALLBACKS 1   /* использовать коллбэки вместо main() */
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h>
#include <iostream>

/* Мы будем использовать этот рендерер для отрисовки в этом окне каждый кадр. */
static  SDL_Window* window = NULL;
static  SDL_Renderer* renderer = NULL;
SDL_Surface* surf = NULL;
SDL_Texture* texture = NULL;
SDL_FRect rect;
bool button_down{ false };
float w, h;
float mouse_x, mouse_y;
float start_mouse_x, start_mouse_y;
bool mouse_in_window{ false };
//SDL_DisplayID* DM;
//int num_display;
Uint64 last_step = 0;

/* Эта функция выполняется один раз при запуске. */
SDL_AppResult  SDL_AppInit(void** appstate, int argc, char* argv[])
{
   // int i;
   // DM = SDL_GetDisplays(&num_display);
   // SDL_DisplayMode *dispMod = SDL_GetDesktopDisplayMode(*DM);
    SDL_SetAppMetadata("Пример примитивов рендерера", "1.0", "com.example.renderer-primitives");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Не удалось инициализировать SDL:  %s ", SDL_GetError());
        return  SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("MyLilit", 400, 400, SDL_WINDOW_TRANSPARENT|SDL_WINDOW_BORDERLESS|SDL_WINDOW_ALWAYS_ON_TOP, &window, &renderer)) {
        SDL_Log("Не удалось создать окно/рендерер:  %s ", SDL_GetError());
        return  SDL_APP_FAILURE;
    }
    surf = SDL_LoadPNG("nya.png");
    if (surf==NULL) {
        SDL_Log("Не удалось открыть пнг: %s ", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == NULL) {
        SDL_Log("Не удалось создать текстуру: %s ", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_GetTextureSize(texture, &w, &h);
    SDL_SetWindowSize(window, w, h);
    SDL_SetWindowShape(window, surf);
    SDL_DestroySurface(surf);

    rect = { 0,0,w,h };

    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется при возникновении нового события (ввод мыши, нажатия клавиш и т. д.). */
SDL_AppResult  SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->key.key == SDLK_ESCAPE) {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_QUIT) {
        return  SDL_APP_SUCCESS;   /* завершить программу, сообщив об успехе операционной системе. */
    }
    if (event->button.button == SDL_BUTTON_LEFT && event->button.down) {
        button_down = true;
        SDL_GetMouseState(&start_mouse_x, &start_mouse_y);
    }
    if (event->button.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        button_down = false;
        mouse_in_window = false;
    }
    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется один раз за кадр и является ядром программы. */
SDL_AppResult  SDL_AppIterate(void* appstate)
{
    SDL_RenderClear(renderer);
    
    const Uint64 now = SDL_GetTicks();
    Uint64 time = now - last_step;
    last_step = now;

    int win_x, win_y;
    SDL_GetWindowPosition(window,&win_x, &win_y);
    if (button_down) {
        SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
        if (mouse_x >= win_x && mouse_x <= win_x + w && mouse_y > win_y && mouse_y <= win_y + h) {
            mouse_in_window = true;
        }
        if (mouse_in_window) {
            SDL_SetWindowPosition(window, mouse_x - start_mouse_x, mouse_y - start_mouse_y);
        }
    }
  //  else if(win_x<)
    SDL_RenderTexture(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);   /* вывести всё на экран! */

    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется один раз при завершении работы. */
void  SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL очистит окно/рендерер за нас. */
}