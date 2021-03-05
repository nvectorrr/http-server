//
//  configurator.hpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#ifndef configurator_hpp
#define configurator_hpp

#include <stdio.h>
#include <map>
#include <string>

class Configuration {
public:
    std::map<std::string, std::string> params;
    
    std::map<std::string, std::string> params_to_map();
    
    Configuration(std::string config_path) {
        this->config_path = config_path;
    }
    
private:
    std::string config_path;
    char config_buffer[3000];
    
    bool open_file(std::string config_path);
};

#endif /* configurator_hpp */
