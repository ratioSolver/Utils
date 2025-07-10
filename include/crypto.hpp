#pragma once

#include <string>

namespace utils
{
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
  [[nodiscard]] std::string encode_password(std::string_view password, std::string_view salt);
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
  [[nodiscard]] std::pair<std::string, std::string> encode_password(std::string_view password);

  /**
   * @brief Signs data using RS256 algorithm with a private key in PEM format.
   *
   * This function takes a string of data and a private key in PEM format,
   * and returns the RS256 signature of the data.
   *
   * @param data The data to be signed.
   * @param private_key_pem The private key in PEM format.
   * @return A string containing the RS256 signature of the data.
   */
  [[nodiscard]] std::string sign_rs256(std::string_view data, std::string_view private_key_pem);

  /**
   * @brief Extracts the public key from a private key in PEM format.
   *
   * This function takes a private key in PEM format and extracts the corresponding
   * public key, returning it as a string.
   *
   * @param private_key_pem The private key in PEM format.
   * @return A string containing the public key in PEM format.
   */
  [[nodiscard]] std::string extract_public_key(std::string_view private_key_pem);
} // namespace utils
