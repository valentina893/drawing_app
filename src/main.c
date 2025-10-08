// main.c

#include "../inc/renderer.h"

#define window_width 640
#define window_height 480

void drawLineOfCircles(renderer* renderer, int x, int y, int prev_x, int prev_y) {
    int dx = x - prev_x;
    int dy = y - prev_y;
    int steps = SDL_max(abs(dx), abs(dy));
    for (int i = 0; i <= steps; i++) {
        int xi = prev_x + dx * i / steps;
        int yi = prev_y + dy * i / steps;
        renderer_drawFilledCircle(renderer, xi, yi, 2, 0, 0, 0, 255);
    }
}

int main() {

    renderer renderer;
    renderer_create(&renderer, "draw", window_width, window_height);

    int running = 1;
    SDL_Event event;

    int click = 0;
    int prev_x = -1, prev_y = -1;

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
                SDL_GetMouseState(&prev_x, &prev_y);  // start stroke
                break;
            case SDL_MOUSEBUTTONUP:
                click = 0;
                prev_x = prev_y = -1;                 // reset stroke
                break;
            default:
                break;
            }
        }

        if (click) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            SDL_SetRenderTarget(renderer._renderer, canvas);

            if (prev_x >= 0 && prev_y >= 0) {
                drawLineOfCircles(&renderer, x, y, prev_x, prev_y);
            } else {
                renderer_drawFilledCircle(&renderer, x, y, 2, 0, 0, 0, 255);
            }

            SDL_SetRenderTarget(renderer._renderer, NULL);

            prev_x = x;
            prev_y = y;
        }
        SDL_RenderCopy(renderer._renderer, canvas, NULL, NULL);
        renderer_present(&renderer);
    }

    return 0;
}