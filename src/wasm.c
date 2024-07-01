#include "ray.h"
#include "emscripten.h"

// global to store the number of pixels in the pixmap
int pixmap_size = 0;
// global to store the address of the pixmap
pixel *pixmap = NULL;

EMSCRIPTEN_KEEPALIVE
void raytrace(char *input, int inputLength, int width, int samples) {
    int columns, rows;
    FILE *fp;

    // the original project expected a file to read input from and
    // a file to write the image to -- we can reuse this functionality
    // without a big overhaul by using the fmemopen function that will make
    // a "file pointer" from buffered memory
    fp = fmemopen(input, inputLength, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error converting string to file pointer.\n");
        exit(1);
    }

    model_t *model  = (model_t *)malloc(sizeof(model_t));
    model->env = environment_init(fp, width);
    model->env->samples = samples;
    model->lights  = l_init();
    model->scene   = l_init();

    if (model_init(fp, model) != 0) {
        fprintf(stderr, "Error initializing the model.\n");
        exit(1);
    } 

    columns = model->env->winPWidth;
    rows = model->env->winPHeight;

    // instead of writing to an image file, we return
    // an array of pixels of the RGBA format
    pixmap = return_image(model);
    pixmap_size = rows*columns*sizeof(pixel);
}

EMSCRIPTEN_KEEPALIVE
// used by JS to free the pixel map memory
void free_pixmap_mem() {
    free(pixmap);
    pixmap = NULL;
    pixmap_size = 0;
}

EMSCRIPTEN_KEEPALIVE
// used by JS to get a pointer to the pixel map
int get_pixmap_pointer() {
    return (int)pixmap;
}

EMSCRIPTEN_KEEPALIVE
// used by JS to get the size of the pixel map in bytes
int get_pixmap_size() {
    return pixmap_size;
}
