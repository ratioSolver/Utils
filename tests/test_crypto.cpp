#include <cassert>
#include <cstdint>
#include "crypto.hpp"

void test_sha1()
{
    std::string encoded = utils::base64_encode(utils::sha1("dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11"));
    assert(encoded == "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=");
}

int main()
{
    test_sha1();

    return 0;
}
