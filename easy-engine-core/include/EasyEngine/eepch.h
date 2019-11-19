#ifndef EEPCH_H
#define EEPCH_H
#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <map>
#include <set>
#include <thread>
#include <typeinfo>
#include <vector>
#include <queue>
#include <deque>
#include <typeinfo>
#include <typeindex>
#include <future>
#include <bitset>
#include <type_traits>
#include <chrono>
#include <filesystem>
#include <numeric>
#include <iterator>
#include <optional>
#include <utility>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/system/config.hpp>

#if defined(_MSC_VER)
#if defined(EE_CORE_DYNAMIC)
#define EASY_ENGINE_API  __declspec(dllexport)   // export DLL information
#elif defined(EE_CORE_DYNAMIC_LINK)
#define EASY_ENGINE_API  __declspec(dllimport)   // import DLL information
#else
#define EASY_ENGINE_API
#endif
#else
#define EASY_ENGINE_API
#endif

#if defined(EASY_ENGINE_BUILD)
#define EASY_ENGINE_EXTERN_TEMPLATE template
#else
#define EASY_ENGINE_EXTERN_TEMPLATE extern template
#endif

typedef unsigned char byte;
typedef unsigned short ushort_t;

#endif // !EEPCH_H