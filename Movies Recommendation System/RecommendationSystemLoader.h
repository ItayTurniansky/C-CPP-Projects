
#ifndef RECOMMENDATIONSYSTEMLOADER_H
#define RECOMMENDATIONSYSTEMLOADER_H
#include "RecommendationSystem.h"
class RecommendationSystemLoader { //a class for loading movies to RS from file.
public:
    RecommendationSystemLoader()= delete;
    static std::unique_ptr<RecommendationSystem> create_rs_from_movies(const std::string&);
};

#endif // RECOMMENDATIONSYSTEMLOADER_H
