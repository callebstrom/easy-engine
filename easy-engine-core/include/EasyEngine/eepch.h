#ifndef COMMON_H
#define COMMON_H
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
#include <typeinfo>
#include <typeindex>
#include <future>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/system/config.hpp>

#ifdef DLLDIR_EX
#define EASY_ENGINE_API  __declspec(dllexport)   // export DLL information
#else
#define EASY_ENGINE_API  __declspec(dllimport)   // import DLL information
#endif 

typedef unsigned char byte;
typedef unsigned short ushort_t;

template<typename OrderedDataType>
using OrderedTypeMap = std::map<std::type_index, OrderedDataType>;

#endif // !COMMON_H

