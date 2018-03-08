#ifndef Crypting_hpp
#define Crypting_hpp

#include <iostream>
//#include <stdio.h>
#include <sstream>
#include <string>
//#include <vector>
#include <fstream>
//#include <streambuf>
#include <botan/block_cipher.h>
#include <botan/pipe.h>
#include <botan/auto_rng.h>
//#include <botan/rng.h>
//#include <botan/hex.h>
#include <botan/pbkdf.h>
#include <botan/data_snk.h>
#include <botan/cipher_mode.h>
#include <botan/key_filt.h>
//#include <botan/b64_filt.h>
#include <botan/init.h>

using namespace Botan;
using namespace std;

class Crypting {
    public:
        static string encryptFileContent(string, string);
        static string decryptFileContent(string, string);
};

#endif
