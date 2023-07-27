#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

// Function to draw a pie slice
void drawPieSlice(SDL_Renderer* renderer, int x, int y, int radius, int startAngle, int endAngle, SDL_Color color, const char* name) {
    // Convert angles to radians
    double startRad = (double)startAngle * M_PI / 180.0;
    double endRad = (double)endAngle * M_PI / 180.0;

    // Draw the pie slice
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = startAngle; i <= endAngle; i++) {
        double rad = (double)i * M_PI / 180.0;
        int x1 = x + (int)(radius * cos(rad));
        int y1 = y + (int)(radius * sin(rad));
        SDL_RenderDrawLine(renderer, x, y, x1, y1);
    }

    // Render the name near the slice
    SDL_Surface* textSurface = NULL;
    SDL_Color textColor = { 255, 255, 255 }; // White color for the text
    SDL_Rect textRect;

    // Create a font
    TTF_Font* font = TTF_OpenFont("arial.ttf", 20); // Provide the correct path to "arial.ttf" font file

    // Create a surface from the font and the name text
    textSurface = TTF_RenderText_Solid(font, name, textColor);

    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Calculate the position of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    int textX = x + (int)((radius + 20) * cos((startRad + endRad) / 2)) - (textWidth / 2);
    int textY = y + (int)((radius + 20) * sin((startRad + endRad) / 2)) - (textHeight / 2);

    // Set the position and dimensions of the text
    textRect.x = textX;
    textRect.y = textY;
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Render the text texture
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Clean up resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_ttf
    TTF_Init();

    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Pie Chart", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    // Set up the pie chart parameters
    int centerX = 400;
    int centerY = 300;
    int radius = 200;

    // Draw the pie chart slices
    drawPieSlice(renderer, centerX, centerY, radius, 0, 60, (SDL_Color) { 255, 0, 0, 255 }, "Food");      // Red
    drawPieSlice(renderer, centerX, centerY, radius, 60, 160, (SDL_Color) { 255, 255, 0, 255 }, "Rent");  // Yellow
    drawPieSlice(renderer, centerX, centerY, radius, 160, 220, (SDL_Color) { 0, 255, 0, 255 }, "Electricity         ");   // Green
    drawPieSlice(renderer, centerX, centerY, radius, 220, 360, (SDL_Color) { 139, 69, 19, 255 }, "Savings"); // Brown

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for the user to close the window
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL_ttf
    TTF_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}
