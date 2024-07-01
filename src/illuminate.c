#include "ray.h"

triple_t diffuse_illumination(
model_t *model, /* pointer to model structure */
obj_t *hitobj) /* object that was hit by the ray */
{
	triple_t total_illumination;
	triple_t processLight;
	obj_t *currentLight;

	/* set total_illumination triple to zeros */
	total_illumination.x = 0;
	total_illumination.y = 0;
	total_illumination.z = 0;

	if(model->lights->head == NULL)
		return total_illumination;

	l_setstart(model->lights);

	currentLight = model->lights->head->objPtr;
	
//	for all lights on the light list

	while ((currentLight = l_getnext(model->lights)) != NULL)
	{
//		add return value from process_light(…) to total_illumination

		processLight = process_light(model->scene, hitobj, currentLight);

		total_illumination.x += processLight.x; 
		total_illumination.y += processLight.y;
		total_illumination.z += processLight.z;

		
	}
	
	return total_illumination;
}


triple_t process_light(
list_t *lst, /* List of all scene objects */
obj_t *hitobj, /* The object hit by the ray */
obj_t *lobj) /* the current light source */
{

	obj_t *closestObj;
	triple_t result;
	triple_t hittoLightUnit;
	triple_t surfaceUnit;
	triple_t diffHitLight;
	double distanceToLight;
	double cosine;
	triple_t closestObjDiff;
	double closestObjDist;

	result.x = 0;
	result.y = 0;
	result.z = 0;

	hittoLightUnit = tl_diff3(&lobj->lightData.center, &hitobj->sceneData.hitloc);
	hittoLightUnit = tl_unitvec3(&hittoLightUnit);

	surfaceUnit = tl_unitvec3(&hitobj->sceneData.normal);

	cosine = tl_dot3(&hittoLightUnit, &surfaceUnit);

	if(cosine < 0)
		return result;

	diffHitLight = tl_diff3(&lobj->lightData.center, &hitobj->sceneData.hitloc);
	distanceToLight = tl_length3(&diffHitLight);
	closestObj = find_closest_obj(lst, &hitobj->sceneData.hitloc, &hittoLightUnit, hitobj);	
	
	if(closestObj != NULL) {

		closestObjDiff = tl_diff3(&closestObj->sceneData.hitloc, &hitobj->sceneData.hitloc);
		closestObjDist = tl_length3(&closestObjDiff);

		if(distanceToLight > closestObjDist)
			return result;
	}

	result = tl_scale3(&lobj->lightData.emissivity, hitobj->sceneData.diffuse * cosine * (1 / distanceToLight));

	return result;
}

