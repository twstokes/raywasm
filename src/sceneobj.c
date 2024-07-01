#include "ray.h"
#include "string.h"

obj_t *sceneobj_init(FILE *fp, char *objclass) {

	obj_t *newObj = object_init(fp, strdup(objclass), 0);

	newObj->sceneData.color.x = getdouble(fp);
	newObj->sceneData.color.y = getdouble(fp);
	newObj->sceneData.color.z = getdouble(fp);
	newObj->sceneData.diffuse = getdouble(fp);
	newObj->sceneData.specular = getdouble(fp);

	return newObj;	
}


void sceneobj_dump(obj_t *obj) {

	object_dump(obj);

	fprintf(stderr, "   Reflectivity data:\n      Color:      %5.4lf   %5.4lf   %5.4lf\n      Diffuse:    %5.4lf\n      Specular:   %5.4lf\n", obj->sceneData.color.x, obj->sceneData.color.y, obj->sceneData.color.z, obj->sceneData.diffuse, obj->sceneData.specular);

	return;
}
