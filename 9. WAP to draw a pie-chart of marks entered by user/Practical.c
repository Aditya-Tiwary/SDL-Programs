#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CHART_RADIUS 200

// Function to draw a pie chart segment
void drawPieSegment(SDL_Renderer* renderer, int x, int y, int radius, int startAngle, int endAngle, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    for (int angle = startAngle; angle <= endAngle; ++angle)
    {
        float angleRad = angle * 3.14159 / 180.0;
        int xPos = x + (radius * cos(angleRad));
        int yPos = y - (radius * sin(angleRad));
        SDL_RenderDrawLine(renderer, x, y, xPos, yPos);
    }
}

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Pie Chart", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int totalMarks;
    printf("Enter total marks: ");
    scanf_s("%d", &totalMarks);

    int marks[5];
    for (int i = 0; i < 5; ++i)
    {
        printf("Enter marks: ");
        scanf_s("%d", &marks[i]);
    }

    // Calculate angles for the pie segments
    double angles[5];
    double totalAngle = 0.0;
    for (int i = 0; i < 5; ++i)
    {
        angles[i] = marks[i] / (double)totalMarks * 360.0;
        totalAngle += angles[i];
    }

    // Normalize the angles to make sure the pie chart is complete
    if (totalAngle < 360.0)
        angles[0] += 360.0 - totalAngle;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Draw the pie chart segments
    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;
    int startAngle = 0;
    for (int i = 0; i < 5; ++i)
    {
        int endAngle = startAngle + (int)angles[i];
        Uint8 r = rand() % 256;
        Uint8 g = rand() % 256;
        Uint8 b = rand() % 256;
        drawPieSegment(renderer, centerX, centerY, CHART_RADIUS, startAngle, endAngle, r, g, b);
        startAngle = endAngle;
    }

    // Render the result
    SDL_RenderPresent(renderer);

    // Wait for the user to close the window
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
