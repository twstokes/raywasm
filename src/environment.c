#include "ray.h"

/** environment_init **/
env_t *environment_init(FILE *inFP, int columns) {
   env_t *newProjPtr;

   /* Allocate space for environment data */
   newProjPtr = (env_t *) malloc(sizeof(env_t));

   /* Fetch the viewpoint (x, y, z) coordinates */
   newProjPtr->view_point.x = getdouble(inFP);
   newProjPtr->view_point.y = getdouble(inFP);
   newProjPtr->view_point.z = getdouble(inFP);

   /* Fetch the world x and y unit sizes */
   newProjPtr->winWWidth = getdouble(inFP);
   newProjPtr->winWHeight = getdouble(inFP);

   /* Set pixel column and row dimensions */
   newProjPtr->winPWidth = columns;
   newProjPtr->winPHeight =
        (newProjPtr->winWHeight/newProjPtr->winWWidth)*columns;

   return(newProjPtr);
} /* End environment_init */

/** environment_dump **/
void environment_dump(env_t *environment) {
   fprintf(stderr, "Environment Dump:\n");
   fprintf(stderr, "   Viewpoint:  %6.2lf %6.2lf %6.2lf\n",
          environment->view_point.x,
          environment->view_point.y,
          environment->view_point.z);
   fprintf(stderr, "   Pixel size: %6d %6d\n",
          environment->winPWidth,
          environment->winPHeight);
   fprintf(stderr, "   World size: %6.2lf %6.2lf\n",
          environment->winWWidth,
          environment->winWHeight);
   fprintf(stderr, "\n");
} /* end environment_dump */

/** map_pix_to_world **/
triple_t map_pix_to_world (env_t *environment, int x, int y) {
   triple_t world;
   double rx;
   double ry;
   rx = randpix(x);
   ry = randpix(y);
   world.x = (((rx)/
      (environment->winPWidth-1))*environment->winWWidth);
   world.x -= environment->winWWidth/2.0;
   world.y = (((ry)/
      (environment->winPHeight-1))*environment->winWHeight);
   world.y -= environment->winWHeight/2.0;
   world.z = 0;
   return(world);
} /* End map_pix_to_world */

/** Randpix function **/
double randpix(int p){
   double rv1;
   double rv2;
   rv1 = drand48();
   //fprintf(stderr, "Value of P: %d\n", p);
   //fprintf(stderr, "Printing value of rv1: %lf\n", rv1);
   rv2 = rv1 - 0.5;
   //fprintf(stderr, "Printing random number: %lf\n", rv2+p);
   return rv2 + p;
}
