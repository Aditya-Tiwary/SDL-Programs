#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

void drawPolygon(SDL_Renderer* renderer, int* verticesX, int* verticesY, int numVertices) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < numVertices; i++) {
        int startX = verticesX[i];
        int startY = verticesY[i];
        int endX = verticesX[(i + 1) % numVertices];
        int endY = verticesY[(i + 1) % numVertices];

        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Polygon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int verticesX[] = { 400, 500, 600, 500 };
    int verticesY[] = { 300, 400, 300, 200 };
    int numVertices = sizeof(verticesX) / sizeof(verticesX[0]);

    drawPolygon(renderer, verticesX, verticesY, numVertices);

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
