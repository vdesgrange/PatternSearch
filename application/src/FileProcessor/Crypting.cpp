#include "../../include/Crypting.hpp"

void Crypting::decryptFileContent(string filePath, string password) {

    string inFilePath = "./files/out.enc";
    //string saltFilePath = "./files/salt";
    string outFilePath = "./files/out";
    ifstream in(inFilePath.c_str(), ios::binary);
    ofstream out(outFilePath.c_str(), ios::binary);
    istream_iterator<uint8_t> input_iterator_start(in);

    AutoSeeded_RNG rng;
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

    return;
}

void Crypting::encryptFileContent(string filePath, string password) {

    string outFilePath = "./files/out.enc";

    ifstream in(filePath.c_str(), ios::binary);
    ofstream out(outFilePath.c_str(), ios::binary); // ios::binary || ios::app
    ostream_iterator<uint8_t> output_iterator(out);
    /*
    ofstream saltOut(saltFilePath.c_str(), ios::binary);
    ostream_iterator<uint8_t> output_iterator(saltOut);
    saltOut.flush();
    saltOut.close();
    */

    AutoSeeded_RNG rng;
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt = rng.random_vec(16);

    copy(salt.begin(), salt.end(), output_iterator);
    out.flush();

    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV.data(), 32);
    OctetString iv(key_and_IV.data() +32, 16);

    //cout << "Encryption key" << key.as_string() << endl;
    //cout << "Encryption iv" << iv.as_string() << endl;

    Pipe pipe(get_cipher("AES-256/CBC", key, ENCRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    return;
}
