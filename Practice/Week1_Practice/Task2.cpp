#include <iostream>
#include <cstring>

constexpr int NAME_SIZE = 100; 
constexpr int MAX_MOVIES = 100;

enum Genre {
    Comedy,
    Action, 
    Horror,
    Romantic
};

struct Movie
{
    char name[NAME_SIZE];
    int duration;
    Genre genre;
    double rating;
};

Movie createMovie(const char name[NAME_SIZE], int duration, Genre genre, double rating) {
    Movie movie;
    std::strncpy(movie.name, name, NAME_SIZE - 1);
    movie.name[NAME_SIZE - 1] = '\0';
    movie.duration = duration;
    movie.genre = genre;
    movie.rating = rating;
    return movie;
}

void printGenre(Genre g) {
    switch (g) {
        case Comedy: std::cout << "Comedy"; break;
        case Action: std::cout << "Action"; break;
        case Horror: std::cout << "Horror"; break;
        case Romantic: std::cout << "Romantic"; break;
        default: std::cout << "Unknown"; break;
    }
}

void printMovieInfo(const Movie& movie) {
    std::cout << "Movie: " << movie.name << "\n";
    std::cout << "Duration: " << movie.duration << " minutes\n";
    std::cout << "Genre: "; 
    printGenre(movie.genre);
    std::cout << "\n";
    std::cout << "Rating: " << movie.rating << "\n";
}

void printAllMovies(const Movie movies[], int size) {
    if(size == 0) {
        std::cout<<"No movies available in the library.\n";
        return;
    }

    std::cout<<"List of movies:"<< std::endl;
    for(int i = 0; i < size; i++) {
        std::cout<<"Movie " << i + 1 << std::endl;
        printMovieInfo(movies[i]);
        std::cout << std::endl;
    }
}

void printTopMovies(const Movie movies[], int size) {
    if(size == 0) {
        std::cout<<"No movies available in the library.\n";
        return;
    }

    int topMovieIndex = 0;
    for(int i = 1; i < size; i++) {
        if(movies[i].rating > movies[topMovieIndex].rating) {
            topMovieIndex = i;
        }
    }

    std::cout << "Top Movie:\n";
    printMovieInfo(movies[topMovieIndex]);
}

void readMovieName(char name[], int size) {

    int i = 0;
    char ch;

    while (i < size - 1) {
        std::cin.get(ch);  // Read character

        if (ch == '\n') {   // Stop at newline
            break;
        }

        name[i++] = ch;  // Store character
    }

    name[i] = '\0';  // Null terminate the string
}

Genre readGenre() {
    int choice;
    std::cout << "Select genre:\n";
    std::cout << "1. Comedy\n";
    std::cout << "2. Action\n";
    std::cout << "3. Horror\n";
    std::cout << "4. Romantic\n";
    std::cout << "Enter the number corresponding to the genre: ";
    std::cin >> choice;

    // В зависимост от избора, връщаме съответния жанр
    switch (choice) {
        case 1: return Comedy;
        case 2: return Action;
        case 3: return Horror;
        case 4: return Romantic;
        default:
            std::cout << "Invalid choice, defaulting to Comedy.\n";
            return Comedy;
    }
}


void enterMovies(Movie movies[], int& count) {
    std::cout << "Enter number of movies (max " << MAX_MOVIES << "): ";
    std::cin >> count;  // Get the number of movies

    if (count > MAX_MOVIES) {
        std::cout << "You can enter up to " << MAX_MOVIES << " movies." << std::endl;
        count = MAX_MOVIES;
    }

    // Ignore the newline left by std::cin >> count
    std::cin.ignore();

    for (int i = 0; i < count; ++i) {
        std::cout << "Enter name for movie " << i + 1 << ": ";
        readMovieName(movies[i].name, NAME_SIZE);

        std::cout << "Enter duration for movie " << i + 1 << " (in minutes): ";
        std::cin >> movies[i].duration;

        movies[i].genre = readGenre();

        std::cout << "Enter rating for movie " << i + 1 << " (0 to 10): ";
        std::cin >> movies[i].rating;

        // Again, we ignore the newline left by the previous input
        std::cin.ignore();
    }
}

int main() {
    Movie movies[MAX_MOVIES];  
    int movieCount = 0;

    enterMovies(movies, movieCount);  
    std::cout<<std::endl;
    printAllMovies(movies, movieCount);  
    std::cout<<std::endl;
    printTopMovies(movies, movieCount);

    return 0;
}
