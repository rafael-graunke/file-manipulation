#include <stdio.h>
#include <stdlib.h>

#include "movie.h"
#include "db.h"

int convert_to_bin(void)
{
    FILE *file = fopen("input/arqMovies.txt", "r");
    int count = 0;
    Movie **movies = movie_read_all(file, &count);
    FILE *out = fopen("input/arqMovies.bin", "wb");

    for (int i = 0; i < count; i++)
        fwrite(movies[i], sizeof(Movie), 1, out);

    fclose(out);
    return EXIT_SUCCESS;
}

int run_binsearch_file(void)
{
    int count, pos;
    char name[256];
    bool found;

    printf("Inform the movie name:\n");
    gets(name);

    FILE *file = fopen("input/arqMovies.bin", "rb");
    fseek(file, 0, SEEK_END);
    count = ftell(file) / sizeof(Movie);
    fseek(file, 0, SEEK_SET);

    Movie *movie = binsearch_in_file(file, 0, count - 1, name, &pos, &found);

    if (movie == NULL)
    {
        printf("Movie \"%s\" was not found!\n", name);
        return EXIT_FAILURE;
    }

    printf("Movie \"%s\" found!\n", name);

    return EXIT_SUCCESS;
}

int run_binsearch_memory(void)
{
    int count, pos;
    char name[256];
    bool found;

    printf("Inform the movie name:\n");
    gets(name);

    FILE *file = fopen("input/arqMovies.txt", "r");
    Movie **movies = movie_read_all(file, &count);
    Movie *movie = binsearch_in_memory(movies, 0, count - 1, name, &pos, &found);

    if (movie == NULL)
    {
        printf("Movie \"%s\" was not found!\n", name);
        return EXIT_FAILURE;
    }

    printf("Movie \"%s\" found!\n", name);

    return EXIT_SUCCESS;
}

int main(void)
{
    int option;
    char name[256];

    printf("Choose and option:\n");
    printf(" 1 - Dump text file;\n");
    printf(" 2 - Bin. search in memory;\n");
    printf(" 3 - Bin. search in file (no indexing).\n");

    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        return convert_to_bin();
        break;

    case 2:
        return run_binsearch_memory();
        break;

    case 3:
        return run_binsearch_file();
        break;

    default:
        printf("Invalid option!\n");
    }

    // int iter;
    // FILE *file = fopen("input/arqMovies.bin", "rb");
    // Movie *movie = binsearch_in_file(file, name, &iter);
}
