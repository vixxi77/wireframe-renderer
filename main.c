#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define POINT_SIZE    10
#define FPS           60
#define DELTA         1/FPS

SDL_Window     *window;
SDL_Event      event;
SDL_Renderer   *renderer;
static float delta_z = 0;

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
frame_animation(void){
	delta_z += 1.0 * DELTA;
	clear_screen();
	projection(0.5, 0 ,1 + delta_z);
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

int 
main(void){
	initalization();
	loop();
	cleanup();
	return 0;
}

    
