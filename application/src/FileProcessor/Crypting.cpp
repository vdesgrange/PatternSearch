#include "../../include/Crypting.hpp"

void Crypting::decryptFileContent(string filePath, string password) {
    string inFilePath = "./files/out.enc";
    string outFilePath = "./files/out";
    ifstream in(inFilePath.c_str(), ios::binary);
    ofstream out(outFilePath.c_str(), ios::binary);

    AutoSeeded_RNG rng;
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");

    secure_vector<uint8_t> salt = rng.random_vec(8);
    //rng.randomize(&salt[0], salt.size());


    //OctetString key = pbkdf->derive_key(32, password, &salt[0], salt.size(), 10000).bits_of();
    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(32, password, &salt[0], salt.size(), 10000).bits_of();
    OctetString key(key_and_IV.data(), 32);
    //OctetString iv(key_and_IV.data() +32, 16);

    Pipe pipe(get_cipher("AES-256/CBC/PKCS7", key, DECRYPTION), new Base64_Decoder, new DataSink_Stream(out));
    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    return;
}

void Crypting::encryptFileContent(string filePath, string password) {
    AutoSeeded_RNG rng;

    string outFilePath = "./files/out.enc";
    ifstream in(filePath.c_str(), ios::binary);
    ofstream out(outFilePath.c_str(), ios::binary);

    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt = rng.random_vec(8);

    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(32, password, &salt[0], salt.size(), 10000).bits_of();
    OctetString key(key_and_IV.data(), 32);

    Pipe pipe(get_cipher("AES-256/CBC/PKCS7", key, ENCRYPTION), new Base64_Encoder, new DataSink_Stream(out));
    //Pipe pipe(get_cipher("AES-256/CBC/PKCS7", key, ENCRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    cout << "Sortie : \n" << pipe << endl;

    out.flush();
    out.close();
    in.close();

    return;
    /*ifstream infile (filePath, ios::binary); //, ios::binary
    string content( (istreambuf_iterator<char>(infile) ),
                       (istreambuf_iterator<char>() ) );*/
    /*ifstream inFile;
    inFile.open(filePath);
    stringstream strStream;
    strStream << inFile.rdbuf();
    string str = strStream.str();

    int len = strlen(str.c_str());
    unsigned char encryptedbuffer[128];
    const unsigned char *oneKey = (const unsigned char*)password.c_str();
    AES_KEY key;
    AES_set_encrypt_key(oneKey,128,&key);

    ofstream outFile;
    outFile.open("./files/out.enc");

    for(int i = 0; i <= len; i += 16) {
        AES_encrypt((const unsigned char *) str.c_str() + i, encryptedbuffer, &key);
        for (int k = 0; k <= 16; k++) {
            outFile << encryptedbuffer[k];
        }
    }

    outFile.close();
    inFile.close();*/

    return;
}
