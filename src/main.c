#include "wireframe_renderer.h"
#include <stdlib.h>

int 
main(void){
	App app = {0};

	if(initalization(&app)) exit(EXIT_FAILURE);
	normalize_model(current);
	loop(&app);
	cleanup(&app);
	return 0;
}

