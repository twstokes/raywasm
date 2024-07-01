#include "ray.h"

obj_t *rectangle_init(FILE *fp, char *objClass) {

	obj_t *new;
	polygon_t *polyPtr;
	triple_t o1;
	double width, height;
	triple_t *point0, *point1, *point2, *point3;
	triple_t *dir0, *dir1, *dir2, *dir3;
	triple_t cross;
	triple_t projectPlane;
	triple_t o1Unit;

	//call polygon_init() to create new instance of a polygon object
	new = polygon_init(fp, objClass);

	polyPtr = ((plane_t *)new->typeData)->priv;
	
	//malloc space for edges array and set pointer in polygram_t structure
	polyPtr->edges = malloc(4*sizeof(edge_t));
	
	//set number of edges to 4
	polyPtr->numEdges = 4;

	point0 = &polyPtr->edges[0].point;
	point1 = &polyPtr->edges[1].point;
	point2 = &polyPtr->edges[2].point;
	point3 = &polyPtr->edges[3].point;
	dir0 = &polyPtr->edges[0].edgeDir;
	dir1 = &polyPtr->edges[1].edgeDir;
	dir2 = &polyPtr->edges[2].edgeDir;
	dir3 = &polyPtr->edges[3].edgeDir;
	
	//set point 0 of rectangle to plane’s point
	*point0 = ((plane_t *)new->typeData)->point;
	
	//set “hits” function pointer to polygon_hits()
	//This was in the psuedo code, but found to be unecessary - already set
	//new->sceneData.hits = polygon_hits;
	
	//input orientation for edge 1
	o1.x = getdouble(fp);
	o1.y = getdouble(fp);
	o1.z = getdouble(fp);

	o1Unit = tl_unitvec3(&o1);

	//input width and height
	width = getdouble(fp);
	height = getdouble(fp);

	//project unitized orientation vector onto plane using plane’s unitized normal
	projectPlane = tl_project3(&((plane_t *)new->typeData)->normal, &o1Unit);
	
	//unitize result
	projectPlane = tl_unitvec3(&projectPlane);

	//scale by plane’s width
	projectPlane = tl_scale3(&projectPlane, width);

	//set point 1’s coordinates to sum of p0 and scaled result
	*point1 = tl_sum3(point0, &projectPlane);

	//compute cross product of plane’s unitized normal and edge 0
	cross = tl_cross3(&((plane_t *)new->typeData)->normal, &o1);

	//unitize result
	cross = tl_unitvec3(&cross);

	//scale by plane’s height
	cross = tl_scale3(&cross, height);

	//set point 2’s coordinates to sum of p1 and scaled result
	*point2 = tl_sum3(point1, &cross);

	//set point 3’s coordinates to sum of p0 and scaled result
	*point3 = tl_sum3(point0, &cross);

	//compute and save in edges array unit vector from point 0 to point 1, point 1 to point 2, point 2 to point 3, and finally point 3 to point 0.
	*dir0 = tl_diff3(point1, point0);
	*dir0 = tl_unitvec3(dir0);
	*dir1 = tl_diff3(point2, point1);
	*dir1 = tl_unitvec3(dir1);
	*dir2 = tl_diff3(point3, point2);
	*dir2 = tl_unitvec3(dir2);
	*dir3 = tl_diff3(point0, point3);
	*dir3 = tl_unitvec3(dir3);

	return new;
	
}
