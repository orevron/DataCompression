#include "Compression.h"

/**
 * Constructor
 */
Compression::Compression(std::string path) : dangling(0), list_of_words(0) {
    this->readData(path);
}

/**
 * Read data from input file to memory
 */
void Compression::readData(std::string path) {
    std::ifstream file;
    file.open(path, file.in);
    char line[256];
    if (file.is_open()) {
        while (!file.eof()) {
            file.getline(line, 256);
            list_of_words.emplace_back(extractValue(line));
        }
    } else {
        std::cout << "Bad path." << std::endl;
    }
    file.close();
}

/**
 * Manage the UD check algorithm
 */
bool Compression::UD_check() {
    int *steps = new int;
    for (size_t i = 0; i < sizeof(list_of_words) / sizeof(int); i++) {
        for (size_t j = 0; j < sizeof(list_of_words) / sizeof(int); j++) {
            if (i != j) {
                if (startsWith(list_of_words[i], list_of_words[j], steps)) {
                    int temp = list_of_words[j] << *(steps);
                    dangling.push_back((list_of_words[i] ^ temp));
                }
            }
        }
    }
    return isDanglingInCode();
}

/**
 * Looks for all danglings in the list of words, in order to confirm UD
 */
bool Compression::isDanglingInCode() {
    if (!dangling.size()) {
        return true;
    }
    for (size_t i = 0; i < sizeof(dangling) / sizeof(int); i++) {
        if (contains(dangling[i])) {
            return false;
        }
    }
    return true;

}

/**
 * Looks for one dangling in the list of words
 */
bool Compression::contains(int word) {
    int size = sizeof(list_of_words) / sizeof(int);
    for (int i = 0; i < size; i++) {
        if (word == i) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if word2 is prefix of word1, if yes assign the number of bit shifting to steps variable
 */
bool Compression::startsWith(int word1, int word2, int *steps) {
    int temp = word1;
    int counter = 0;
    while (temp > 0) {
        if ((temp ^ word2) == 0) {
            *steps = counter;
            return true;
        }
        temp = (temp >> 1);
        counter++;
    }
    return false;
}

/**
 * Extract the value of the word from the string
 */
int Compression::extractValue(char *line) {
    int index = 4, ind = 0, check = line[index++], counter = 0, ar[50];
    while (check != 41) {
        counter++;
        ar[ind++] = check - 48;
        check = line[index++];
    }
    check = 0;
    index = 0;
    while (counter-- > 0) {
        check += ar[--ind] * std::pow(10, index++);
    }
    return check;
}
