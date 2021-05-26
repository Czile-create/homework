#include "start.h"

int main(int argc, char * argv[]) {
    if (argv[1][0] != '-')
        _zip(argc, argv);
    else
        _unzip(argv[2]);
    return 0;
}