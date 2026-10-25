#include <SDL3/SDL.h>
#include <string>
#include "Pet.h"

Pet::Pet() {
    if (!SDL_CreateWindowAndRenderer(window_name.c_str(), 400, 400, SDL_WINDOW_TRANSPARENT | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP, &window, &renderer)) {
        throw ErrorPet("Window or Renderer not create");
    }
}

Pet::Pet(SDL_Window* window, SDL_Renderer* renderer) :window{ window }, renderer{ renderer } {}

std::string Pet::ErrorPet::getErrMessage()const {
    if (!errMessage.empty()) {
        return errMessage;
    }
    else return "Not Error";
}
bool Pet::setWindowName(std::string name) {
    if (name.empty()) {
        throw ErrorPet("Name is empty");
        return false;
    }
    else {
        window_name = name;
        SDL_SetWindowTitle(window, window_name.c_str());
    }
    return true;
}
bool Pet::setTexture(SDL_Surface* surf) {
    if (surf == NULL) {
        throw ErrorPet("Surface is NULL");
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            throw ErrorPet("Texture not created");
        }
        else {
			SDL_GetTextureSize(texture, &size.w, &size.h);
			rect = { 0,0,size.w,size.h };
			SDL_SetWindowSize(window, size.w, size.h);
            return true;
        }
    }
}
bool Pet::setPNG(std::string direct) {
    if (direct.empty()) {
        throw ErrorPet("Directory is empty");
    }
    else {
        SDL_Surface* surface = NULL;
        surface = SDL_LoadPNG(direct.c_str());
        if (surface == NULL) {
            throw ErrorPet("PNG not loaded");
        }
        if (!setTexture(surface)) {
			throw ErrorPet("Texture not set");
        }
        if (!setWindowShape(surface)) {
            throw ErrorPet("Window shape not set");
        }
        SDL_DestroySurface(surface);
    }
    return true;
}
bool Pet::setWindowShape(SDL_Surface* surf) {
    if (surf == NULL) {
        throw ErrorPet("Surface is NULL");
    }
    else {
        if (SDL_SetWindowShape(window, surf)) {
            return true;
        }
        else {
            throw ErrorPet("Window shape not set");
        }
    }
}

SDL_Window* Pet::getWindow()const { return window; }
SDL_Renderer* Pet::getRenderer()const { return renderer; }
SDL_Texture* Pet::getTexture()const { return texture; }
std::string Pet::getWindowName()const { return window_name; }

Pet::Size::Size() :w{0}, h{0} {}