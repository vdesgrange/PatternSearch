#include "../../include/Crypting.hpp"

int AES_BLOCK_SIZE = 128;


void Crypting::decryptFileContent(string filePath, string password) {
    return;
}

void Crypting::encryptFileContent(string filePath, string password) {
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
