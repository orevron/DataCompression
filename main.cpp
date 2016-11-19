#include <iostream>
#include "Compression.h"

using namespace std;

int main() {
    std::string path = "C:\\Users\\orevr\\ClionProjects\\data\\DataCompression\\test.txt";
    Compression test(path);
    cout << "is UD: " << test.UD_check() << endl;

    return 0;
}