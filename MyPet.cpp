#define SDL_MAIN_USE_CALLBACKS 1   /* использовать коллбэки вместо main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include "Pet.h"

SDL_AppResult  SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Не удалось инициализировать SDL:  %s ", SDL_GetError());
        return  SDL_APP_FAILURE;
    }
    try {
        Pet* pet = (Pet*)SDL_calloc(1, sizeof(Pet));
        if (!pet) {
			return SDL_APP_FAILURE;
        }
        *pet = Pet();
        *appstate = pet;
        if (!pet->setPNG("C:\\Users\\ЕГМПГЕВАВААжэюЬИМРМИ\\source\\repos\\MyLilit\\nya.png")) {
            throw Pet::ErrorPet("PNG not loaded");
        }
        SDL_SetRenderLogicalPresentation(pet->getRenderer(), pet->size.w, pet->size.h, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }
    catch (Pet::ErrorPet& e) {
		std::cerr << e.getErrMessage() << std::endl;
        return  SDL_APP_FAILURE;
    }

    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется при возникновении нового события (ввод мыши, нажатия клавиш и т. д.). */
SDL_AppResult  SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->key.key == SDLK_ESCAPE) {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_QUIT) {
        return  SDL_APP_SUCCESS;   
    }
    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется один раз за кадр и является ядром программы. */
SDL_AppResult  SDL_AppIterate(void* appstate)
{
    Pet* pet;
    try {
        pet = static_cast<Pet*>(appstate);
    }
    catch (std::bad_alloc) {
		std::cerr << "Error read pet" << std::endl;
		return SDL_APP_FAILURE;
    }
    SDL_RenderClear(pet->getRenderer());

    SDL_RenderTexture(pet->getRenderer(), pet->getTexture(), NULL, &pet->rect);
    SDL_RenderPresent(pet->getRenderer());

    return  SDL_APP_CONTINUE;   /* продолжить выполнение программы! */
}

/* Эта функция выполняется один раз при завершении работы. */
void  SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL очистит окно/рендерер за нас. */
}