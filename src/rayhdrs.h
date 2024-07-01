/* Ray Tracer Prototype Statements */

#ifndef RAYHDRS_H
#define RAYHDRS_H
#include "ray.h"
#include "list.h"

/** getnum.c **/
int getint(FILE *inFP);
double getdouble(FILE *inFP);

/** environment.c **/
env_t *environment_init(FILE *inFP, int columns);
void environment_dump(env_t *env);
triple_t map_pix_to_world(env_t *env, int x, int y);
double randpix(int p);

/** model.c **/
int model_init( FILE *fp, model_t *model);
void model_dump(FILE *out, model_t *model);

/** object.c **/
obj_t *object_init(FILE *fp, char *objclass, int objcat);
void object_dump(obj_t *objPtr);

/** sceneobj.c **/
obj_t *sceneobj_init(FILE *fp, char *objclass);
void sceneobj_dump(obj_t *obj);

/** sphere .c **/
obj_t *sphere_init(FILE *fp, char *objclass);
void sphere_dump(FILE *out, obj_t *objPtr);
double sphere_hits(triple_t *base, triple_t *dir, obj_t  *obj);

/** plane_hits **/
obj_t *plane_init(FILE *fp, char *objclass);
void plane_dump(FILE *out, obj_t *objPtr);
double plane_hits(triple_t *base, triple_t *dir, obj_t  *obj);

/** image **/
void make_image(FILE *outFP, model_t *model);
pixel* return_image(model_t *model);
void make_pixel(model_t *model, int colndx, int rowndx, pixel *pixPtr);

/** ray **/
void ray_trace(model_t *model, triple_t *base, triple_t *unitDir,
                  triple_t *intensity, double total_dist,
                  obj_t *last_hit);
obj_t *find_closest_obj(list_t *scene, triple_t *base, triple_t *unitDir,
   obj_t *lasthit); 

/** light.c **/
obj_t *light_init(FILE *fp, char *objClass);
void light_dump(FILE *out, model_t *model);

/** illuminate.c **/
triple_t diffuse_illumination(model_t *model, obj_t *hitobj);
triple_t process_light(list_t *lst, obj_t *hitobj, obj_t *lobj);

/** polygon.c **/
obj_t *polygon_init(FILE *in, char *objclass);
void polygon_dump(FILE *out, obj_t *objPtr);
double polygon_hits(triple_t *base, triple_t *dir, obj_t *obj);

/** rectangle.c **/
obj_t *rectangle_init(FILE *fp, char *objClass);

/** triangle.c **/
obj_t *triangle_init(FILE *fp, char *objClass);

/** POLYTEST TEMP **/
obj_t *polytest_init(FILE *fp, char *objClass);

#endif
