#ifndef OBJ_CONVERTER_H
#define OBJ_CONVERTER_H
#pragma once

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <ResourceManager3D.h>

void ConvertObjFile(std::string file_path);

#endif //!OBJ_CONVERTER_H