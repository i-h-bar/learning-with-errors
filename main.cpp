#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include "lwe.h"


int main() {
    std::uniform_int_distribution<int> dist(111206400, 1112064000);
    int max_char = 1114111;
    int mod = dist(rd);
    int addition = mod / max_char;
    int max_error = addition * 0.05;
    std::cout << max_error << std::endl;
    int max_encryption_vectors = round(addition / (max_error + 1 * 2.0));
    std::vector<int> key = create_secret_key(5);
    auto pub = create_public_key(key, mod, max_error);
    std::string message = "Hello World!";
    auto encrypted = encrypt(message, pub, mod, addition, max_encryption_vectors);
    auto decrypted = decrypt(encrypted, key, addition, mod);
    std::cout << decrypted;

    return 0;
}

