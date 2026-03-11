#pragma once

/**
 * Defines the export/import macros for the dynamic library.
 */

#ifdef __linux__
#define DYNAMIC_LIBRARY_API __attribute__((visibility("default")))
#else // Windows
#ifdef DYNAMIC_LIBRARY_EXPORTS
#define DYNAMIC_LIBRARY_API __declspec(dllexport)
#else
#define DYNAMIC_LIBRARY_API __declspec(dllimport)
#endif // DYNAMIC_LIBRARY_EXPORTS
#endif // __linux__

/**
 * Includes
 */

#include <memory>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>

/**
 * Using declarations
 */

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using std::make_shared;
using std::dynamic_pointer_cast;
using std::forward;
using std::find;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

template<class T>
using Vector = std::vector<T>;

template <typename T>
using Optional = std::optional<T>;

using String = std::string;

using IOFStream = std::fstream;

template <typename Base, typename Derived>
using IsBaseOf = std::is_base_of<Base, Derived>;
