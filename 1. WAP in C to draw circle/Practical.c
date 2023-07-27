#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Function to draw a pixel on the SDL window
void drawPixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

// Function to draw a circle using Bresenham's Circle Drawing Algorithm
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        drawPixel(renderer, centerX + x, centerY + y);
        drawPixel(renderer, centerX - x, centerY + y);
        drawPixel(renderer, centerX + x, centerY - y);
        drawPixel(renderer, centerX - x, centerY - y);
        drawPixel(renderer, centerX + y, centerY + x);
        drawPixel(renderer, centerX - y, centerY + x);
        drawPixel(renderer, centerX + y, centerY - x);
        drawPixel(renderer, centerX - y, centerY - x);

        if (d < 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window
    window = SDL_CreateWindow("Circle Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Set renderer color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear the window
    SDL_RenderClear(renderer);

    // Set renderer color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw a circle
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = 100;
    drawCircle(renderer, centerX, centerY, radius);

    // Update the renderer
    SDL_RenderPresent(renderer);

    // Wait for user exit
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
