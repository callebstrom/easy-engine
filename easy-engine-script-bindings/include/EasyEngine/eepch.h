#pragma once

#include <vector>

#ifdef SCRIPT_BINDINGS_DLLDIR_EX
#define EASY_ENGINE_API  __declspec(dllexport)   // export DLL information
#else
#define EASY_ENGINE_API  __declspec(dllimport)   // import DLL information
#endif 