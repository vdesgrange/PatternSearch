#include "../../include/Crypting.hpp"
#include "../../include/FileProcessor.hpp"

string Crypting::decryptFileContent(string inFilePath, string password) {

    cout << "File decryption" << endl;

    string decodedFilePath = "./files/" + FileProcessor::fileNameGenerator(10, "");

    ifstream in(inFilePath.c_str(), ios::binary);
    ofstream out(decodedFilePath.c_str(), ios::binary);

    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt;

    char * saltC =  new char[16];
    in.seekg(in.beg);
    in.read(saltC, 16);
    copy(saltC, saltC + 16, back_inserter(salt));

    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV.data(), 32);
    OctetString iv(key_and_IV.data() +32, 16);
    //cout << "Decryption key" << key.as_string() << endl;
    //cout << "Decryption iv" << iv.as_string() << endl;

    Pipe pipe(get_cipher("AES-256/CBC", key, DECRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    cout << decodedFilePath << endl;

    return decodedFilePath;
}

string Crypting::encryptFileContent(string filePath, string password) {

    string encodedFilePath = "./files/" + FileProcessor::fileNameGenerator(10, ".enc");

    ifstream in(filePath.c_str(), ios::binary);
    ofstream out(encodedFilePath.c_str(), ios::binary); // ios::binary || ios::app
    ostream_iterator<uint8_t> output_iterator(out);

    AutoSeeded_RNG rng;
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt = rng.random_vec(16);

    copy(salt.begin(), salt.end(), output_iterator);
    out.flush();

    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV.data(), 32);
    OctetString iv(key_and_IV.data() +32, 16);

    Pipe pipe(get_cipher("AES-256/CBC", key, ENCRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    cout << encodedFilePath << endl;

    return encodedFilePath;
}
