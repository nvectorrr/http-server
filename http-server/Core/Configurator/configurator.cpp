//
//  configurator.cpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#include "configurator.hpp"

bool Configuration::open_file(std::string config_path) {
    FILE *F;
    int i = 0, config_size = 0;
    
    if((F = fopen(config_path.c_str(), "rb")) == NULL) {
        throw "--- Configuration file-open error ---";
        return false;
    }
    
    
    return true;
}
