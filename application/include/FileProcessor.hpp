#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <regex>

#include "Crypting.hpp"
#include "Matrice.hpp"

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

using namespace std;

class FileProcessor {
    public:
        static string encryptFile(string, string);
        static vvvi readFile(string, string);
        static vvvi readFile(string);
        static void toString(vvvi);
        static string fileNameGenerator(const int, string);
        static Matrice* processMatrice(vvvi);

    private:
        static string decryptFile(string, string);
        static vvi processLine(string);
};

#endif
