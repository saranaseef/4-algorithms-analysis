#include <string.h>
#include <iostream>

using namespace std;

void computeLPSArray(std::string pat, int M, int *lps, int &count);
int KMPSearch(std::string pat, std::string txt, int &count);
void TestKMP();