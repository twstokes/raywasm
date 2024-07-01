#include "ray.h"
#include <string.h>

obj_t *object_init(FILE *fp, char *objclass, int objcat) {
	static int objid = 0;

	obj_t *newObj = malloc(sizeof(obj_t));
	
	newObj->objclass = objclass;
	newObj->objcat = objcat;
	newObj->objid = objid;
	objid++;
	return newObj;
}


void object_dump(obj_t *obj) {

	fprintf(stderr, "\nDumping object %d, category %d, type %s\n", obj->objid, obj->objcat, obj->objclass);

	return;

}
