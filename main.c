#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 800

SDL_Window     *window;
SDL_Event      event;
SDL_Renderer   *renderer;

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
draw_rectangle(int *x, int *y, int *size){
    SDL_Rect rectangle = {*x - (*size / 2), *y - (*size / 2), *size, *size};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}

void 
screen_projection_point(int x, int y, int size){
	int _x = (x + 1) / 2.0 * WINDOW_WIDTH; //didint know literal flaoting point numbers help with such conversions, no need to change everything to floats nice
	int _y = (y + 1) / 2.0 * WINDOW_HEIGHT;

	draw_rectangle(&_x, &_y, &size);
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
	clear_screen();
	screen_projection_point(0, 0, 10);
        SDL_RenderPresent(renderer);
    }
}

int 
main(void){
	initalization();
	loop();
	cleanup();
	return 0;
}

    
