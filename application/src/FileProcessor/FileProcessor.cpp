#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../../include/FileProcessor.hpp"
#include "../../include/Matrice.hpp"

using namespace cv;
using namespace std;

Matrice * FileProcessor::processMatrice(int** array2D) {
    return new Matrice();
}

string FileProcessor::decryptFileContent(string filePath) {
    return "";
}

int** FileProcessor::readFile(string filePath) {
    Mat source = imread(filePath);
    int ** array2D = nullptr;

    if (source.empty() || !source.data) {
        printf("Error loading file : %s", filePath.c_str());
        return nullptr;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", source);
    waitKey(0);

    return array2D;
}

int main(int argc, const char ** argv) {
    string filePath = "../../files/lenaGrayscale.png";
    if (argc != 2) {
        filePath = argv[1];
        cout << "Type : " << filePath << endl;
    }

    FileProcessor::readFile(filePath);
    return 0;
}
