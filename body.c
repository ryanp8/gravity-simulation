#include "body.h"


void print_body(Body *b) {
    printf("[Body %d] x: %f, y: %f, prevx: %f, prevy: %f, vx: %f, vy: %f, ax: %f, ay: %f\n", b->id, b->x, b->y, b->prevx, b->prevy, b->vx, b->vy, b->ax, b->ay);
}



void draw_circle(SDL_Renderer * renderer, int centerX, int centerY, int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

}


void draw_body(SDL_Renderer *renderer, Body *b) {
    int x = b->x;
    int y = b->y;
    int r = b->r;

    SDL_SetRenderDrawColor(renderer, b->c.r, b->c.g, b->c.b, b->c.a);
    if ( r > 1 ) {
        draw_circle(renderer, x, y, r);
    }
    else {
        SDL_RenderDrawPoint(renderer, x, y);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void update(Body *b1, Body **bodies) {
    Body *b2;
    int i = 0;
    float tmpax = 0;
    float tmpay = 0;
    float adj;
    float opp;
    double fg;
    int r;

    while ((b2 = bodies[i])) { // bodies should have trailing 0
        if (b1->id != b2->id) {
            double x = pow(b1->x - b2->prevx, 2.0);
            r = (int) (0.5 + sqrt(pow(b1->x - b2->prevx, 2.0) + pow(b1->y - b2->prevy, 2.0)));
            // printf("%d\n", r);
            if (r > 20) {
                fg = G * b1->m * b2->m / (r * r);
                opp = b2->prevy - b1->y;
                adj = b2->prevx - b1->x;
                tmpax += fg * adj / r / b1->m;
                tmpay += fg * opp / r / b1->m;
            }
        }
        i++;
    }
    b1->ax = tmpax;
    b1->ay = tmpay;
    b1->vx += 10 * b1->ax;
    b1->vy += 10 * b1->ay;
    b1->prevx = b1->x;
    b1->prevy = b1->y;
    b1->x += b1->vx;
    b1->y += b1->vy;
    // print_body(b1);
}

void draw_vectors(SDL_Renderer *renderer, Body *b, float theta) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, b->x, b->y, b->x + b->vx * 50, b->y);
    SDL_RenderDrawLine(renderer, b->x, b->y, b->x, b->y + b->vy * 50);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
