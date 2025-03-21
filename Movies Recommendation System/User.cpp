#include "User.h"
#include "Movie.h"

User::User(const std::string & name, rank_map& ranks, const std::shared_ptr<RecommendationSystem> & rs_ptr)
    :name_(name), ranks_(ranks), rs_ptr_(rs_ptr){}; //constructor

std::string User::get_name() const { //return username
    return name_;
}
const rank_map& User::get_rank() const { //return user ranks
    return ranks_;
}
void User::add_movie_to_user( std::string name, int year, //add movie to user through RS algorithm
                          std::vector<double> features,
                          double rate) {
    auto movie = Movie(name, year);
    std::shared_ptr<Movie> movie_ptr= this->rs_ptr_->add_movie_to_rs(movie.get_name(),movie.get_year(), features);
    this->ranks_[movie_ptr] = rate; //adds movie to user ranks
}
sp_movie User::get_rs_recommendation_by_content() { //all recommendation algorithms are in RS.
    return this->rs_ptr_->recommend_by_content(*this);
}

double User::get_rs_prediction_score_for_movie(const std::string &name, int year, int k) {
    return this->rs_ptr_->predict_movie_score(*this,(this->rs_ptr_)->get_movie(name,year),k);
}
sp_movie User::get_rs_recommendation_by_cf(int k) {
    return this->rs_ptr_->recommend_by_cf(*this, k);
}
std::ostream & operator<<(std::ostream & os, const User & user) { //prints username and then a list of all movies
    os<<"name: "<<user.get_name()<<std::endl;
    os<< *user.rs_ptr_<<std::endl;
    return os;
}





