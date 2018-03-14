#include "../../include/FileProcessor.hpp"

/**
 * \brief random filename generator
 * Get length and extension of a filename to create, and
 * generate a random string.
 * \param {const int} len - length of filename
 * \param {string} ext - filename extension
 * \return {string} random file name
 */
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

/**
 * \brief Extract matrix information of a row
 * Receive a string corresponding to a matrix row from the plain text file.
 * Extract matrix's elements (composed of 1 or + dimensions).
 * \param {string} line - matrix row
 * \return {vector<vector<int>>} - A vector X dimensional matrix items.
 */
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

/**
 * \brief Decrypte file encrypted in AES-256/CBC method.
 * Receive file path of a cipher file (encrypted by encryptFile method),
 * and use password to create a decrypted file.
 * \param {string} filePath - cipher file path.
 * \param {string} password - password used for encryption.
 * \return {string} path of decrypted file.
 */
string FileProcessor::decryptFile(string filePath, string password) {
    string decodedFilePath = Crypting::decryptFileContent(filePath, password);
    return decodedFilePath;
}

/**
 * \brief Encrypt file in AES-256-CBC method.
 * Receive plain text file path and use password to create a cipher file.
 * \param {string} filePath - plain text file path.
 * \param {string} password - password used for encryption.
 * \return {string} path of cipher file.
 */
string FileProcessor::encryptFile(string filePath, string password) {
    string cipherFilePath = Crypting::encryptFileContent(filePath, password);
    return cipherFilePath;
}

/**
 * \brief Read cipher matrix file and store it into simple data structure.
 * Receive cipher matrix file, call method to decrypt file and method to
 * read file and store matrix content into simple data structure.
 * \param {string} filePath - plain text file path.
 * \param {string} password - password used for encryption.
 * \return {vvvi} matrice - rows of cols of X dimensional int elements.
 */
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

/**
 * \brief Read plain text matrix file and store it into simple data structure.
 * Receive plain text matrix file, call method to
 * read file and store matrix content into simple data structure.
 * \param {string} filePath - plain text file path.
 * \rturn {vvvi} matrice - rows of cols of X dimensional int elements.
 */
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

/**
 * \brief toString method
 * Display matrice content.
 * \param {vvvi} source - matrice simple data structure (rows of cols of X dimensional int element).
 */
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

/**
 * \brief Get complex matrice structure from file content data.
 * Call matrice complex structure constructor to process plain text file content data.
 * \param {vvvi} data - simple matrice data structure
 * \return {Matrice} complexe Matrice data structure
 */
Matrice* processMatrice(vvvi data) {
    return new Matrice();
}

/**
 * \brief main method. Temporary.
 */
/*int main(int argc, const char ** argv) {
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
}*/
