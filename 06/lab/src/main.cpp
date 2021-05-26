#include "start.h"
#include <string.h>
#include <iostream>

int main(int argc, char * argv[]) {
    if (!strcmp(argv[1], "zip"))
        _zip(argc, argv);
    else if (!strcmp(argv[1], "unzip"))
        _unzip(argv[2]);
    else 
        std::cerr<<"Parameter Error!\n";
    return 0;
}