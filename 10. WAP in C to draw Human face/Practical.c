#include <SDL.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void drawEllipse(int x, int y, int radiusX, int radiusY) {
    int radiusXSquared = radiusX * radiusX;
    int radiusYSquared = radiusY * radiusY;
    int twoRadiusXSquared = 2 * radiusXSquared;
    int twoRadiusYSquared = 2 * radiusYSquared;
    int xCoord = radiusX;
    int yCoord = 0;
    int xChange = radiusYSquared * (1 - (2 * radiusX));
    int yChange = radiusXSquared;
    int ellipseError = 0;
    int stoppingX = radiusYSquared * radiusX;
    int stoppingY = 0;

    while (stoppingX >= stoppingY) {
        SDL_RenderDrawPoint(renderer, x + xCoord, y + yCoord);
        SDL_RenderDrawPoint(renderer, x - xCoord, y + yCoord);
        SDL_RenderDrawPoint(renderer, x - xCoord, y - yCoord);
        SDL_RenderDrawPoint(renderer, x + xCoord, y - yCoord);

        yCoord++;
        stoppingY += twoRadiusXSquared;
        ellipseError += yChange;
        yChange += twoRadiusXSquared;

        if (((2 * ellipseError) + xChange) > 0) {
            xCoord--;
            stoppingX -= twoRadiusYSquared;
            ellipseError += xChange;
            xChange += twoRadiusYSquared;
        }
    }

    xCoord = 0;
    yCoord = radiusY;
    xChange = radiusYSquared;
    yChange = radiusXSquared * (1 - (2 * radiusY));
    ellipseError = 0;
    stoppingX = 0;
    stoppingY = radiusXSquared * radiusY;

    while (stoppingX <= stoppingY) {
        SDL_RenderDrawPoint(renderer, x + xCoord, y + yCoord);
        SDL_RenderDrawPoint(renderer, x - xCoord, y + yCoord);
        SDL_RenderDrawPoint(renderer, x - xCoord, y - yCoord);
        SDL_RenderDrawPoint(renderer, x + xCoord, y - yCoord);

        xCoord++;
        stoppingX += twoRadiusYSquared;
        ellipseError += xChange;
        xChange += twoRadiusYSquared;

        if (((2 * ellipseError) + yChange) > 0) {
            yCoord--;
            stoppingY -= twoRadiusXSquared;
            ellipseError += yChange;
            yChange += twoRadiusXSquared;
        }
    }
}

void drawRobotFace() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw the face outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawEllipse(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200, 250);

    // Draw the eyes
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawEllipse(WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 - 80, 40, 30);
    drawEllipse(WINDOW_WIDTH / 2 + 90, WINDOW_HEIGHT / 2 - 80, 40, 30);

    // Draw the pupils
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawEllipse(WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 - 80, 20, 15);
    drawEllipse(WINDOW_WIDTH / 2 + 90, WINDOW_HEIGHT / 2 - 80, 20, 15);

    // Draw the nose
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50);
    SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50, WINDOW_WIDTH / 2 + 20, WINDOW_HEIGHT / 2);

    // Draw the mouth
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect mouthRect = { WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 + 100, 100, 20 };
    SDL_RenderFillRect(renderer, &mouthRect);

    // Render everything to the window
    SDL_RenderPresent(renderer);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow("Robot Face", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        drawRobotFace();
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
