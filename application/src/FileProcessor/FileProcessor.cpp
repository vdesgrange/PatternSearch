#include "../../include/FileProcessor.hpp"

Matrice * FileProcessor::processMatrice(int** array2D) {
    return new Matrice();
}

string FileProcessor::decryptFileContent(ifstream file, string password) {
    return "";
}

Mat FileProcessor::readFile(string filePath, string password) {
    cout << "Encrypt file" << endl;
    Crypting::encryptFileContent(filePath, password);
    cout << "Decrypt file" << endl;
    Crypting::decryptFileContent(filePath, password);
    //return FileProcessor::readFile(filePath);
    return Mat(0,0,CV_8UC(0));
}

Mat FileProcessor::readFile(string filePath) {
    Mat source = imread(filePath, CV_LOAD_IMAGE_GRAYSCALE);

    if (source.empty() || !source.data) {
        printf("Error file not found : %s", filePath.c_str());
        return Mat(0,0,CV_8UC(0));
    }

    FileProcessor::toString(source);

    return source;
}

void FileProcessor::toString(Mat source) {
    int item = (int)source.at<uchar>(0,0);
    printf("Number of elements %lu \n", source.total());
    printf("Channels %d \n", source.channels());
    printf("Type %d \n", source.type());
    printf("Dimension %d \n", source.dims);
    //cout << "Mat : \n " <<  source << endl;
    cout << "Item(0,0) : " <<  item << endl;

    printf("Display picture in a window. \n");
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", source);
    waitKey(0);
}

int main(int argc, const char ** argv) {
    string filePath = "";
    string password = "";

    cout << "Getting arguments : " << argc - 1 << endl;
    if (argc == 2) {
        filePath = argv[1];
        FileProcessor::readFile(filePath);
    } else if (argc == 3) {
        filePath = argv[1];
        password = argv[2];
        FileProcessor::readFile(filePath, password);
    }

    return 0;
}
