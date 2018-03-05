#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <string>
#include "Matrice.hpp"

using namespace std;

class FileProcessor {
    public:
        static int** readFile(string);
        Matrice * processMatrice(int** );

    private:
        string decryptFileContent(string);
};

#endif
