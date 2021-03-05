//
//  parser.cpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#include "parser.hpp"

void Parser::debug_buffer_printer( void ) {
    for(int u = 0; u < io_buffer_size; ++u)
        
    std::cout << _buffer[u];
}

void Parser::clean_buffer( void ) {
    for(int u = 0; u < io_buffer_size; ++u)
        _buffer[u] = 0;
}

void Parser::parse_startline( void ) {
    std::string method = "", filepath = "", http_version = "";
    
    for(int i = 0; i < io_buffer_size; ++i) {
        if(_buffer[i] == ' ') {
            _buffer[i] = 0;
            break;
        }
        method +=  _buffer[i];
        _buffer[i] = 0;
    }
    
    for(int i = 0; i < io_buffer_size; ++i) {
        if(_buffer[i] != 0) {
            if(_buffer[i] == ' ') {
                _buffer[i] = 0;
                break;
            }
            filepath += _buffer[i];
            _buffer[i] = 0;
        }
    }
    
    for(int i = 0; i < io_buffer_size; ++i) {
        if(_buffer[i] != 0) {
            if(_buffer[i] == '\r') {
                _buffer[i] = 0;
                break;
            }
            http_version += _buffer[i];
            _buffer[i] = 0;
        }
    }
}
