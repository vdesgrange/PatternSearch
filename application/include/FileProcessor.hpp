#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Crypting.hpp"
#include "Matrice.hpp"

using namespace cv;
using namespace std;

class FileProcessor {
    public:
        static Mat readFile(string, string);
        static Mat readFile(string);
        static void toString(Mat);

    private:
        Matrice * processMatrice(int** );
        static string decryptFileContent(ifstream, string);
};

#endif
