#pragma once

#include <string>

namespace utils
{
  /**
   * @brief Computes the SHA-1 hash of the given input string.
   *
   * @param input The input string to be hashed, provided as a std::string_view.
   * @return A std::string containing the hexadecimal representation of the SHA-1 hash.
   */
  std::string sha1(std::string_view input);

  /**
   * @brief Computes the SHA-256 hash of the given input string.
   *
   * This function takes a string input and returns its SHA-256 hash
   * as a hexadecimal string. SHA-256 is a cryptographic hash function
   * commonly used for data integrity and security purposes.
   *
   * @param input The input string to be hashed.
   * @return A string representing the SHA-256 hash of the input in hexadecimal format.
   */
  std::string sha256(std::string_view input);

  /**
   * @brief Encodes a given input string into its Base64 representation.
   *
   * @param input The input string to be encoded, provided as a std::string_view.
   * @return A std::string containing the Base64-encoded representation of the input.
   */
  std::string base64_encode(std::string_view input);
  /**
   * @brief Decodes a Base64-encoded string.
   *
   * This function takes a Base64-encoded string as input and returns the decoded
   * string. It is useful for decoding data that has been encoded in Base64 format,
   * such as data transmitted over text-based protocols or stored in text files.
   *
   * @param input The Base64-encoded string to decode, provided as a std::string_view.
   * @return A std::string containing the decoded data.
   */
  std::string base64_decode(std::string_view input);

  /**
   * @brief Encodes a password using the provided salt.
   *
   * This function takes a password and a salt as input and returns an encoded
   * version of the password. The encoding process ensures that the password
   * is securely transformed, typically for storage or comparison purposes.
   *
   * @param password The plain-text password to be encoded.
   * @param salt The salt to be used in the encoding process. Salts are used
   *             to add randomness to the encoding, making it more secure.
   * @return A string containing the encoded password.
   */
  std::string encode_password(std::string_view password, std::string_view salt);
  /**
   * @brief Encodes a given password into a pair of strings.
   *
   * This function takes a password as input and encodes it into two separate
   * strings - a salt and the encoded password. The salt is a random value used
   * to enhance the security of the encoded password.
   *
   * @param password The plain-text password to be encoded.
   * @return A pair of strings, where the first string is the salt and the second
   *         string is the encoded password.
   */
  std::pair<std::string, std::string> encode_password(std::string_view password);
} // namespace utils
