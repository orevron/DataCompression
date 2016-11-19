#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>


#ifndef DATACOMPRESSION_COMPRESSION_H
#define DATACOMPRESSION_COMPRESSION_H


class Compression {
    private:
        std::vector<int> dangling;
        bool startsWith(int word1, int word2, int *steps);
        bool isDanglingInCode();
        std::vector<int> list_of_words;
        void readData(std::string path);
        bool contains(int word);
        int extractValue(char *line);
    public:
        Compression(std::string path);
        bool UD_check();
};


#endif //DATACOMPRESSION_COMPRESSION_H
