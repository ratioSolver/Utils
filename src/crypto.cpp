#include "crypto.hpp"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/buffer.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>

namespace utils
{
    std::string sha1(std::string_view input)
    {
        unsigned char hash[SHA_DIGEST_LENGTH]; // SHA_DIGEST_LENGTH is 20
        SHA1(reinterpret_cast<const unsigned char *>(input.data()), input.size(), hash);

        std::ostringstream oss;
        for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);

        return oss.str();
    }

    std::string sha256(std::string_view input)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH]; // SHA256_DIGEST_LENGTH is 32
        SHA256(reinterpret_cast<const unsigned char *>(input.data()), input.size(), hash);

        std::ostringstream oss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);

        return oss.str();
    }

    std::string base64_encode(std::string_view input)
    {
        BIO *bio, *b64;
        BUF_MEM *bufferPtr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        BIO_push(bio, b64);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines

        BIO_write(bio, input.data(), static_cast<int>(input.size()));
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bufferPtr);

        std::string result(bufferPtr->data, bufferPtr->length);
        BIO_free_all(bio);

        return result;
    }

    std::string base64_decode(std::string_view input)
    {
        BIO *bio, *b64;
        char buffer[1024];
        int length;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new_mem_buf(input.data(), static_cast<int>(input.size()));
        BIO_push(bio, b64);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines

        length = BIO_read(bio, buffer, static_cast<int>(input.size()));
        buffer[length] = '\0';

        std::string result(buffer, length);
        BIO_free_all(bio);

        return result;
    }

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
