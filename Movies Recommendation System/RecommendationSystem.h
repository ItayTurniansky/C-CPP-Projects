//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include "Movie.h"
#include "map"
class User;
struct CustomComparator { // comparator struct for map of pointers to movies.
    bool operator()(const sp_movie& lhs, const sp_movie& rhs) const {
        return *lhs < *rhs;
    }
};
typedef std::map<sp_movie, std::vector<double>, CustomComparator> movie_map;
class RecommendationSystem
{
private:
    movie_map rs_map;

public:
    RecommendationSystem(); //constructor
    sp_movie get_movie(std::string name, int year); // return movie in RS
    sp_movie add_movie_to_rs(const std::string& name, int year, const std::vector<double>& features); //add movie to RS
    friend std::ostream& operator<<(std::ostream& os, const RecommendationSystem& recommendation_system); //print entire RS
    sp_movie recommend_by_content(const User & user_rankings) const; //recommend a movie by user rankings
    double predict_movie_score(const User & user_rankings, const sp_movie & movie, int k); //predict a movie's score based on user rankings and given algorithm in ex5
    sp_movie recommend_by_cf(const User & user_rankings, int k);// recommend a movie by similarities to watched movies.

};

#endif // RECOMMENDATIONSYSTEM_H
