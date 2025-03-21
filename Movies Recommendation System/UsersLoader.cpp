//
// Created by itayt on 21/01/2025.
//
#include "UsersLoader.h"
#include <fstream>
#include <sstream>
#include "RecommendationSystem.h"
#include "User.h"
#include "Movie.h"
#define INIT_BUCKET_SIZE 8

std::vector<User> UsersLoader::create_users(const std::string& users_file_path,std::unique_ptr<RecommendationSystem> rs)
    {
        std::shared_ptr<RecommendationSystem> rs_shared= std::move(rs);
        std::ifstream file(users_file_path);
        if (!file.is_open()) {
            throw std::invalid_argument("File Error");
        }
        std::string line;
        std::vector<std::shared_ptr<Movie>> movies;
        std::vector<User> users;
        std::string name_year;
        std::string name;
        int year;
        std::getline(file, line);
        std::istringstream stream(line);
        while (stream>>name_year) { //create movie vector from input movies
            size_t pos = name_year.find('-');
            year = std::stoi(name_year.substr(pos+1));
            name = name_year.substr(0,pos);
            sp_movie tmp_movie;
            tmp_movie=rs_shared->get_movie(name,year);
            movies.push_back(tmp_movie);
        }

        while(std::getline(file,line)) { //iterate through each user while matching each rank with movie.
            std::istringstream stream_2(line);
            std::string user_name;
            stream_2>>user_name;
            std::string rank;
            int counter= 0;
            rank_map ranks(INIT_BUCKET_SIZE,sp_movie_hash,
                                   sp_movie_equal);            while (stream_2 >>rank ) {
                if(rank!="NA") {
                    double number= std::stod(rank);
                    if (number<1||number>10) {
                        throw std::invalid_argument("Invalid rank");
                    }
                    sp_movie tmp_movie_vector= movies[counter];
                    ranks[tmp_movie_vector] = number;
                    counter++;

                }else {
                    counter++;
                }
            }
            users.emplace_back(user_name,ranks,rs_shared);
        }
        file.close();
        return users;
    }
