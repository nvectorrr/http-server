//
//  logger.hpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#ifndef logger_hpp
#define logger_hpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <netinet/in.h>
#include <arpa/inet.h>

class Logger {
public:
    void log_action(std::string action);
    void log_error(std::string error);
    void log_new_connection(int new_socket, struct sockaddr_in address, int i);
    void log_main_server_info(int port, int max_conn);
    
    Logger(std::string log_file_name) {
        this->log_file_name = log_file_name;
        if(!open_file(this->fstream, this->log_file_name)) {
            throw "Logger exeption";
        }
        log_startup();
    }
    
private:
    std::string log_file_name;
    std::ofstream fstream;
    
    bool open_file(std::ofstream& fstream, std::string log_file_name);
    void log_startup();
};

#endif
