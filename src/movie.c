#include <movie.h>
#include <string.h>

#define TOK_BUFF_SZ 256
#define LINE_BUFF_SZ 512

Movie *movie_read_next(FILE *input)
{
    Movie *movie = (Movie *) malloc(sizeof(Movie));
    char *line = (char *) malloc(LINE_BUFF_SZ);
    fgets(line, LINE_BUFF_SZ, input);

    if (line[0] == '\0')
        return NULL; // Chegou no fim

    char *token;

    // Le o ID do filme
    token = strtok(line, ";");
    if (token == NULL)
        exit(EXIT_FAILURE); // Erro pois o filme precisa ter ID
    movie->id = atoi(token);

    // Le nome do filme
    token = strtok(NULL, ";");
    if (token == NULL)
        exit(EXIT_FAILURE); // Erro pois o filme precisa ter nome
    strncpy(movie->name, token, BUFF_SZ);

    // Le ano do filme (pode ser vazio)
    token = strtok(NULL, ";");
    if (token != NULL)
        movie->year = atoi(token);

    // Le URL do filme (pode ser vazia)
    token = strtok(NULL, ";");
    if (token != NULL)
        strncpy(movie->url, token, BUFF_SZ);

    // Le ID do autor (pode ser vazio)
    token = strtok(NULL, "");
    if (token != NULL)
        movie->director_id = atoi(token);

    return movie;
}

Movie **movie_read_all(FILE *input, int *count)
{
    char *line = (char *) malloc(LINE_BUFF_SZ);
    while (fgets(line, LINE_BUFF_SZ, input)) {
        *count += 1;
    }
    fseek(input, 0, SEEK_SET);

    Movie *movie;
    Movie **movie_list = (Movie **) malloc(sizeof(Movie*)*(*count));
    int i = 0;
    while ((movie = movie_read_next(input)) != NULL)
    {
        movie_list[i] = movie;
        i++;
    }
    return movie_list;
}