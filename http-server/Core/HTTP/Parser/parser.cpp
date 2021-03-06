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
    int last_i = 0;
    
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
                _buffer[i + 1] = 0;
                last_i = i + 1;
                break;
            }
            http_version += _buffer[i];
            _buffer[i] = 0;
        }
    }
    parse_headers(last_i);
}

void Parser::parse_headers( int start_i ) {
    std::string param = "", value = "", line = "";
    std::vector<std::string> lines;
    int skip_flag = 0, switch_flag = 0;
    
    for(int i = start_i; i < io_buffer_size; ++i) {
        if(skip_flag == 0) {
            if(_buffer[i] == '\n')
                break;
            if(_buffer[i] == '\r') {
                skip_flag = 1;
                lines.push_back(line);
                line = "";
            } else {
                line += _buffer[i];
            }
        } else {
            skip_flag = 0;
        }
    }
    
    //MARK: body container here
    
    for(int i = 0; i < lines.size(); ++i) {
        std::string str = lines.at(i);
        switch_flag = 0;
        param = "";
        value = "";
        
        for(int j = 0; j < str.length(); ++j) {
            if(switch_flag == 0) {
                if(str.at(j) == ':') {
                    switch_flag = 2;
                } else {
                    param += str.at(j);
                }
            } else if(switch_flag == 2) {
                switch_flag = 1;
            } else {
                value += str.at(j);
            }
        }
        if(!(param == "" && value == ""))
            headers.insert(std::pair<std::string, std::string>(param, value));
    }
    print_map(headers);
}

void Parser::print_map( std::map<std::string, std::string> map ) {
    for(auto elem : map) {
       std::cout << "|" << elem.first << "|" << elem.second << "|" << std::endl;
    }
}
