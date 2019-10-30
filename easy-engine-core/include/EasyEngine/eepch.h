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

#ifdef DLLDIR_EX
#define EASY_ENGINE_API  __declspec(dllexport)   // export DLL information
#define EASY_ENGINE_EXTERN_TEMPLATE template
#elif EE_CORE_STATIC
#define EASY_ENGINE_API
#define EASY_ENGINE_EXTERN_TEMPLATE extern template
#else
#define EASY_ENGINE_API  __declspec(dllimport)   // import DLL information
#define EASY_ENGINE_EXTERN_TEMPLATE extern template
#endif 

typedef unsigned char byte;
typedef unsigned short ushort_t;

#endif // !EEPCH_H