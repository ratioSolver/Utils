#include "crypto.hpp"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>

namespace utils
{
    std::string encode_password(std::string_view password, std::string_view salt)
    {
        int iterations = 10000;
        unsigned char hash[32];
        if (PKCS5_PBKDF2_HMAC(password.data(), password.size(), reinterpret_cast<const unsigned char *>(salt.data()), salt.size(), iterations, EVP_sha256(), sizeof(hash), hash) == 0)
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed");

        std::ostringstream hash_stream;
        for (unsigned char c : hash)
            hash_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        return hash_stream.str();
    }

    std::pair<std::string, std::string> encode_password(std::string_view password)
    {
        unsigned char salt[16];
        RAND_bytes(salt, sizeof(salt));
        std::ostringstream salt_stream;
        for (unsigned char c : salt)
            salt_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        return {salt_stream.str(), encode_password(password, salt_stream.str())};
    }
} // namespace utils
