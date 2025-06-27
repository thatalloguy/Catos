//
// Created by allos on 4/30/2024.
//
#pragma once


#include <string>



#if _WIN64
#   define CATOS_WIN
#   define CATOS_API __declspec(dllexport)
#   define CATOS_PATH_SEPARATOR '\\'
#elif __linux__
#   define CATOS_LINUX
#   define CATOS_API __attribute__ ((visibility ("default")))
#   define CATOS_PATH_SEPARATOR '/'
#   define CATOS_UNIX
#endif

typedef std::string_view str;
typedef const char*  cstr;
typedef unsigned int uint;


void* get_type_info(size_t hash);
bool is_type_registered(size_t hash);