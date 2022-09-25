#pragma once

namespace game {
template <typename T> class symbol {
public:
  symbol(const size_t mp) : mp_(reinterpret_cast<T*>(mp)) {}

  [[nodiscard]] T* get() const { return mp_; }

  operator T*() const { return this->get(); }

  T* operator->() const { return this->get(); }

private:
  T* mp_;
};

// clang-format off
extern ScreenPlacement* ScrPlace_GetUnsafeFullPlacement();
extern void Dvar_SetVariant(dvar_t* dvar, DvarValue value, DvarSetSource source);
// clang-format on
} // namespace game

#include "symbols.hpp"
