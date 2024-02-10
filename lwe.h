#include <iostream>
#include <random>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<long long>> matrix;


std::random_device rd;


std::string decrypt(matrix encrypted_matrix, std::vector<int> key, double add, int mod) {
    std::string solved_message;
    int message_len = encrypted_matrix.size();
    int dimension = key.size();

    for (int i = 0; i < message_len; i++) {
        int answer = 0;
        for (int x = 0; x < dimension; x++) {
            answer += encrypted_matrix[i][x] * key[x];
        }
        solved_message += (char)((add * round(((encrypted_matrix[i].back() - answer) % mod) / add)) / add);
    }

    return solved_message;
}


matrix encrypt(std::string message, matrix public_matrix, int mod, int add, int max_encryption_vectors) {
    int len = message.size();
    int dimension = public_matrix[0].size();
    std::uniform_int_distribution<int> pub_mat_index(0, public_matrix.size() - 1);
    std::uniform_int_distribution<int> num_encryption_vectors(2, max_encryption_vectors);
    matrix encrypted_message(len, std::vector<long long>(dimension));

    for (int i = 0; i < len; i++) {
        std::vector<long long> vector(dimension);
        for (int j = 0; j < num_encryption_vectors(rd); j++) {
            std::vector<long long> public_vector = public_matrix[pub_mat_index(rd)];
            for (int l = 0; l < dimension; l++) {
                vector[l] += public_vector[l];
            }
        }

        for (int k = 0; k < dimension; k++) {
            encrypted_message[i][k] += vector[k];
        }
        encrypted_message[i][dimension - 1] = (encrypted_message[i][dimension - 1] + ((int)message[i] * add)) % mod;
    }

    return encrypted_message;
}


std::vector<int> create_secret_key(int dimension) {
    std::uniform_int_distribution<int> dist(-8192, 8192);
    std::vector<int> key;

    for (int i = 0; i < dimension; i++) {
        key.push_back(dist(rd));
    }

    return key;
}


matrix create_public_key(std::vector<int> secret_key, int mod, int max_error) {
    int dimension = secret_key.size();
    std::uniform_int_distribution<int> dist(-8192, 8192);
    std::uniform_int_distribution<int> error(-max_error, max_error);
    std::vector<std::vector<long long>> public_key;

    for (int x = 0; x < dimension*10; x++) {
        std::vector<long long> temp_vector;
        long long answer = 0;
        for (int i = 0; i < dimension; i++) {
            int num = dist(rd);
            answer += (num * secret_key[i]);
            temp_vector.push_back(num);
        }
        temp_vector.push_back((answer + error(rd)) % mod);
        public_key.push_back(temp_vector);
    }

    return public_key;
}
