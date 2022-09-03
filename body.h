#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#ifndef BODY_H
#define BODY_H

#define G 6.67408E-11
// #define G 1

struct color {
	int r;
	int g;
	int b;
	int a;
};

typedef struct body {
	int id;
	int r;
	float x;
	float y;
	float prevx;
	float prevy;
	float vx;
	float vy;
	float ax;
	float ay;
	float m;
	struct color c;
} Body;

void print_body(Body *b);
void draw_vectors(SDL_Renderer *renderer, Body *b, float theta);
void draw_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius);
void draw_body(SDL_Renderer *renderer, Body *b);

void update(Body *b1, Body **bodies);

#endif
