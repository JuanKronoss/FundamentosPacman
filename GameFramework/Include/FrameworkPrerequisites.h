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
#include <unordered_map>
#include <set>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <exception>

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

using std::cout;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::remove_if;
using std::forward;
using std::find;
using std::tie;
using std::to_string;
using std::function;
using Exception = std::exception;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

template<class T>
using Vector = std::vector<T>;

template<class Key, class Value>
using UMap = std::unordered_map<Key, Value>;

template<class T>
using Set = std::set<T>;

template <typename T>
using Optional = std::optional<T>;

using String = std::string;

using IFStream = std::ifstream;
using OFStream = std::ofstream;
using IOFStream = std::fstream;

template <typename Base, typename Derived>
using IsBaseOf = std::is_base_of<Base, Derived>;

const String ASSETS_PATH = "Assets/";
const String TEXTURES_PATH = ASSETS_PATH + "Textures/";
const String FONTS_PATH = ASSETS_PATH + "Fonts/";
const String SCORE_FILE_PATH = ASSETS_PATH + "Scores/";
const String LEVELS_PATH = ASSETS_PATH + "Levels/";
