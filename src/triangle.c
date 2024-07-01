#include "ray.h"

obj_t *triangle_init(FILE *fp, char *objClass) {

	obj_t *new;
	polygon_t *polyPtr;
	triple_t o1, o2;
	double l0, l2;
	triple_t *point0, *point1, *point2;
	triple_t *dir0, *dir1, *dir2;
	triple_t projectPlane;
	

	//call polygon_init() to create new instance of a polygon object
	new = polygon_init(fp, objClass);	

	//malloc space for edges array and set pointer in polygram_t structure
	polyPtr = ((plane_t *)new->typeData)->priv;
	
	polyPtr->edges = malloc(3*sizeof(edge_t));
	
	//set number of edges to 3
	polyPtr->numEdges = 3;

	point0 = &polyPtr->edges[0].point;
	point1 = &polyPtr->edges[1].point;
	point2 = &polyPtr->edges[2].point;

	dir0 = &polyPtr->edges[0].edgeDir;
	dir1 = &polyPtr->edges[1].edgeDir;
	dir2 = &polyPtr->edges[2].edgeDir;

	//set point 0 of triangle to plane’s point
	*point0 = ((plane_t *)new->typeData)->point;

	//set “hits” function pointer to polygon_hits()
	//This was in the psuedo code, but found to be unecessary - already set
	//new->sceneData.hits = polygon_hits;

	//input orientation vector for edge 0
	o1.x = getdouble(fp);
	o1.y = getdouble(fp);
	o1.z = getdouble(fp);

	//input length of edge 0
	l0 = getdouble(fp);

	//project unitized orientation vector onto plane using plane’s unitized normal
	projectPlane = tl_project3(&((plane_t *)new->typeData)->normal, &o1);
	//unitize result
	projectPlane = tl_unitvec3(&projectPlane);
	//scale by edge 0’s length
	projectPlane = tl_scale3(&projectPlane, l0);
	//set point 1’s coordinates to sum of p0 and scaled result
	*point1 = tl_sum3(point0, &projectPlane);	

	//input orientation vector for edge 2
	o2.x = getdouble(fp);
	o2.y = getdouble(fp);
	o2.z = getdouble(fp);

	//input length of edge 2
	l2 = getdouble(fp);

	//project unitized orientation vector onto plane using plane’s unitized normal
	projectPlane = tl_project3(&((plane_t *)new->typeData)->normal, &o2);

	//unitize result
	projectPlane = tl_unitvec3(&projectPlane);

	//scale by edge 2’s length
	projectPlane = tl_scale3(&projectPlane, l2);

	//set point 2’s coordinates to sum of p0 and scaled result
	*point2 = tl_sum3(point0, &projectPlane);	

	//compute and save in edges array unit vector from point 0 to point 1, point 1 to point 2, and finally point 2 to point 0.
	*dir0 = tl_diff3(point1, point0);
	*dir0 = tl_unitvec3(dir0);

	*dir1 = tl_diff3(point2, point1);
	*dir1 = tl_unitvec3(dir1);
	
	*dir2 = tl_diff3(point0, point2);
	*dir2 = tl_unitvec3(dir2);


	return new;
}
