#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <stdio.h>
#include <math.h>


#define WIDTH 800
#define HEIGHT 600

void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float xIncrement, yIncrement;
    float x = (float)x1, y = (float)y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    for (int i = 0; i <= steps; ++i) {
        SDL_RenderDrawPoint(renderer, (int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Line", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int x1, y1, x2, y2;

    printf("Enter the coordinates of the first point: ");
    scanf("%d %d", &x1, &y1);

    printf("Enter the coordinates of the second point: ");
    scanf("%d %d", &x2, &y2);

    drawLine(renderer, x1, y1, x2, y2);

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
