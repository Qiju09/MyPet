#pragma once
#include <SDL3/SDL.h>
#include <string>
class Pet {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    std::string window_name = "MyPet";
    SDL_Texture* texture = NULL;
	struct Size {
        Size();
		float w = 0;
		float h = 0;
	};
public:
    Pet();
    Pet(SDL_Window* window, SDL_Renderer* renderer);
    bool setWindowName(std::string name);
    std::string getWindowName()const;
    bool setWindowShape(SDL_Surface* surf);
    bool setTexture(SDL_Surface* surf);
    bool setPNG(std::string direct);
    SDL_Window* getWindow()const;
    SDL_Renderer* getRenderer()const;
    SDL_Texture* getTexture()const;
    Size size{};
    SDL_FRect rect{};

    class ErrorPet {
        std::string errMessage;
    public:
        ErrorPet(std::string message) :errMessage(message) {}
        std::string getErrMessage()const;
    };
};