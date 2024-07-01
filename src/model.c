#include "ray.h"

/**/
obj_t *error_init(FILE *in, char *objclass) {
fprintf(stderr, "Unknown object class \"%s\"\n", objclass);
return(NULL);
}
/**/
void error_dump(FILE *out, obj_t *objPtr) {
fprintf(stderr, "Unknown object type \"%s\"\n", objPtr->objclass);
}
/* Supported objects */
struct {
char *className;
obj_t *(*classInit)();
void (*classDump) ();
} classes[] = {{"pointlight", light_init, light_dump},{"sphere", sphere_init, sphere_dump},{"plane", plane_init, plane_dump},{"triangle", triangle_init, polygon_dump},{"rectangle", rectangle_init, polygon_dump},{NULL, error_init,error_dump}};

/** model_init **/
int model_init(FILE *in,model_t *model) {
   char  buf[256];
   char  objclass[128];
   obj_t *new;
   int classNdx;


/* Load the objects in the scene */
   while (fscanf(in, "%128s", objclass) == 1)
   {
      /* The word just inputted must be either a class name or the
         beginning of a comment 
      */
      if (objclass[0] == '#') {
         /* It's a comment -- skip the rest of the line */
         fgets(buf, sizeof(buf), in); /* consume rest of line */
      }
      else {
       for (classNdx = 0; classes[classNdx].className != NULL; classNdx++) {
	if (strcasecmp(objclass, classes[classNdx].className) == 0) {
		break;
	}
     }
	
/* Call the object initialization routine */
	new = classes[classNdx].classInit(in, objclass);
	if (new == NULL) {
		fprintf(stderr, "failed to load type %s \n", objclass);
		model_dump(stderr, model);
		exit(2);
	}
	else if(classNdx == 0){
		l_add(model->lights, new);
	}
	else {
		l_add(model->scene, new);
	}
}
} /* End else "not a comment" */

   return(0);
}

/** model_dump **/
void model_dump(FILE *out, model_t *model) {
   obj_t *obj;
   int classNdx;

   l_setstart(model->scene);
   while ((obj = l_getnext(model->scene)) != NULL)
   {
     for (classNdx = 0; classes[classNdx].className != NULL; classNdx++) {
		if (strcasecmp(obj->objclass, classes[classNdx].className) == 0) {
			break;
		}
	}
	classes[classNdx].classDump(out, obj);
   }
}
