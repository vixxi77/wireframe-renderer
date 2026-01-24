#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wireframe_renderer.h"
#include "ak47_model.h"
#include "penger_model.h"
#include "sink_model.h"
#include "minivan_model.h"

static float delta_z = 1;
static float angle   = 0;

//Model *current = &ak47_model;
Model *current = &penger_model;
//Model *current = &sink_model;
//Model *current = &minivan_model;

int 
initalization(App *app){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
	    printf("failed initialazing SDL: %s \n", SDL_GetError());
	    return 1;
    }

    app->window = SDL_CreateWindow("wireframe_renderer",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, 0);

    if(app->window == NULL){
	    printf("failed creating a window: %s \n", SDL_GetError());
	    return 1;
    }

    app->renderer = SDL_CreateRenderer(app->window,
                             -1, 0);

    if(app->renderer == NULL){
	    printf("failed creating a renderer: %s \n", SDL_GetError());
	    return 1;
    }
    return 0;
}

void 
cleanup(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

void
clear_screen(App *app){
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void 
get_screen_coordinates(float *x, float *y, float *screen_x, float *screen_y){
	*screen_x = (*x + 1) / 2.0 * WINDOW_WIDTH; //didint know literal flaoting point numbers help with such conversions, no need to change everything to floats nice
	*screen_y = (1.0 - (*y + 1.0) / 2.0) * WINDOW_HEIGHT;
}

void projection(float x, float y, float z, float *screen_x, float *screen_y){
	if( z < 0.1) z = 0.1;
	float _x = x / z * ZOOM;
	float _y = y / z * ZOOM;	

	get_screen_coordinates(&_x, &_y, screen_x, screen_y);
}

void
translate_z(float *z, float *_delta_z){
	*z += *_delta_z;
}

void 
rotate_xz(float *x, float *z, float angle){
	float c = cos(angle);
	float s = sin(angle);

	float old_x = *x;
	float old_z = *z;

	*x = old_x * c - old_z * s;
        *z = old_x * s + old_z * c;	
}

void
draw_line(App *app, float x1, float y1,  float x2, float y2){
	SDL_RenderDrawLineF(app->renderer, x1, y1, x2, y2);
}

void
frame_animation(App *app, Model *m){
	//delta_z += 1.0 * DELTA;
	angle   += 0.5 * M_PI * DELTA;
	clear_screen(app);

	for(int i = 0; i < m->face_count; i++){
		int _a = m->faces[i][0];
		int _b = m->faces[i][1];
		int _c = m->faces[i][2];

		float _x1 = m->vertices[_a][0];
		float _y1 = m->vertices[_a][1];
		float _z1 = m->vertices[_a][2];
		rotate_xz(&_x1, &_z1, angle);
		translate_z(&_z1, &delta_z);

		float screen_x1, screen_y1;
		projection(_x1, _y1, _z1, &screen_x1, &screen_y1);

		float _x2 = m->vertices[_b][0];
		float _y2 = m->vertices[_b][1];
		float _z2 = m->vertices[_b][2];
		rotate_xz(&_x2, &_z2, angle);
		translate_z(&_z2, &delta_z);

		float screen_x2, screen_y2;
		projection(_x2, _y2, _z2, &screen_x2, &screen_y2);

		float _x3 = m->vertices[_c][0];
		float _y3 = m->vertices[_c][1];
		float _z3 = m->vertices[_c][2];
		rotate_xz(&_x3, &_z3, angle);
		translate_z(&_z3, &delta_z);

		float screen_x3, screen_y3;
		projection(_x3, _y3, _z3, &screen_x3, &screen_y3);

		SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255);
		draw_line(app, screen_x1, screen_y1, screen_x2, screen_y2);
		draw_line(app, screen_x2, screen_y2, screen_x3, screen_y3);
		draw_line(app, screen_x3, screen_y3, screen_x1, screen_y1);
	}
        SDL_RenderPresent(app->renderer);
	SDL_Delay(1000/FPS);
}

void set_bounds(Model *m, float *min_x, float *max_x, float *min_y, float *max_y, float *min_z, float *max_z){
	*min_x = *min_y = *min_z = 1e9f;
	*max_x = *max_y = *max_z = -1e9f;

	for (int i = 0; i < m->vertex_count; i++) {
		float x = m->vertices[i][0];
		float y = m->vertices[i][1];
		float z = m->vertices[i][2];

		if (x < *min_x) *min_x = x;
		if (x > *max_x) *max_x = x;
		if (y < *min_y) *min_y = y;
		if (y > *max_y) *max_y = y;
		if (z < *min_z) *min_z = z;
		if (z > *max_z) *max_z = z;
	    }
}

void normalize_model (Model *m){
	if(!m) return;

	float min_x, max_x, min_y, max_y, min_z, max_z;
	set_bounds(m, &min_x, &max_x, &min_y, &max_y, &min_z, &max_z);

	float cx = (min_x + max_x) * 0.5f;
	float cy = (min_y + max_y) * 0.5f;
	float cz = (min_z + max_z) * 0.5f;

	float sx = max_x - min_x;
	float sy = max_y - min_y;
	float sz = max_z - min_z;

	float max_extent = sx;
	if (sy > max_extent) max_extent = sy;
	if (sz > max_extent) max_extent = sz;

	float scale = 1.0f / max_extent;

	for (int i = 0; i < m->vertex_count; i++) {
	     m->vertices[i][0] = (m->vertices[i][0] - cx) * scale;
	     m->vertices[i][1] = (m->vertices[i][1] - cy) * scale;
	     m->vertices[i][2] = (m->vertices[i][2] - cz) * scale;
	}
}

void loop(App *app){
    int run = 1;
    while(run){
        while(SDL_PollEvent(&app->event)){
    	    switch(app->event.type){
    	    case SDL_QUIT:
    		    run = 0;
    		    break;
    	    }
        }
	frame_animation(app, current);
    }
}

