#include "main.h"
#include "body.h"

#define NUM_BODIES 10000

int main(void) {
    
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("error during SDL video init\n");
    }

    SDL_Window *window = SDL_CreateWindow("gravity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!window) {
        printf("error creating window\n");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("error creating renderer\n");
    }

    SDL_RenderClear(renderer);

    srand( time( NULL ) );
    Body **bodies = calloc(NUM_BODIES + 1, sizeof(Body*));
    for (int i = 0; i < NUM_BODIES; i++) {
        // Body *b = calloc(1, sizeof(Body));
        // b->id = i;
        // b->x = (float) rand() / RAND_MAX * WIDTH;
        // b->y = (float) rand() / RAND_MAX * HEIGHT;
        // // printf("%f, %f\n", b->x, b->y);
        // b->prevx = b->x;
        // b->prevy = b->y;
        // b->r = 2;
        // b->m = (float) rand() / RAND_MAX * 5.972E11;
        // // b->m = 5.972E10;
        // b->c = (struct color) { .r=255, .g=255, .b=255, .a=255};
        // bodies[i] = b;
    }

    Body *b1 = calloc(1, sizeof(Body));
    b1->id = 1;
    // b1->x = (float) rand() / RAND_MAX * WIDTH;
    // b1->y = (float) rand() / RAND_MAX * HEIGHT;
    b1->x = 250;
    b1->y = 250;
    b1->prevx = b1->x;
    b1->prevy = b1->y;
    b1->vy = 0.001;
    b1->r = 15;
    b1->m = 5.972E10;
    b1->c = (struct color) { .r=255, .g=127, .b=127, .a=255};
    bodies[0] = b1;

    for (int i = 0; i < NUM_BODIES - 1; i++) {
        Body *b2 = calloc(1, sizeof(Body));
        b2->id = i;
        b2->x = (float) rand() / RAND_MAX * WIDTH;
        b2->y = (float) rand() / RAND_MAX * HEIGHT;
        b2->vx = (float) rand() / RAND_MAX/ 2;
        b2->vy = (float) rand() / RAND_MAX/2;
        printf("%d, %d\n", b2->vx, b2->vy);
        b2->prevx = b2->x;
        b2->prevy = b2->y;
        b2->r = 3;
        b2->m = (float) rand() / RAND_MAX * 5.972E3;
        b2->c = (struct color) { .r=255, .g=127, .b=127, .a=255};
        bodies[i + 1] = b2;
    }
    


    // print_body(bodies[0]);

    // Body b1;
    // b1.x = WIDTH / 2;
    // b1.y = HEIGHT / 2;
    // b1.r = 50;
    // b1.c.r = b1.c.g = b1.c.b = b1.c.a = 255;

    // draw_body(renderer, &b1);

    SDL_Event e;
    char running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        int i;
        SDL_RenderClear(renderer);
        for (i = 0; i < NUM_BODIES; i++) {
            update(bodies[i], bodies);
            draw_body(renderer, bodies[i]);
            // draw_vectors(renderer, bodies[i], 0);
        }
        SDL_RenderPresent(renderer);
        // draw_body(renderer, bodies[0]);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
