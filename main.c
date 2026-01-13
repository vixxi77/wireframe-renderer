#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define POINT_SIZE    10
#define FPS           60
#define DELTA         1.0/FPS

SDL_Window     *window;
SDL_Event      event;
SDL_Renderer   *renderer;
static float delta_z = 1;
static float angle   = 0;
/*
 * TODO: FIX VERTEX COUNT, VERTEX COUNT IS FIRST
 */
float vertices[8][3] = {
	0.25,0.25, 0.25,   
	-0.25,0.25,0.25, 
	0.25,-0.25,0.25,
	-0.25,-0.25,0.25,

	0.25,0.25, -0.25,   
	-0.25,0.25,-0.25, 
	0.25,-0.25,-0.25,
	-0.25,-0.25,-0.25
};

float edges [12][2] = {
    {0, 1}, {1, 3}, {3, 2}, {2, 0},
    {4, 5}, {5, 7}, {7, 6}, {6, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

void initalization(void);
void cleanup(void);
void clear_screen(void);
void draw_rectangle(float *x, float *y);
void screen_coordinate_point_normalized(float *x, float *y);
void projection(float x, float y, float z, float *screen_x, float *screen_y);
void translate_z(float *z, float *_delta_z);
void rotate_xz(float *x, float *y, float angle);
void frame_animation(void);
void loop(void);

int 
main(void){
	initalization();
	loop();
	cleanup();
	return 0;
}

void 
initalization(void){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
	    printf("failed initialazing SDL: %s \n", SDL_GetError());
	    exit(1);
    }

    window = SDL_CreateWindow("wireframe_renderer",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, 0);

    if(window == NULL){
	    printf("failed creating a window: %s \n", SDL_GetError());
	    exit(1);
    }

    renderer = SDL_CreateRenderer(window,
                             -1, 0);

    if(renderer == NULL){
	    printf("failed creating a renderer: %s \n", SDL_GetError());
	    exit(1);
    }

}

void 
cleanup(void){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void
clear_screen(void){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void
draw_rectangle(float *x, float *y){
    SDL_Rect rectangle = {
	    .x = (int)*x - (POINT_SIZE / 2),
	    .y = (int)*y - (POINT_SIZE / 2),
	    .w = POINT_SIZE,
	    .h = POINT_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}

void 
get_screen_coordinates(float *x, float *y, float *screen_x, float *screen_y){
	*screen_x = (*x + 1) / 2.0 * WINDOW_WIDTH; //didint know literal flaoting point numbers help with such conversions, no need to change everything to floats nice
	*screen_y = (1 - (*y + 1) / 2.0) * WINDOW_HEIGHT;
}



void projection(float x, float y, float z, float *screen_x, float *screen_y){
	float _x = x / z;
	float _y = y / z;	

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
draw_line(float *x1, float *y1,  float *x2, float *y2){
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLineF(renderer, *x1, *y1, *x2, *y2);
}

void
frame_animation(void){
	//delta_z += 1.0 * DELTA;
	angle   += M_PI * DELTA;
	clear_screen();

	for(int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++){
		int _a = edges[i][0];
		int _b = edges[i][1];

		float _x1 = vertices[_a][0];
		float _y1 = vertices[_a][1];
		float _z1 = vertices[_a][2];
		rotate_xz(&_x1, &_z1, angle);
		translate_z(&_z1, &delta_z);

		float screen_x1, screen_y1;
		projection(_x1, _y1, _z1, &screen_x1, &screen_y1);

		float _x2 = vertices[_b][0];
		float _y2 = vertices[_b][1];
		float _z2 = vertices[_b][2];
		rotate_xz(&_x2, &_z2, angle);
		translate_z(&_z2, &delta_z);

		float screen_x2, screen_y2;
		projection(_x2, _y2, _z2, &screen_x2, &screen_y2);
		draw_line(&screen_x1, &screen_y1, &screen_x2, &screen_y2);
	}
        SDL_RenderPresent(renderer);
	SDL_Delay(1000/FPS);
}

void loop(void){
    int run = 1;
    while(run){
        while(SDL_PollEvent(&event)){
    	    switch(event.type){
    	    case SDL_QUIT:
    		    run = 0;
    		    break;
    	    }
        }
	frame_animation();
    }
}
    
