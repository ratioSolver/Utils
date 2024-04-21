#pragma once

#include <string>
#include <cstring>

namespace utils
{
  /**
   * @class sha1
   * @brief Represents a SHA-1 hash algorithm implementation.
   *
   * The `sha1` class provides functionality to calculate the SHA-1 hash of a given input data.
   * It supports obtaining the hash as both a 32-bit integer array and an 8-bit byte array.
   */
  class sha1
  {
  public:
    typedef unsigned int digest_32[5];
    typedef unsigned char digest_8[20];
    inline static unsigned int left_rotate(unsigned int value, size_t count) { return (value << count) ^ (value >> (32 - count)); }

    sha1(const std::string &data) { process_bytes(data.data(), data.size()); }

    /**
     * @brief Retrieves the digest value for a given SHA1 hash.
     *
     * @param dig The SHA1 digest value to retrieve.
     * @return A pointer to the digest value.
     */
    const unsigned int *get_digest(digest_32 dig)
    {
      size_t bit_count = byte_count * 8;
      process_byte(0x80);
      if (block_byte_index > 56)
      {
        while (block_byte_index != 0)
          process_byte(0);
        while (block_byte_index < 56)
          process_byte(0);
      }
      else
        while (block_byte_index < 56)
          process_byte(0);
      process_byte(0);
      process_byte(0);
      process_byte(0);
      process_byte(0);
      process_byte(static_cast<unsigned char>((bit_count >> 24) & 0xFF));
      process_byte(static_cast<unsigned char>((bit_count >> 16) & 0xFF));
      process_byte(static_cast<unsigned char>((bit_count >> 8) & 0xFF));
      process_byte(static_cast<unsigned char>((bit_count) & 0xFF));

      memcpy(dig, digest, 5 * sizeof(unsigned int));
      return dig;
    }

    /**
     * @brief Retrieves the bytes of the digest.
     *
     * This function returns a pointer to the bytes of the given digest.
     *
     * @param digest The digest for which to retrieve the bytes.
     * @return A pointer to the bytes of the digest.
     */
    const unsigned char *get_digest_bytes(digest_8 digest)
    {
      digest_32 d32;
      get_digest(d32);
      size_t di = 0;
      digest[di++] = ((d32[0] >> 24) & 0xFF);
      digest[di++] = ((d32[0] >> 16) & 0xFF);
      digest[di++] = ((d32[0] >> 8) & 0xFF);
      digest[di++] = ((d32[0]) & 0xFF);

      digest[di++] = ((d32[1] >> 24) & 0xFF);
      digest[di++] = ((d32[1] >> 16) & 0xFF);
      digest[di++] = ((d32[1] >> 8) & 0xFF);
      digest[di++] = ((d32[1]) & 0xFF);

      digest[di++] = ((d32[2] >> 24) & 0xFF);
      digest[di++] = ((d32[2] >> 16) & 0xFF);
      digest[di++] = ((d32[2] >> 8) & 0xFF);
      digest[di++] = ((d32[2]) & 0xFF);

      digest[di++] = ((d32[3] >> 24) & 0xFF);
      digest[di++] = ((d32[3] >> 16) & 0xFF);
      digest[di++] = ((d32[3] >> 8) & 0xFF);
      digest[di++] = ((d32[3]) & 0xFF);

      digest[di++] = ((d32[4] >> 24) & 0xFF);
      digest[di++] = ((d32[4] >> 16) & 0xFF);
      digest[di++] = ((d32[4] >> 8) & 0xFF);
      digest[di++] = ((d32[4]) & 0xFF);
      return digest;
    }

  private:
    void process_bytes(const void *const data, size_t len)
    {
      const unsigned char *block = static_cast<const unsigned char *>(data);
      process_block(block, block + len);
    }

    void process_byte(unsigned char octet)
    {
      block[block_byte_index++] = octet;
      ++byte_count;
      if (block_byte_index == 64)
      {
        block_byte_index = 0;
        process_block();
      }
    }

    void process_block(const void *const start, const void *const end)
    {
      const unsigned char *begin = static_cast<const unsigned char *>(start);
      const unsigned char *finish = static_cast<const unsigned char *>(end);
      while (begin != finish)
      {
        process_byte(*begin);
        begin++;
      }
    }

    void process_block()
    {
      unsigned int w[80];
      for (size_t i = 0; i < 16; i++)
      {
        w[i] = (block[i * 4 + 0] << 24);
        w[i] |= (block[i * 4 + 1] << 16);
        w[i] |= (block[i * 4 + 2] << 8);
        w[i] |= (block[i * 4 + 3]);
      }
      for (size_t i = 16; i < 80; i++)
        w[i] = left_rotate((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);

      unsigned int a = digest[0];
      unsigned int b = digest[1];
      unsigned int c = digest[2];
      unsigned int d = digest[3];
      unsigned int e = digest[4];

      for (std::size_t i = 0; i < 80; ++i)
      {
        unsigned int f = 0;
        unsigned int k = 0;

        if (i < 20)
        {
          f = (b & c) | (~b & d);
          k = 0x5A827999;
        }
        else if (i < 40)
        {
          f = b ^ c ^ d;
          k = 0x6ED9EBA1;
        }
        else if (i < 60)
        {
          f = (b & c) | (b & d) | (c & d);
          k = 0x8F1BBCDC;
        }
        else
        {
          f = b ^ c ^ d;
          k = 0xCA62C1D6;
        }
        unsigned int temp = left_rotate(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = left_rotate(b, 30);
        b = a;
        a = temp;
      }

      digest[0] += a;
      digest[1] += b;
      digest[2] += c;
      digest[3] += d;
      digest[4] += e;
    }

  private:
    digest_32 digest{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    unsigned char block[64];
    size_t block_byte_index{0};
    size_t byte_count{0};
  };
} // namespace utils
