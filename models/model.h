#ifndef MODEL_H
#define MODEL_H


typedef struct {
	float (*vertices)[3];
	int   (*faces)[3];
	int vertex_count;
	int face_count;
}Model;

#endif
