#include "crypto.hpp"
#include <openssl/evp.h>
#include <openssl/pem.h>
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

    std::string sign_rs256(std::string_view data, std::string_view private_key_pem)
    {
        BIO *bio = BIO_new_mem_buf(private_key_pem.data(), private_key_pem.size());
        EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);

        EVP_MD_CTX *ctx = EVP_MD_CTX_new();
        EVP_PKEY_CTX *pkey_ctx = nullptr;
        std::string signature;
        size_t sig_len = 0;

        if (EVP_DigestSignInit(ctx, &pkey_ctx, EVP_sha256(), nullptr, pkey) == 1 && EVP_DigestSignUpdate(ctx, data.data(), data.size()) == 1 && EVP_DigestSignFinal(ctx, nullptr, &sig_len) == 1)
        {
            signature.resize(sig_len);
            if (EVP_DigestSignFinal(ctx, (unsigned char *)signature.data(), &sig_len) == 1)
                signature.resize(sig_len);
            else
                signature.clear();
        }

        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return signature; // binary signature, base64url-encode for JWT
    }

    std::string extract_public_key(std::string_view private_key_pem)
    {
        BIO *bio = BIO_new_mem_buf(private_key_pem.data(), private_key_pem.size());
        EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);

        if (!pkey)
            throw std::runtime_error("Failed to read private key");

        BIO *pub_bio = BIO_new(BIO_s_mem());
        if (PEM_write_bio_PUBKEY(pub_bio, pkey) == 0)
        {
            EVP_PKEY_free(pkey);
            BIO_free(pub_bio);
            throw std::runtime_error("Failed to write public key");
        }

        char *pub_key_data;
        long pub_key_len = BIO_get_mem_data(pub_bio, &pub_key_data);
        std::string public_key(pub_key_data, pub_key_len);

        EVP_PKEY_free(pkey);
        BIO_free(pub_bio);
        return public_key;
    }
} // namespace utils
