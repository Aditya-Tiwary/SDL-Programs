#include <SDL.h>
#include <SDL_ttf.h>

// Function to initialize SDL and create a window
SDL_Window* initSDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Background Color Example",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN);

    return window;
}

// Function to set the background color
void setBackgroundColor(SDL_Renderer* renderer, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderClear(renderer);
}

// Function to render text on the screen
// Function to render text on the screen with highlighted background
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, SDL_Color highlightColor, int x, int y)
{
    // Render the text on a transparent surface
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, textColor);

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Set the blend mode to enable transparency
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Get the dimensions of the text surface
    int textWidth = surface->w;
    int textHeight = surface->h;

    // Create a surface for the highlight background
    SDL_Surface* highlightSurface = SDL_CreateRGBSurface(0, textWidth, textHeight, 32, 0, 0, 0, 0);

    // Fill the highlight surface with the desired highlight color
    SDL_FillRect(highlightSurface, NULL, SDL_MapRGB(highlightSurface->format, highlightColor.r, highlightColor.g, highlightColor.b));

    // Create a texture from the highlight surface
    SDL_Texture* highlightTexture = SDL_CreateTextureFromSurface(renderer, highlightSurface);

    // Set the blend mode to enable transparency for the highlight texture
    SDL_SetTextureBlendMode(highlightTexture, SDL_BLENDMODE_BLEND);

    // Copy the highlight texture to the renderer
    SDL_Rect highlightRect;
    highlightRect.x = x;
    highlightRect.y = y;
    highlightRect.w = textWidth;
    highlightRect.h = textHeight;
    SDL_RenderCopy(renderer, highlightTexture, NULL, &highlightRect);

    // Copy the text texture to the renderer
    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = textWidth;
    textRect.h = textHeight;
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Cleanup resources
    SDL_DestroyTexture(highlightTexture);
    SDL_FreeSurface(highlightSurface);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


int main()
{
    // Initialize SDL and create a window
    SDL_Window* window = initSDL();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Load a font for rendering text
    TTF_Font* font = TTF_OpenFont("arial.ttf", 48); // Increase the font size to 48

    // Set the initial background color
    setBackgroundColor(renderer, 0, 0, 0); // Black background

    // Event loop
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Render the text
        setBackgroundColor(renderer, 0, 0, 0); // Clear the renderer with the background color
        renderText(renderer, font, "Current background color is RED", (SDL_Color) { 255, 255, 255 }, (SDL_Color) { 255, 0, 0, 255 }, 100, 200); // White text color and red background

        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
