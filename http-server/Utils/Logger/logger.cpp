//
//  logger.cpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#include "logger.hpp"

bool Logger::open_file(std::ofstream &fstream, std::string log_file_name) {
    std::string log_correction = "../" + log_file_name;
    
    fstream.open(log_correction);
    if(!fstream.is_open()) {
        throw "--- Logger file-open failed ---";
        return false;
    }
    
    return true;
}

void Logger::log_startup() {
    std::time_t t = std::time(nullptr);
    fstream << std::put_time(std::localtime(&t), "%c %Z") <<": Logger started..." << std::endl;
}

void Logger::log_main_server_info(int port, int max_conn) {
    std::time_t t = std::time(nullptr);
    fstream << "\n\n" << std::put_time(std::localtime(&t), "%c %Z") << ": Server started on port: " << port << ", maximum_connections = " << max_conn << "\n\n" << std::endl;
}

void Logger::log_action(std::string action) {
    std::time_t t = std::time(nullptr);
    fstream << "\n\n" << std::put_time(std::localtime(&t), "%c %Z") << "ACTION: " << action << "\n\n" << std::endl;
}

void Logger::log_error(std::string error) {
    std::time_t t = std::time(nullptr);
    fstream << "\n\n\n" << std::put_time(std::localtime(&t), "%c %Z") << "ERROR: " << error << "\n\n" << "Server stopped!" << std::endl;
}

void Logger::log_new_connection(int new_socket, struct sockaddr_in address, int i) {
    std::time_t t = std::time(nullptr);
    fstream << std::put_time(std::localtime(&t), "%c %Z") << ": New connection: socket fd is " << new_socket << ", ip is: " << inet_ntoa(address.sin_addr) << ", port: " << ntohs(address.sin_port) << std::endl;
    fstream << "\t\t\tAdded to the list of sockets as: " << i << "\n\n " << std::endl;
}
