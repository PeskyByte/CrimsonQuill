#pragma once
#include <string>
#include <errno.h>

void panic(const std::string s){
    perror(s.c_str());
    exit(1);
}