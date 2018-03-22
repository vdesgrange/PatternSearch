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
    string encrypt = "encrypt";
    CLI cli;

    cout << "Getting arguments : " << argc - 1 << endl;
    if (argc == 2) {
        filePath = argv[1];
        simpleMat = FileProcessor::readFile(filePath);
        mat = FileProcessor::processMatrice(simpleMat);
    } else if (argc == 3) {
        filePath = argv[1];
        password = argv[2];
        simpleMat = FileProcessor::readFile(filePath, password);
        mat = FileProcessor::processMatrice(simpleMat);
    } else if (argc == 4 && argv[1] == encrypt.c_str()) {
        FileProcessor::encryptFile(filePath,password);
        return 0;
    }

    cli.workflow(mat);

/*    pattern.push_back(57);
    pattern.push_back(189);
    pattern.push_back(68);
    pattern.push_back(94);
    pattern.push_back(62);

    cout << Processing::applySearch("searchSequence", mat, pattern) << endl;
*/
    return 0;
}
