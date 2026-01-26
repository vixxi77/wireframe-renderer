#include "wireframe_renderer.h"

int 
main(void){
	App app = {0};

	if(initalization(&app)) return EXIT_FAILURE;
	normalize_model(current);

	app.running = 1;
	while(app.running){
		frame(&app);
	}

	cleanup(&app);
	return 0;
}

