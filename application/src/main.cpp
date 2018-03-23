#include "../include/CLI.hpp"
#include "../include/Matrice.hpp"
#include "../include/Search.hpp"
#include "../include/SearchSequence.hpp"
#include "../include/Processing.hpp"
#include "../include/FileProcessor.hpp"

int main(int argc, const char **argv) {
    vvvi simpleMat;
    Matrice* mat = nullptr;
    vector<int> pattern;
    string filePath = "";
    string password = "";
    string encrypt;
    CLI cli;

    cout << "Getting arguments : " << argc - 1 << endl;
    if (argc == 2) {
        filePath = argv[1];
        simpleMat = FileProcessor::readFile(filePath);
        mat = FileProcessor::processMatrice(simpleMat);
        cli.workflow(mat);
    } else if (argc == 3) {
        filePath = argv[1];
        password = argv[2];
        simpleMat = FileProcessor::readFile(filePath, password);
        mat = FileProcessor::processMatrice(simpleMat);
        cli.workflow(mat);
    } else if (argc == 4) {
        encrypt = argv[1];
        if (encrypt == "encrypt") {
            filePath = argv[2];
            password = argv[3];
            FileProcessor::encryptFile(filePath,password);
        }
        return 0;
    }

    return 0;
}
