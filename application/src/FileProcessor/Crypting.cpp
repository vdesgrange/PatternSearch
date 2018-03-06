#include "../../include/Crypting.hpp"

void Crypting::decryptFileContent(string filePath, string password) {
    string outFilePath = "./files/out";
    ifstream in(filePath.c_str(), ios::binary);
    ofstream out(outFilePath.c_str(), ios::binary);

    AutoSeeded_RNG rng;
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");

    secure_vector<byte> salt(8);
    rng.randomize(&salt[0], salt.size());

    secure_vector<byte> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    OctetString key(key_and_IV.data(), 32);
    OctetString iv(key_and_IV.data() +32, 16);

    Pipe pipe(get_cipher("AES-256/CBC", key, iv, DECRYPTION),new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    return;
}

void Crypting::encryptFileContent(string filePath, string password) {
    /*ifstream infile (filePath, ios::binary); //, ios::binary
    string content( (istreambuf_iterator<char>(infile) ),
                       (istreambuf_iterator<char>() ) );*/

    /*string filePathOut = "./files/out";
    ifstream in(filePath, ios::binary);
    ofstream out(filePath, ios::binary);

    //LibraryInitializer init;
    AutoSeeded_RNG rng;
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");

    SecureVector<byte> salt(8);
    rng.randomize(&salt[0], salt.size());

    SecureVector<byte> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV, 32);
    OctetString iv(key_and_IV +32, 16);
    Pipe pipe(get_cipher("AES-256/CBC", key, iv, ENCRYPTION), new DataSink_Stream(out));

    return;*/
}
