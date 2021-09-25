#include <string>
#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0

std::vector<std::string> list_movies()
{
    std::vector<std::string> list_movies;

    list_movies.push_back("The Lion King");
    list_movies.push_back("Fight Club");
    list_movies.push_back("Star Wars IV");
    list_movies.push_back("Inception");
    list_movies.push_back("Matrix");

    return (list_movies);
}


class IServer
{
    public :
        virtual void getMovies(std::string) = 0;
};

class MovieServer
{

    public:
        virtual bool getMovies(std::string movie_name)
        {
            std::vector<std::string> list_movie = list_movies();
            std::cout << "We looking if we have the movie" << std::endl;
            for (size_t i = 0; i < list_movie.size() ; i++)
            {
                if (movie_name == list_movie[i])
                {
                    std::cout << "Movie found ! Downloading in progress ! Keep Patient ! \nEnjoy !!\n" << std::endl;
                    return (TRUE);
                }
            }
                std::cout << "Movie not found ! Sorry\n" << std::endl;
                return (FALSE);
        }
};

class LocalServer : public MovieServer
{
    private :
        MovieServer *_movie_server;
        std::vector<std::string> _movies_in_cache;
    
        bool check_if_movie_in_cache(std::string movie_to_watch)
        {
            for (size_t i = 0; i < _movies_in_cache.size(); i++)
            {
                if (_movies_in_cache[i] == movie_to_watch)
                    return (TRUE);
            }
            return (FALSE);
        }
    
    public :
        LocalServer(MovieServer *movie_server) : _movie_server(new MovieServer(*movie_server))
        {

        }
        ~LocalServer()
        {
            delete _movie_server;
        }

        virtual bool getMovies(std::string movie_name)
        {
            std::cout << "First, looking if movie is on cache ! " << std::endl;
            if (check_if_movie_in_cache(movie_name))
            {
                std::cout << "Nice, no waiting ! You have already this movie in cache!\n" << std::endl;
            }
            else
            {
                std::cout << "Need to call the original server :(" << std::endl;
                if (_movie_server->getMovies(movie_name))
                    _movies_in_cache.push_back(movie_name);
            }
            return (TRUE);
        }
};

void looking_films(MovieServer & server)
{
    server.getMovies("The Lion King");
    server.getMovies("Inception");
    server.getMovies("Babar");
    server.getMovies("Inception");
}

int main()
{
    MovieServer *movie_server = new MovieServer;
    LocalServer *local_server = new LocalServer(movie_server);

    std::cout << "Distant Server" << std::endl;
    looking_films(*movie_server);
    std::cout << "\nLocal Server" << std::endl;
    looking_films(*local_server);

    delete movie_server;
    delete local_server;
}
