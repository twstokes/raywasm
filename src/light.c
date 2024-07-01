#include "ray.h"

obj_t *light_init(FILE *fp, char *objClass){
	obj_t *new;

	assert((new = object_init(fp, strdup(objClass), 1)) != NULL);
	
	new->lightData.emissivity.x = getdouble(fp);
	new->lightData.emissivity.y = getdouble(fp);
	new->lightData.emissivity.z = getdouble(fp);

	new->lightData.center.x = getdouble(fp);
	new->lightData.center.y = getdouble(fp);
	new->lightData.center.z = getdouble(fp);

	return(new);
}


void light_dump(FILE *out, model_t *model){
	obj_t *obj;
	lightobj_t *lightData;
		
	l_setstart(model->lights);
	
	while((obj = l_getnext(model->lights)) != NULL) {
		object_dump(obj);
		lightData = &obj->lightData;
		fprintf(out, "Light data:\n");
		tl_print3("   Center coordinates: ", &lightData->center);
		tl_print3("   Emissivity:         ", &lightData->emissivity);
	}	
}
