/* This is SDL2 Initialization boiler plate

   #include <SDL2/SDL.h>
   -----------------------------------------------
    int SDL_Init(Uint32 flags);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_INIT_AUDIO
    SDL_INIT_VIDEO
    SDL_INIT_EVERYTHING
    -----------------------------------------------
    SDL_Window *window;
    window = SDL_CreateWindow(const char *title,
                              int x, int y, int w,
                              int h, Uint32 flags);
    SDL_WINDOWPOS_CENTERED
    -----------------------------------------------
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(SDL_Window * window,
                             int index, Uint32 flags);

    SDL_SetRenderDrawColor(SDL_Renderer * renderer,
                   Uint8 r, Uint8 g, Uint8 b,
                   Uint8 a);
		   
    SDL_RenderClear(SDL_Renderer * renderer); SDL_RENDERER_ACCELERATED
    -----------------------------------------------
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
    }
    -----------------------------------------------
    WIP TO BE CONTINUED!
 */ 

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 800

SDL_Window    *window;
SDL_Event      event;
SDL_Renderer  *renderer;

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
	    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    SDL_RenderClear(renderer);
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

    
