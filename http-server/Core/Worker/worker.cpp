//
//  worker.cpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#include "worker.hpp"
#include "parser.hpp"

void new_thread_task( int buff_size, char* worker_buff ) {
    Parser *parser = new Parser(buff_size);
    char *tmp = parser->get_parser_buffer();
    
    for(int i = 0; i < buff_size; ++i) {
        tmp[i] = worker_buff[i];
    }
    tmp = 0; worker_buff = 0;
    
    parser->parse_startline();
}


void Worker::init_server( void ) {
    int opt = 1;
    
    for(int i = 0; i < maximum_connections; i++)
        client_socket[i] = 0;
    
    if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        logger->log_error("Master socket init error");
        exit(EXIT_FAILURE);
    }
    
    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
            logger->log_error("Setsockopt error");
            exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
            logger->log_error("Binding error");
            exit(EXIT_FAILURE);
    }
    
    if (listen(master_socket, 3) < 0) {
        logger->log_error("Listener error");
        exit(EXIT_FAILURE);
    }
    
    addrlen = sizeof(address);
    logger->log_main_server_info(port, maximum_connections);
    multiplexor();
}

void Worker::multiplexor( void ) {
    int new_socket;
    
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        
        max_sd = master_socket;
        
        for(int i = 0; i < maximum_connections; i++) {
            sd = client_socket[i];
            if(sd > 0)
                FD_SET(sd, &readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        
        activity = select(max_sd + 1, &readfds, &writefds, &errorfds, NULL);
        
        if(FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                logger->log_error("Accept failed");
                exit(EXIT_FAILURE);
            }
            
            for(int i = 0; i < maximum_connections; i++) {
                if(client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                                    
                    logger->log_new_connection(new_socket, address, i);
                                    
                    conn_info[i].connection_id = i;
                    conn_info[i].connection_socket = new_socket;
                    conn_info[i].linked_data_struct = i;
                                    
                    break;
                }
            }
            
            for(int j = 0; j < maximum_connections; j++) {
                sd = client_socket[j];
                        
                if(FD_ISSET(master_socket, &readfds)) {
                    if((valread = read(sd, buffer, io_buffer_size)) == 0) {
                        getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                        close(sd);
                        client_socket[j] = 0;
                        thread_list.at(j).detach();
                        thread_list.erase(thread_list.begin() + j);
                    } else {
                        //MARK: debug buffer printer
                        debug_buffer_printer();
                        
                        thread_list.push_back(std::thread(new_thread_task, io_buffer_size, buffer));
                        thread_list.at(j).join();
                    }
                }
            }
        }
    }
}

void Worker::debug_buffer_printer( void ) {
    for(int u = 0; u < io_buffer_size; ++u)
            std::cout << buffer[u];
}

void Worker::clean_buffer( void ) {
    for(int u = 0; u < io_buffer_size; ++u)
        buffer[u] = 0;
}
