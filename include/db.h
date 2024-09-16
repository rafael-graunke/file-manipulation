#ifndef _DB_H_
#define _DB_H_

#include "movie.h"

Movie *binsearch_in_memory(FILE *input, char *name);

// This function takes in a bin file with all movies
Movie *binsearch_in_file(FILE *input, char *name);

#endif