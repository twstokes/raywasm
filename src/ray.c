#include "ray.h"

/**/
/* This function traces a single ray and returns the composite */
/* intensity of the light it encounters It is recursive and */
/* so the start of the ray cannot be assumed to be the viewpt */
/* Recursion won't be involved until we take on specular light */
void ray_trace(
model_t *modelP, /* pointer to model container */
triple_t *baseP, /* location of viewer or previous hit */
triple_t *dirP, /* unit vector in direction of object */
triple_t *intensityP, /* intensity return location */
double total_dist, /* distance ray has traveled so far */
obj_t *lastHitP) /* obj that reflected this ray or NULL */
{
/* The ray trace function should rely upon find_closest_object to identify the 
nearest object that is hit by the ray. If none of the objects in the scene is hit, NULL is returned. */

obj_t *closest;
triple_t diff_refl;
triple_t spec_refl;
triple_t u, n, v;
double uDotn;

//fprintf(stderr, "FINDING THE CLOSEST OBJECTTTTTTTTTTTTTTTTT\n");

closest = find_closest_obj(modelP->scene, baseP, dirP, lastHitP);

if (closest == NULL)
	return;

/* Add distance from base to closest object to total_dist */

total_dist += closest->sceneData.distance;

/* Set intensity to the ambient color of closest object */

/*!!!! Could this not be just intensityP = closest->scenedata.color or something close to that? !!!*/

intensityP->x = closest->sceneData.color.x;
intensityP->y = closest->sceneData.color.y;
intensityP->z = closest->sceneData.color.z;

/* Add the diffuse reflectivity of the object at the hitpoint to the intensity triple */

//fprintf(stderr, "CALCULATING DIFF REFL!!!!!!!\n");

diff_refl = diffuse_illumination(modelP, closest);

*intensityP = tl_sum3(intensityP, &diff_refl);

/* Divide intensity by total_dist */

*intensityP = tl_scale3(intensityP, 1/total_dist);

//If the specular value for the object is non-zero {
	if(closest->sceneData.specular != 0) {

	//Determine the vector “v” for the reflected ray;
	//u = -r

	u = tl_scale3(dirP, -1);

	n = closest->sceneData.normal;

	//should be uneccessary
//	n = tl_unitvec3(&n);
//	u = tl_unitvec3(&u);

	//v = 2(u dot n)n-u
	uDotn = tl_dot3(&u, &n);
	v = tl_scale3(&n, 2*uDotn);
	v = tl_diff3(&v, &u);
	v = tl_unitvec3(&v);

	//set reflected_intensity to zeros,
	spec_refl.x = 0;
	spec_refl.y = 0;
	spec_refl.z = 0;

	//Recursively call raytrace() passing the hit point as the new base, “v” as the direction, a pointer to the reflected_intensity and “closest” as the “last_hit” parameter;

	ray_trace(modelP, &closest->sceneData.hitloc, &v, &spec_refl, total_dist, closest);

	//Scale the returned reflected_intensity by the specular value for the original object;

	spec_refl = tl_scale3(&spec_refl, closest->sceneData.specular);
	
	//Add the result to the intensity	

	*intensityP = tl_sum3(intensityP, &spec_refl);

	}

}

obj_t *find_closest_obj(
list_t *scene, /* Scene objects list */
triple_t *basePtr, /* starting coordinates of ray */
triple_t *dirPtr, /* direction of ray */
obj_t *lasthit /* object last hit by ray, or NULL */
) {
	double currentDist;
	double distance = 0;
	obj_t *closest_obj = NULL;

	l_setstart(scene);

	/* No objects in the list */

	if(scene->head == NULL)
		return NULL;

	obj_t *currentObject = scene->head->objPtr;

	while(((currentObject = l_getnext(scene)) != NULL))
	{

		if(currentObject != lasthit) {
	
			currentDist = currentObject->sceneData.hits(basePtr, dirPtr, currentObject);
				
			if((distance == 0 || currentDist < distance) && currentDist > 0) {
				closest_obj = currentObject;
				distance = currentDist;
			}
		}
	}
	
	return closest_obj;
}
