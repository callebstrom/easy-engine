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
#include <typeinfo>
#include <typeindex>
#include <future>
#include <bitset>
#include <type_traits>
#include <chrono>

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

#endif // !EEPCH_H