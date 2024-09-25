#include <string.h>
#include <math.h>
#include "db.h"

Movie *binsearch_in_memory(Movie **movies, int start, int end, char *name, int *pos, bool *found)
{
    int middle;
    *found = false;
    Movie *cursor;
    if (start <= end)
    {
        middle = (end + start) / 2;
        cursor = movies[middle];

        int cmp = strcmp(name, cursor->name);
        if (cmp == 0)
        {
            *found = true;
            *pos = middle;
            return cursor;
        }

        else if (cmp < 0)
            return binsearch_in_memory(movies, start, middle - 1, name, pos, found);
        else
            return binsearch_in_memory(movies, middle + 1, end, name, pos, found);
    }

    return NULL;
}

Movie *binsearch_in_file(FILE *movies, int start, int end, char *name, int *pos, bool *found)
{
    int middle;
    *found = false;
    Movie *cursor = (Movie *)malloc(sizeof(Movie));

    if (start <= end)
    {
        middle = (end + start) / 2;
        fseek(movies, sizeof(Movie) * middle, SEEK_SET);
        fread(cursor, sizeof(Movie), 1, movies);

        int cmp = strcmp(name, cursor->name);

        if (cmp == 0)
        {
            *found = true;
            *pos = middle;
            return cursor;
        }

        else if (cmp < 0)
            return binsearch_in_file(movies, start, middle - 1, name, pos, found);
        else
            return binsearch_in_file(movies, middle + 1, end, name, pos, found);
    }

    return NULL;
}