//
//  main.cpp
//  http-server
//
//  Created by Виктор  Найденович  on 05.03.2021.
//

#include "logger.hpp"
#include "worker.hpp"

Logger *logger = 0;
Worker *worker = 0;

int main(int argc, const char * argv[]) {
    logger = new Logger("log.txt");
    worker = new Worker(1234, 10, 4096);
    return 0;
}
