// //
// // Created by itayt on 21/01/2025.
// //
// #include "RecommendationSystemLoader.h"
// #include <fstream>
// #include <sstream>
// #include "RecommendationSystem.h"
//
// std::unique_ptr<RecommendationSystem> RecommendationSystemLoader::create_rs_from_movies(std::string path) {// loading movies to RS from file
//     std::ifstream file(path);
//     std::string line;
//     auto rs = std::make_unique<RecommendationSystem>();
//     while(std::getline(file,line)) { //iterate through all lines of file.
//         std::istringstream stream(line);
//         std::string name;
//         int year;
//         std::vector<double> features;
//         double feature;
//         stream>>name;
//         size_t pos = name.find('-');
//         year = std::stoi(name.substr(pos+1));
//         while (stream >> feature) { //iterate through each feature for movie
//             features.push_back(feature); //create feature vector
//         }
//         sp_movie s = rs->add_movie_to_rs(name.substr(0,pos), year, features);
//     }
//     file.close();
//     return rs;
// }

#include "RecommendationSystemLoader.h"
#include <sstream>
#include <fstream>


#define DASH '-'
#define ERROR_OPEN_FILE "Failed to open the movies file."
#define ERROR_INVALID_FORMAT "Invalid movie details format."
#define ERROR_INVALID_FEATURE "Feature values must be positive."


std::unique_ptr<RecommendationSystem> RecommendationSystemLoader::
create_rs_from_movies(const std::string& movies_file_path) noexcept(false)
{
    // init a unique pointer to new RecommendationSystem
    auto rs = std::make_unique<RecommendationSystem>();

    // Opening file
    std::ifstream in_file(movies_file_path);
    if (!in_file.is_open()) {
        throw std::invalid_argument(ERROR_OPEN_FILE);
    }

    std::string line;

    // Processing each line of the file
    while (std::getline(in_file, line))
    {
        std::istringstream stream(line);

        // Parse movie details (name and year)
        std::string movie_details;
        stream >> movie_details;
        size_t dash = movie_details.find(DASH);
        if (dash == std::string::npos) {
            throw std::invalid_argument(ERROR_INVALID_FORMAT);
        }
        std::string name = movie_details.substr(0, dash);
        int year = std::stoi(movie_details.substr(dash + 1));

        // load feature vector
        std::vector<double> features;
        double feature;
        while (stream >> feature)
        {
            if (feature <= 0 || feature > 10)
            {
                throw std::invalid_argument(ERROR_INVALID_FEATURE);
            }
            features.push_back(feature);
        }

        // Add the movie to the RecommendationSystem
        rs->add_movie_to_rs(name, year, features);
    }

    in_file.close();
    return rs;
}

