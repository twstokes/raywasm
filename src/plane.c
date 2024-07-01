#include "ray.h"

/** plane_init() */
obj_t *plane_init(FILE *fp, char *objClass) {
    obj_t *new;
    plane_t *newPlane;

    /* Create new instance of a plane object */
    assert((new = sceneobj_init(fp, objClass)) != NULL);

    /* Create plane specific part */
    assert((newPlane = (plane_t *)malloc(sizeof(plane_t))) != NULL);

    /* Get plane specific data */
    newPlane->point.x = getdouble(fp);
    newPlane->point.y = getdouble(fp);
    newPlane->point.z = getdouble(fp);
    newPlane->normal.x = getdouble(fp);
    newPlane->normal.y = getdouble(fp);
    newPlane->normal.z = getdouble(fp);

    newPlane->normal = tl_unitvec3(&newPlane->normal);

    /* Link plane specific data to object */
    new->typeData = newPlane;

    new->sceneData.hits = plane_hits;

    return(new);
}
   
/** plane_dump() */
void plane_dump(FILE *out, obj_t *objPtr) {
   plane_t *privPtr;

   sceneobj_dump(objPtr);
   
   privPtr = objPtr->typeData;

   fprintf(out, "   Plane data:\n");
   tl_print3(      "      Normal vector:     ", &privPtr->normal);
   tl_print3(      "      Point Coordinates: ", &privPtr->point);
}

double plane_hits(triple_t *base, triple_t *dir, obj_t *obj) {
   double t;
   plane_t *plane = obj->typeData;
   double NdotQ;
   double NdotD;
   double NdotV;
   double NdotRN;
   triple_t Base2Hit, revNormal;

   /* Compute components of distance function */
   NdotD = tl_dot3(&plane->normal, dir);
   if (NdotD == 0) {
      /* Miss -- plane parallel with ray */
      return(-1);
   }

   NdotQ = tl_dot3(&plane->normal, &plane->point);
   NdotV = tl_dot3(&plane->normal, base);
   /* Compute distance */
   t = (NdotQ - NdotV) /  NdotD;
   if (t < 0) {
      /* Miss -- hit point behind viewpoint */
      return(-1);
   }

   /* Hit -- compute hit location */
   Base2Hit = tl_scale3(dir, t);
   obj->sceneData.hitloc = tl_sum3(base, &Base2Hit); 

   if (obj->sceneData.hitloc.z > 0) {
      /* Object between base and screen */
      return(-1);
   }

   /* Set rest of hit-related fields and fix normal to hitpoint issue **/
   revNormal = tl_scale3(&obj->sceneData.hitloc, -1);
   NdotRN = tl_dot3(&plane->normal, &revNormal);

   if(NdotRN > 0)
	obj->sceneData.normal = plane->normal;
   else
   	obj->sceneData.normal = revNormal;

   obj->sceneData.distance = t;

   return(t);
}
