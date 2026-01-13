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
#include <stdint.h>

SDL_Window    *window;
SDL_Event      event;
SDL_Renderer  *renderer;

void 
window_initalization(){
	SDL_Init(SDL_INIT_VIDEO);	
}

void 
window_creation(){
    window = SDL_CreateWindow("wireframe_renderer",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
                              800, 0);
	
}

void 
renderer_initalization(){
    renderer = SDL_CreateRenderer(window,
                             -1, 0);
}


int 
main(void){
	window_initalization();
	window_creation();
	renderer_initalization();


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
	
	SDL_Quit();
	return 1;
}

    
