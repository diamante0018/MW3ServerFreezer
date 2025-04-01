#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// min and max is required by gdi, therefore NOMINMAX won't work
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <filesystem>
#include <functional>
#include <string>

namespace utils::nt {
class library final {
public:
  static library load(const std::string& name);
  static library load(const std::filesystem::path& path);
  static library get_by_address(void* address);

  library();
  explicit library(const std::string& name);
  explicit library(HMODULE handle);

  library(const library& a) : module_(a.module_) {}

  bool operator!=(const library& obj) const { return !(*this == obj); };
  bool operator==(const library& obj) const;

  operator bool() const;
  operator HMODULE() const;

  void unprotect() const;
  void* get_entry_point() const;
  size_t get_relative_entry_point() const;

  bool is_valid() const;
  std::string get_name() const;
  std::string get_path() const;
  std::string get_folder() const;
  std::uint8_t* get_ptr() const;
  void free();

  HMODULE get_handle() const;

  std::vector<PIMAGE_SECTION_HEADER> get_section_headers() const;

  PIMAGE_NT_HEADERS get_nt_headers() const;
  PIMAGE_DOS_HEADER get_dos_header() const;
  PIMAGE_OPTIONAL_HEADER get_optional_header() const;

private:
  HMODULE module_;
};

std::string load_resource(int id);

void relaunch_self();
void terminate(uint32_t code = 0);
} // namespace utils::nt
