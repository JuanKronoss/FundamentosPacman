#pragma once

/**
 * Defines the export/import macros for the dynamic library.
 */

#if defined _WIN32
#   if defined _MSC_VER
#     if defined FRAMEWORK_STATIC_LIB
#       define FRAMEWORK_EXPORT
#     else
#       if defined FRAMEWORK_EXPORTS
#         define FRAMEWORK_EXPORT __declspec(dllexport)
#       else
#         define FRAMEWORK_EXPORT __declspec(dllimport)
#       endif
#     endif
#   else  //Any other Compiler
#     if defined FRAMEWORK_STATIC_LIB
#       define FRAMEWORK_EXPORT
#     else
#       if defined FRAMEWORK_EXPORTS
#         define FRAMEWORK_EXPORT __attribute__ ((dllexport))
#       else
#         define FRAMEWORK_EXPORT __attribute__ ((dllimport))
#       endif
#     endif
#   endif
#   define FRAMEWORK_HIDDEN
#   define DYNAMIC_LIB_EXPORT __declspec(dllexport)
#elif defined __linux__
 //Unix-like systems (Linux, macOS, PS4, PS5, Android, IOS)
#   if defined FRAMEWORK_STATIC_LIB
#     define FRAMEWORK_EXPORT
#   else
#     define FRAMEWORK_EXPORT __attribute__((visibility("default")))
#   endif
#   define FRAMEWORK_HIDDEN __attribute__((visibility("hidden")))
#   define DYNAMIC_LIB_EXPORT __attribute__((visibility("default")))
#else
#   error "Unsupported platform detected for FRAMEWORK_EXPORT."
#endif

/**
 * Includes
 */

#include <memory>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility> // pair
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <exception>
#include <filesystem>

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
using std::cerr;
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

template<class Key, class Value>
using Pair = std::pair<Key, Value>;

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
const String MODS_PATH = ASSETS_PATH + "Mods/";
