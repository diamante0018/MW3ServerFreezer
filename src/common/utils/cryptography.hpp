#pragma once

#include <string>
#include <tomcrypt.h>

namespace utils::cryptography {
namespace ecc {
class key final {
public:
  key();
  ~key();

  key(key&& obj) noexcept;
  key(const key& obj);
  key& operator=(key&& obj) noexcept;
  key& operator=(const key& obj);
  bool operator==(key& key) const;

  [[nodiscard]] bool is_valid() const;

  ecc_key& get();
  [[nodiscard]] const ecc_key& get() const;

  [[nodiscard]] std::string get_public_key() const;

  void set(const std::string& pub_key_buffer);

  void deserialize(const std::string& key);

  [[nodiscard]] std::string serialize(int type = PK_PRIVATE) const;

  void free();

  [[nodiscard]] std::uint64_t get_hash() const;

private:
  ecc_key key_storage_{};
};

key generate_key(int bits);
key generate_key(int bits, const std::string& entropy);
std::string sign_message(const key& key, const std::string& message);
bool verify_message(const key& key, const std::string& message,
                    const std::string& signature);

bool encrypt(const key& key, std::string& data);
bool decrypt(const key& key, std::string& data);
} // namespace ecc

namespace rsa {
std::string encrypt(const std::string& data, const std::string& hash,
                    const std::string& key);
}

namespace des3 {
std::string encrypt(const std::string& data, const std::string& iv,
                    const std::string& key);
std::string decrypt(const std::string& data, const std::string& iv,
                    const std::string& key);
} // namespace des3

namespace tiger {
std::string compute(const std::string& data, bool hex = false);
std::string compute(const std::uint8_t* data, std::size_t length,
                    bool hex = false);
} // namespace tiger

namespace aes {
std::string encrypt(const std::string& data, const std::string& iv,
                    const std::string& key);
std::string decrypt(const std::string& data, const std::string& iv,
                    const std::string& key);
} // namespace aes

namespace hmac_sha1 {
std::string compute(const std::string& data, const std::string& key);
}

namespace sha1 {
std::string compute(const std::string& data, bool hex = false);
std::string compute(const std::uint8_t* data, std::size_t length,
                    bool hex = false);
} // namespace sha1

namespace sha256 {
std::string compute(const std::string& data, bool hex = false);
std::string compute(const std::uint8_t* data, std::size_t length,
                    bool hex = false);
} // namespace sha256

namespace sha512 {
std::string compute(const std::string& data, bool hex = false);
std::string compute(const std::uint8_t* data, std::size_t length,
                    bool hex = false);
} // namespace sha512

namespace base64 {
std::string encode(const std::uint8_t* data, std::size_t len);
std::string encode(const std::string& data);
std::string decode(const std::string& data);
} // namespace base64

namespace jenkins_one_at_a_time {
unsigned int compute(const std::string& data);
unsigned int compute(const char* key, std::size_t len);
}; // namespace jenkins_one_at_a_time

namespace random {
std::uint32_t get_integer();
std::string get_challenge();
void get_data(void* data, std::size_t size);
} // namespace random
} // namespace utils::cryptography
