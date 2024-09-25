#ifndef _DB_H_
#define _DB_H_

#include <stdbool.h>
#include "movie.h"

Movie *binsearch_in_memory(Movie **movies, int start, int end, char *name, int *pos, bool *found);

// This function takes in a bin file with all movies
Movie *binsearch_in_file(FILE *movies, int start, int end, char *name, int *pos, bool *found);

#endif