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

void initalization(void);
void cleanup(void);
void clear_screen(void);
void draw_rectangle(float *x, float *y);
void screen_coordinate_point_normalized(float *x, float *y);
void projection(float x, float y, float z);
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
screen_coordinate_point_normalized(float *x, float *y){
	float _x = (*x + 1) / 2.0 * WINDOW_WIDTH; //didint know literal flaoting point numbers help with such conversions, no need to change everything to floats nice
	float _y = (1 - (*y + 1) / 2.0) * WINDOW_HEIGHT;

	draw_rectangle(&_x, &_y);
}

void projection(float x, float y, float z){
	float _x = x / z;
	float _y = y / z;	

	screen_coordinate_point_normalized(&_x, &_y);

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
frame_animation(void){
	//delta_z += 1.0 * DELTA;
	angle   += M_PI * DELTA;
	clear_screen();
	for(int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++){
		float _x = vertices[i][0];
		float _y = vertices[i][1];
		float _z = vertices[i][2];

		rotate_xz(&_x, &_z, angle);
		translate_z(&_z, &delta_z);
		projection(_x, _y, _z);
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
    
