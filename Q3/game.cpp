#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool running = true;

void initializeSDL()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Prompackman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void shutdownSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void updateGame()
{
    // Update game logic here
}

void renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game graphics here

    SDL_RenderPresent(renderer);
}

int main()
{
    initializeSDL();

    while (running)
    {
        handleInput();
        updateGame();
        renderGame();
    }

    shutdownSDL();
    return 0;
}
