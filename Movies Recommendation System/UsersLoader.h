//
// Created on 2/21/2022.
//
#ifndef USERFACTORY_H
#define USERFACTORY_H
#include "User.h"

class UsersLoader { //a class for creating a user vector and loading all data to RS.
    public:
    UsersLoader()=delete;
    static std::vector<User> create_users(const std::string& users_file_path,std::unique_ptr<RecommendationSystem>);
};

#endif //USERFACTORY_H
