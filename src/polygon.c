#include "ray.h"

/**/
obj_t *polygon_init(FILE *in, char *objclass)
{
	obj_t *new;
	plane_t *typeDataPtr;
	polygon_t *newPolygon;

	new = plane_init(in, objclass);

	//newPolygon = malloc’d space for polygon_t structure
	newPolygon = malloc(sizeof(polygon_t));

	//set priv pointer in plane_t structure to newPolygon

	typeDataPtr = new->typeData;

	typeDataPtr->priv = newPolygon;

	//reset objects hit’s function to polygon_hits()

	new->sceneData.hits = polygon_hits;

	return(new);
}

void polygon_dump(FILE *out, obj_t *objPtr) {

	plane_dump(out, objPtr);
	int i;
	plane_t *typeDataPtr;

	typeDataPtr = objPtr->typeData;

	polygon_t *privPtr = typeDataPtr->priv;
	
	fprintf(out, "Polygon data:\n");
	fprintf(out, "  Number of edges: %d\n", privPtr->numEdges);
	for(i = 0; i< privPtr->numEdges; i++) {
		fprintf(out, "  Edge %d: ", i);
		tl_print3("    Point:	 ", &(privPtr->edges + i)->point);
		tl_print3("    Direction: ", &(privPtr->edges + i)->edgeDir);
	}
	fprintf(out, "\n");
}

double polygon_hits(triple_t *base, triple_t *dir, obj_t *obj){

	double planeHitsReturn;	
	int i, edges;
	plane_t *typeDataPtr;

	typeDataPtr = obj->typeData;

	polygon_t *privPtr = typeDataPtr->priv;

	triple_t unitVecEdgeHit;
	triple_t diffVecEdge;
	triple_t crossVector;
	double dotCrossNormal;
	double lastDot;


	//call plane_hits(), if it returns -1 then return -1
	planeHitsReturn = (plane_hits(base, dir, obj));
	
	if(planeHitsReturn == -1)
		return -1;

	edges = privPtr->numEdges;

	//	for each edge {
	for(i=0; i<edges; i++){
		//compute a unit vector from the edge’s point to the hit location returned by plane_hits()
		diffVecEdge = tl_diff3(&obj->sceneData.hitloc, &privPtr->edges[i].point);

		unitVecEdgeHit = tl_unitvec3(&diffVecEdge);

		//take the cross product of the edge’s director vector with the vector to the hit point
		crossVector = tl_cross3(&privPtr->edges[i].edgeDir, &unitVecEdgeHit);

		//unitize the cross prduct result
		crossVector = tl_unitvec3(&crossVector);

		//compute the dot product of the unitized cross product result with the plane’s normal
		dotCrossNormal = tl_dot3(&crossVector, &typeDataPtr->normal);
	
		//if not the first edge,
		if(i != 0){
		//	if the sign of the dot product is different from the sign of the last dot product,
			if(dotCrossNormal * lastDot < 0)
					return -1;
		}
		//save the dot product as the last dot product value
		lastDot = dotCrossNormal;
	}
	
	return planeHitsReturn;

}
