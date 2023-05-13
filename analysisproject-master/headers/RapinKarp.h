#pragma once
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
struct counts
{
    int occ, comp;
};

counts RapinKarplookforpattern(const std::string& pat, const std::string& text, int prime);
void algorithmtest();
