//
//  parser.hpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Parser {
public:
    void parse_startline( void );
    void parse_headers( int start_i );
    void debug_buffer_printer( void );
    void clean_buffer( void );
    void print_map( std::map<std::string, std::string> map );
    
    Parser(int io_buffer_size) {
        this->io_buffer_size = io_buffer_size;
        this->_buffer = new char[io_buffer_size];
        clean_buffer();
    }
    
    char* get_parser_buffer( void ) {
        return _buffer;
    }
    
private:
    char *_buffer;
    int io_buffer_size;
    std::string method = "", filepath = "", http_version = "";
    std::map<std::string, std::string> headers;
};

#endif
