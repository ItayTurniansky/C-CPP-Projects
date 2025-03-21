//
// Created by itayt on 19/01/2025.
//
#include "RecommendationSystem.h"

#include <cmath>
#include <queue>

#include "Movie.h"
#define FEATURE_MAX 10
#define FEATURE_MIN 1

void multiply_vector_with_scalar( std::vector<double>& vector, double scalar) { // help function for multiplying vector with scalar
    for( auto& element : vector ) {
        element*=scalar;
    }
}

void find_avg_and_reduce( std::map<sp_movie, double>& watched_movies_rankings_vector) { // help function finding user ranking avg and reducing it from each one(used in recommend by content)
    double sum=0, avg=0;
    int counter=0;
    for( auto& movie : watched_movies_rankings_vector ) {
        sum+=movie.second;
        counter++;
    }
    avg=sum/counter;
    for( auto& movie : watched_movies_rankings_vector ) {
        movie.second -= avg;
    }
}
std::vector<double> add_vectors(const std::vector<std::vector<double>>& vecOfVecs) { // help function that helps create the p vector in recommend by content. add vectors
    size_t dimension = vecOfVecs[0].size();
    std::vector<double> result(dimension, 0.0);
    for (const auto& vec : vecOfVecs) {
        for (size_t i = 0; i < dimension; ++i) {
            result[i] += vec[i];
        }
    }

    return result;
}

std::vector<double> create_preference_vector(std::map<sp_movie,std::vector<double>> watched_movies_features_map,std::map<sp_movie, double> watched_movies_rankings_map ) { //final function for creating the p vector in recommend by content
    std::vector<std::vector<double>> preference_vector_1;
    for (auto & watched_movie : watched_movies_features_map) {
        multiply_vector_with_scalar(watched_movie.second,watched_movies_rankings_map[watched_movie.first]);
        preference_vector_1.push_back(watched_movie.second);
    }
    std::vector<double> preference_vector_final= add_vectors(preference_vector_1);
    return preference_vector_final;
}

double cs_value(const std::vector<double> &v1, const std::vector<double> &v2) { // calculates the cos of the angle between two vectors
    double scalar_mult=0, norm1_sum=0, norm2_sum=0;
    for( size_t i = 0; i < v1.size(); i++ ) {
        scalar_mult+=v1[i]*v2[i];
        norm1_sum += v1[i]*v1[i];
        norm2_sum += v2[i]*v2[i];
    }
    return scalar_mult/ ((std::sqrt(norm1_sum))* (std::sqrt(norm2_sum)));



}
sp_movie find_prefered_movie(const std::vector<double>& preference_vector,const std::map<sp_movie,std::vector<double>>& unwatched_movies_features_map) { //help function that gets all unwatched movies and p vector and calculates each score and returns the maximum one, used in recommend by content.
    std::map<sp_movie,double> unwatched_movies_final_ranks;
    for (auto& unwatched_movie : unwatched_movies_features_map) {
        unwatched_movies_final_ranks[unwatched_movie.first]=cs_value(unwatched_movie.second,preference_vector);
    }
    sp_movie max_movie = unwatched_movies_final_ranks.begin()->first;
    double maxValue = unwatched_movies_final_ranks.begin()->second;

    for (const auto& pair : unwatched_movies_final_ranks) {
        if (pair.second > maxValue) {
            maxValue = pair.second;
            max_movie = pair.first;
        }
    }
    return max_movie;

}

RecommendationSystem::RecommendationSystem() = default; //default constructor

sp_movie RecommendationSystem::get_movie(std::string name, int year) { // returns movie from RS or null if it doesn't exist
    const auto temp = std::make_shared<Movie> (name,year);
    const auto it = rs_map.find(temp);
    if (it == rs_map.end()) {
        return nullptr;
    }
    return it->first;
}

sp_movie RecommendationSystem::add_movie_to_rs(const std::string &name, int year, const std::vector<double> &features) { // adds movie to RS
    for (const auto &feature : features) {
        if (feature>FEATURE_MAX||feature<FEATURE_MIN) {
            throw std::invalid_argument("feature must be between 1 and 10"); //check feature is in range.
        }
    }
    const auto movie = std::make_shared<Movie> (name,year);
    rs_map[movie]=features;
    return movie;
}
std::ostream &operator<<(std::ostream &os, const RecommendationSystem &rs) { // prints all RS movies.
    for (const auto &movie : rs.rs_map) {
        os<<*movie.first;
    }
    return os;
}

sp_movie RecommendationSystem::recommend_by_content(const User &user_rankings) const { // recommend a movie by content using all help functions.by the algorithm in ex5
    std::map<sp_movie, double> watched_movies_rankings_map;
    std::map<sp_movie,std::vector<double>> watched_movies_features_map; //create watched and unwatched vectors of movies.
    std::map<sp_movie,std::vector<double>> unwatched_movies_features_map; //create watched and unwatched vectors of movies.
    rank_map user_rank = user_rankings.get_rank();
    for (auto &rs_movie : this->rs_map) {
        if(user_rank.contains(rs_movie.first)) {
            watched_movies_features_map[rs_movie.first]=rs_movie.second;
            watched_movies_rankings_map[rs_movie.first]=user_rank[rs_movie.first];
        }
        else {
            unwatched_movies_features_map[rs_movie.first]=rs_movie.second;
        }
    }
    find_avg_and_reduce(watched_movies_rankings_map);
    std::vector<double> preference_vector = create_preference_vector(watched_movies_features_map, watched_movies_rankings_map);
    sp_movie result= find_prefered_movie(preference_vector, unwatched_movies_features_map);
    return result;
}


double RecommendationSystem::predict_movie_score(const User &user_rankings, const sp_movie &movie, int k) { // predict movie score by the user watched movies, and the algorithm in ex5.
    std::multimap<double,double> k_highest;
    long unsigned int k_2 = k;
    for (const auto &user_rank : user_rankings.get_rank()) {
        k_highest.emplace(cs_value(this->rs_map[user_rank.first],this->rs_map[movie]),user_rank.second); //create multimap of rating and cs score.
        if(k_highest.size()>k_2) {
            k_highest.erase(k_highest.begin());
        }
    }
    double sum_sc=0, sum_c=0;
    for (const auto& pair : k_highest) {
        sum_sc+=(pair.first*pair.second);
        sum_c+=pair.first;
    }
    return sum_sc/sum_c;
}

sp_movie RecommendationSystem::recommend_by_cf(const User & user_rankings, int k) { //use predict movie score to return the maximum valued movie matched.
    sp_movie result=nullptr;
    const rank_map& user_rank = user_rankings.get_rank();
    double max=0, tmp=0;
    for (auto &rs_movie : this->rs_map) {
        if(user_rank.contains(rs_movie.first)) {
            continue;
        }
        tmp = predict_movie_score(user_rankings, rs_movie.first,k);
            if (tmp>max) {
                max=tmp;
                result = rs_movie.first;
            }
        }
    return result;;
}





