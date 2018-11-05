#ifndef COMMON_H
#define COMMON_H
#pragma once

#include <vector>
#include <iostream>
#include <set>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/system/config.hpp>

#include <EasyEngine/Logger.h>

#ifdef DLLDIR_EX
#define EASY_ENGINE_API  __declspec(dllexport)   // export DLL information
#else
#define EASY_ENGINE_API  __declspec(dllimport)   // import DLL information
#endif 

typedef unsigned char byte;
typedef unsigned short ushort_t;

#endif // !COMMON_H

