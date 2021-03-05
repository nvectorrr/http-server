//
//  worker.hpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#ifndef worker_hpp
#define worker_hpp

#include <stdio.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>

#include "logger.hpp"

extern Logger *logger;

struct connection_info {
    int connection_id;
    int connection_socket;
    int linked_data_struct;
};

class Worker {
public:
    Worker(int port, int maximum_connections, int io_buffer_size) {
        this->port = port;
        this->maximum_connections = maximum_connections;
        this->io_buffer_size = io_buffer_size;
        
        this->buffer = new char[this->io_buffer_size];
        this->conn_info = new struct connection_info[this->maximum_connections];
        this->client_socket = new int[this->maximum_connections];
        
        clean_buffer();
        init_server();
    }
    
private:
    int master_socket, addrlen, max_sd, sd;
    int activity;
    ssize_t valread;
    int port, maximum_connections, io_buffer_size, *client_socket;
    char *buffer;
    struct connection_info *conn_info;
    struct sockaddr_in address;
    fd_set readfds, writefds, errorfds;
    
    void init_server( void );
    void multiplexor( void );
    void debug_buffer_printer( void );
    void clean_buffer( void );
};

#endif
