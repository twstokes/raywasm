#include "ray.h"

void make_image(FILE *outFP, model_t *model) {
	int columns = model->env->winPWidth;
	int rows = model->env->winPHeight;

	pixel *pixmap = return_image(model);

	/* Write out file */

	fprintf(outFP, "P6 %d %d 255\n", columns, rows);

	fwrite(pixmap, 1, rows*columns*sizeof(pixel), outFP);

	fclose(outFP);
}

pixel* return_image(model_t *model) {
	pixel *pixmap;
	int x,y;
	int columns, rows;

	columns = model->env->winPWidth;
	rows = model->env->winPHeight;

	/* Compute size of output image and malloc() pixmap */

	pixmap = malloc(columns*rows*sizeof(pixel));

	for (y = 0; y<rows; y++)
	{
		for (x = 0; x<columns; x++)
			make_pixel(model, x, y, (pixmap+x+(columns*(rows-1-y))));
	}

	return pixmap;
}

void make_pixel(model_t *model, int x, int y, pixel *pixval) {
	triple_t world;
	triple_t tempIntensity, intensity;
	triple_t dir;
	int i, samples;

	samples = model->env->samples;

	/* Initilize intensity to (0.0, 0.0, 0.0) */
	intensity.x = 0.0;
	intensity.y = 0.0;
	intensity.z = 0.0;

	for(i=0;i<samples;i++){
		world = map_pix_to_world(model->env, x, y);

		/* Compute unit vector dir in the direction from the view_point to world */
		dir = tl_diff3(&world, &model->env->view_point);
		dir = tl_unitvec3(&dir);
		tempIntensity.x = 0.0;
		tempIntensity.y = 0.0;
		tempIntensity.z = 0.0;
		ray_trace(model, &model->env->view_point, &dir, &tempIntensity, 0.0, NULL);
		intensity = tl_sum3(&intensity, &tempIntensity);
}

	intensity = tl_scale3(&intensity, 1.0/samples);

	/* Clamp each element of intensity to the range [0.0, 1.0] */

	if (intensity.x > 1) 
		intensity.x = 1.0;

	if (intensity.y > 1)
		intensity.y = 1.0;

	if (intensity.z > 1)
		intensity.z = 1.0;

	if (intensity.x < 0)
		intensity.x = 0.0;

	if (intensity.y < 0)
		intensity.y = 0.0;

	if (intensity.z < 0)
		intensity.z = 0.0;

	/* Set (r, g, b) components of vector pointed to by pixval to 255 * corresponding intensity */

	pixval->r = 255*intensity.x;
	pixval->g = 255*intensity.y;
	pixval->b = 255*intensity.z;
	pixval->a = 255;


	return;
}
