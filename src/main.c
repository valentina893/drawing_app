// main.c

#include "../inc/renderer.h"

#define window_width 640
#define window_height 480

int main() {

    renderer renderer;
    renderer_create(&renderer, "draw", window_width, window_height);

    int click = 0;

    int running = 1;
    SDL_Event event;

    SDL_Texture* canvas = SDL_CreateTexture(
    renderer._renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    window_width, window_height
    );

    SDL_SetRenderTarget(renderer._renderer, canvas);
    renderer_clear(&renderer, 255, 255, 255, 255);
    SDL_SetRenderTarget(renderer._renderer, NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                click = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                click = 0;
                break;
            default:
                break;
            }
        }
        if (click) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_SetRenderTarget(renderer._renderer, canvas);
            renderer_drawFilledCircle(&renderer, x, y, 2, 0, 0, 0, 255);
            SDL_SetRenderTarget(renderer._renderer, NULL);
        }
        SDL_RenderCopy(renderer._renderer, canvas, NULL, NULL);
        renderer_present(&renderer);
    }

    return 0;
}