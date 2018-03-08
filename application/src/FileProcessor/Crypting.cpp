#include "../../include/Crypting.hpp"
#include "../../include/FileProcessor.hpp"

/**
 * \brief Decrypt cipher file.
 * Use Botan crypto library to decrypt cipher file.
 * File have been previously encrypted with AES-256/CBC algorithm.
 * User password is use to derive a Key and an Initialiation Vector.
 * Salt used to retrieved Key and IV is stored into cipher file.
 * \param {string} inFilePath - cipher file path
 * \param {string} password
 * \return {string} decrypted file path
 */
string Crypting::decryptFileContent(string inFilePath, string password) {

    cout << "File decryption" << endl;

    string decodedFilePath = "./files/" + FileProcessor::fileNameGenerator(10, "");

    ifstream in(inFilePath.c_str(), ios::binary);
    ofstream out(decodedFilePath.c_str(), ios::binary);
    // PBKDF(SHA-256) - method to derive key and IV from passphrase.
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt;

    // 16 char blocks Salt used to create key and IV is store at the beginning of cipher file.
    char * saltC =  new char[16];
    in.seekg(in.beg); // Reset ifstream to file begin.
    in.read(saltC, 16); // Retrieve first 16 char blocks.
    copy(saltC, saltC + 16, back_inserter(salt)); // Store into salt data structure.

    // Derive key and IV from password and salt.
    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV.data(), 32); // Get Key
    OctetString iv(key_and_IV.data() +32, 16); // Get IV

    // Construct pipe with AES-256/CBC decryption filter. Output stream.
    Pipe pipe(get_cipher("AES-256/CBC", key, DECRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close();
    in.close();

    return decodedFilePath;
}

/**
 * \brief Crypt plain textfile.
 * Use Botan crypto library to crypt plain text file.
 * File is encrypted with AES-256/CBC algorithm.
 * A password is use to derive a Key and an Initialiation Vector.
 * Salt used to derived Key and IV is stored into cipher file, to be used for decryption..
 * \param {string} filePath - plain text file path
 * \param {string} password - passphrase used to derive key and iv.
 * \return {string} cipher file path
 */
string Crypting::encryptFileContent(string filePath, string password) {

    string encodedFilePath = "./files/" + FileProcessor::fileNameGenerator(10, ".enc");

    ifstream in(filePath.c_str(), ios::binary);
    ofstream out(encodedFilePath.c_str(), ios::binary); // ios::binary || ios::app
    ostream_iterator<uint8_t> output_iterator(out);

    AutoSeeded_RNG rng;
    // PBKDF(SHA-256) - method to derive key and IV from passphrase.
    PBKDF* pbkdf = get_pbkdf("PBKDF2(SHA-256)");
    secure_vector<uint8_t> salt = rng.random_vec(16); // Generate 16 char blocks salt.

    copy(salt.begin(), salt.end(), output_iterator); // Store salt.
    out.flush();

    // Derive key and IV from password and salt.
    secure_vector<uint8_t> key_and_IV = pbkdf->derive_key(48, password, &salt[0], salt.size(), 10000).bits_of();
    SymmetricKey key(key_and_IV.data(), 32); // Get Key
    OctetString iv(key_and_IV.data() +32, 16); // Get IV

    // Construct pipe with AES-256/CBC encryption filter. Output stream.
    Pipe pipe(get_cipher("AES-256/CBC", key, ENCRYPTION), new DataSink_Stream(out));

    pipe.start_msg();
    in >> pipe;
    pipe.end_msg();

    out.flush();
    out.close(); // Cipher file.
    in.close();

    return encodedFilePath;
}
