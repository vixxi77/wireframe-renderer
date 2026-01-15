#include "../include/wireframe_renderer.h"

int 
main(void){
	initalization();
	normalize_model(current);
	loop();
	cleanup();
	return 0;
}

