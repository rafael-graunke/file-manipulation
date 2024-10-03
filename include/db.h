#ifndef _DB_H_
#define _DB_H_

#include <stdbool.h>
#include "movie.h"

typedef struct m_index
{
    int id;
    long addr;
    long next; // addr of the following one, one the extensions
} MovieIndex;

Movie *binsearch_in_memory(Movie **movies, int start, int end, char *name, int *pos, bool *found);
Movie *binsearch_in_file(FILE *movies, int start, int end, char *name, int *pos, bool *found); // This function takes in a bin file with all movies
MovieIndex *index_movies_by_id(char *index_name);

#endif