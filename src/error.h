#pragma once
#include <string>

void panic(const std::string s){
    perror(s.c_str());
    exit(1);
}