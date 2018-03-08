#include "../../include/FileProcessor.hpp"

string FileProcessor::fileNameGenerator(const int len, string ext = "") {
    string randomizeName = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i(0); i < len; i++) {
        randomizeName.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }

    randomizeName.append(ext);

    return randomizeName;
}

vvi FileProcessor::processLine(string line) {
    regex itemRe("-?[0-9]+");
    smatch itemMatch;
    vvi row;
    string itemTxt;
    istringstream stream(line);

    while (!stream.eof()) {
        stream >> itemTxt;

        auto item_begin = sregex_iterator(itemTxt.begin(), itemTxt.end(), itemRe);
        auto item_end = sregex_iterator();
        int N = distance(item_begin, item_end);
        vi item(N,0);
        int j(0);

        for(sregex_iterator i = item_begin; i != item_end; ++i) {
            item[j] = stoi(i->str());
            j++;
        }

        row.push_back(item);
    }

    return row;
}

string FileProcessor::decryptFile(string filePath, string password) {
    string decodedFilePath = Crypting::decryptFileContent(filePath, password);
    return decodedFilePath;
}

string FileProcessor::encryptFile(string filePath, string password) {
    string cipherFilePath = Crypting::encryptFileContent(filePath, password);
    return cipherFilePath;
}

vvvi FileProcessor::readFile(string filePath, string password) {
    vvvi fileContent;
    try {
        string decodedFilePath = FileProcessor::decryptFile(filePath, password);
        fileContent = FileProcessor::readFile(decodedFilePath);

        if (remove(decodedFilePath.c_str()) != 0)
            throw "Error : Error deleting decrypted file.";
    } catch ( string err ) {
        cerr << err << endl;
    }

    return fileContent;
}

vvvi FileProcessor::readFile(string filePath) {
    vvvi fileContent;
    ifstream inputFile(filePath);
    string line;

    try {
        if (inputFile.is_open()) {
            while (!inputFile.eof()) {
                getline(inputFile, line);
                fileContent.push_back(FileProcessor::processLine(line));
            }
        } else {
            throw "Error : File lecture failed.";
        }
        inputFile.close();

    } catch (string err) {
        cerr << err << endl;
    }

    return fileContent;
}

void FileProcessor::toString(vvvi source) {
    cout << "Number of elements : " <<  (source.size() * source.front().size()) << endl;
    cout << "Matrice" << endl;

    for (const auto& row : source) {
        for (const auto& col : row) {
            for (const auto& item: col)
                cout << item << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    return;
}

int main(int argc, const char ** argv) {
    string filePath = "";
    string password = "";
    string encFilePath = "";

    cout << "Getting arguments : " << argc - 1 << endl;
    if (argc == 2) {
        filePath = argv[1];
        FileProcessor::readFile(filePath);
    } else if (argc == 3) {
        filePath = argv[1];
        password = argv[2];
        encFilePath = FileProcessor::encryptFile(filePath,password);
        FileProcessor::readFile(encFilePath, password);
    }

    return 0;
}
