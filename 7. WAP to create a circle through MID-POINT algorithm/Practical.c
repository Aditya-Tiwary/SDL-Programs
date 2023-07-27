#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void drawPixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        drawPixel(renderer, centerX + x, centerY + y);
        drawPixel(renderer, centerX + y, centerY + x);
        drawPixel(renderer, centerX - y, centerY + x);
        drawPixel(renderer, centerX - x, centerY + y);
        drawPixel(renderer, centerX - x, centerY - y);
        drawPixel(renderer, centerX - y, centerY - x);
        drawPixel(renderer, centerX + y, centerY - x);
        drawPixel(renderer, centerX + x, centerY - y);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

int main() {
    int centerX, centerY, radius;

    printf("Enter center coordinates (a,b): ");
    scanf("%d,%d", &centerX, &centerY);
    printf("Enter radius (r): ");
    scanf("%d", &radius);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawCircle(renderer, centerX, centerY, radius);

    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
