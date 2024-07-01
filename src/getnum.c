/* CpSc 210

   Implementations of getint() and getdouble()

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** getint **/
int getint(FILE *fp) {
    char buf[256];
    int  code;
    int  result;

    while ((code=fscanf(fp, "%d", &result)) != 1) {
       if (fgets(buf, sizeof(buf), fp) == NULL) {
          fprintf(stderr, "getint[0]: Unexpected EOF\n");
          exit(0);
       }
       if (buf[0] != '#') {
          fprintf(stderr, "getint[%d]: Error in input: \"%s\"\n", code, buf);
          exit(0);
       }
    }
    return(result);
}

/** getdouble **/
double getdouble(FILE *fp) {
    char buf[256];
    int  code;
    double  result;

    while ((code=fscanf(fp, "%lf", &result)) != 1) {
       if (fgets(buf, sizeof(buf), fp) == NULL) {
          fprintf(stderr, "getdouble[0]: Unexpected EOF\n");
          exit(0);
       }
       if (buf[0] != '#') {
          fprintf(stderr, "getdouble[%d]: Error in input: \"%s\"\n", code, buf);
          exit(0);
       }
    }
    return(result);
}

