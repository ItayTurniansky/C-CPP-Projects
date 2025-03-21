
#ifndef EX5_MOVIE_H
#define EX5_MOVIE_H

#include <iostream>
#include <vector>
#include <memory>

#define HASH_START 17



class Movie;

typedef std::shared_ptr<Movie> sp_movie; // define your smart pointer

/**
 * those declartions and typedefs are given to you and should be used in the ex
 */
typedef std::size_t (*hash_func)(const sp_movie& movie);
typedef bool (*equal_func)(const sp_movie& m1,const sp_movie& m2);

std::size_t sp_movie_hash(const sp_movie& movie);

bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2);

class Movie
{

public:
 Movie(std::string name, int year); //constructor
 ~Movie()=default; //destructor
 std::string get_name() const; //return movie name
 int get_year() const; // return movie year
 friend std::ostream& operator<<(std::ostream& os, const Movie& movie); //prints movie by ex5 requirements
 friend bool operator<(const Movie& m1,const Movie& m2); //compare two movies
private:
 std::string name_;
 int year_;
};


#endif //EX5_MOVIE_H
