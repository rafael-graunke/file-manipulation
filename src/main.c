#include <stdio.h>
#include <stdlib.h>

#include "movie.h"
#include "db.h"

void convert_to_bin(void)
{
    FILE *file = fopen("input/arqMovies.txt", "r");
    int count = 0;
    Movie **movies = movie_read_all(file, &count);
    FILE *out = fopen("input/arqMovies.bin", "wb");

    for (int i = 0; i < count; i++)
        fwrite(movies[i], sizeof(Movie), 1, out);
}

int main(void)
{
    char name[256] = "Toy Story";

    FILE *file = fopen("input/arqMovies.bin", "rb");
    Movie *movie = binsearch_in_file(file, name);

    // FILE *file = fopen("input/arqMovies.txt", "r");
    // Movie *movie = binsearch_in_memory(file, name);

    if (movie == NULL)
    {
        printf("Movie \"%s\" was not found!\n", name);
        return EXIT_FAILURE;
    }

    printf("Movie found!\n");

    return EXIT_SUCCESS;
}
