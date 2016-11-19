#include <iostream>
#include "Compression.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please provide legal file path." << std::endl;
        return 1;
    }
    std::string path = argv[1];
    Compression test(path);
    int isUD = test.UD_check();
    if (isUD) {
        std::cout << "This Code is UD." << std::endl;
    } else {
        std::cout << "This Code is NOT UD." << std::endl;
    }
    return 0;
}