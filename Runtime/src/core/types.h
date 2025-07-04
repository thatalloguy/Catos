//
// Created by allos on 4/30/2024.
//
#pragma once


#include <string>
#include <typeinfo>


#if _WIN64
#   define CATOS_WIN
#   define CATOS_API __declspec(dllexport)
#   define CATOS_PATH_SEPARATOR '\\'
#elif __linux__
#   define CATOS_LINUX
#   define CATOS_API __attribute__ ((visibility ("default")))
#   define CATOS_PATH_SEPARATOR '/'
#   define CATOS_UNIX
#else
# define CATOS_MAC
#   define CATOS_API __attribute__ ((visibility ("default")))
#endif

inline size_t float_hash = typeid(float).hash_code();
inline size_t int_hash = typeid(int).hash_code();
inline size_t uint_hash = typeid(unsigned int).hash_code();
inline size_t bool_hash = typeid(bool).hash_code();




typedef std::string_view str;
typedef const char*  cstr;
typedef unsigned int uint;


void* get_type_info(size_t hash);
bool is_type_registered(size_t hash);