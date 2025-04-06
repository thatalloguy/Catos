//
// Created by allos on 4/30/2024.
//
#pragma once


#include <string>




typedef std::string_view str;
typedef const char*  cstr;
typedef unsigned int uint;


void* get_type_info(size_t hash);
bool is_type_registered(size_t hash);