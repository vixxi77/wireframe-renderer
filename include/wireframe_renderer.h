#ifndef W_RENDER
#define W_RENDER

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000
#define POINT_SIZE    10
#define FPS           60
#define DELTA         1.0/FPS
#define ZOOM          1.5

#include "../include/model.h"
#include <SDL2/SDL.h>

extern Model *current;

typedef struct {
	SDL_Window   *window;
	SDL_Event     event;
	SDL_Renderer *renderer;
} App;

int  initalization(App *app);
void cleanup(App *app);
void clear_screen(App *app);
void get_screen_coordinates(float *x, float *y, float *screen_x, float *screen_y);
void projection(float x, float y, float z, float *screen_x, float *screen_y);
void translate_z(float *z, float *_delta_z);
void rotate_xz(float *x, float *y, float angle);
void frame_animation(App *app, Model *model);
void set_bounds(Model *m, float *min_x, float *max_x, float *min_y, float *max_y, float *min_z, float *max_z);
void normalize_model (Model *m);
void draw_line(App *app, float x1, float y1, float x2, float y2);
void loop(App *app);

#endif
