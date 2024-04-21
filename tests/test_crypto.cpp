#include <cassert>
#include "sha1.hpp"
#include "base64.hpp"

void test_sha1()
{
    utils::sha1 sha1("dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    uint8_t digest[20];
    sha1.get_digest_bytes(digest);

    std::string encoded = utils::base64_encode(digest, 20);
    assert(encoded == "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=");
}

int main(int argc, char const *argv[])
{
    test_sha1();

    return 0;
}
