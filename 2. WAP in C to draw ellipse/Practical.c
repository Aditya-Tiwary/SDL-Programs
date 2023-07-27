#include <SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

void drawEllipse(SDL_Renderer* renderer, int centerX, int centerY, int radiusX, int radiusY) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int x, y;
    int halfWidth = radiusX / 2;
    int halfHeight = radiusY / 2;
    int sqrHalfWidth = halfWidth * halfWidth;
    int sqrHalfHeight = halfHeight * halfHeight;
    int sqrHalfWidthTimesTwo = sqrHalfWidth * 2;
    int sqrHalfHeightTimesTwo = sqrHalfHeight * 2;

    for (x = -halfWidth; x <= halfWidth; ++x) {
        y = (int)(halfHeight * sqrt(1 - ((double)(x * x) / sqrHalfWidth)));

        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
    }

    for (y = -halfHeight; y <= halfHeight; ++y) {
        x = (int)(halfWidth * sqrt(1 - ((double)(y * y) / sqrHalfHeight)));

        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Ellipse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;
    int radiusX = 200;
    int radiusY = 100;

    drawEllipse(renderer, centerX, centerY, radiusX, radiusY);

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
