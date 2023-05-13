#include <iostream>
#include <string>

void BadCharHueristic(const std::string &str, int badCharPos[256]);
int BoyerMorreSearch(const std::string &text, const std::string &pattarn);
int BoyerMorreSearchCountable(const std::string &text, const std::string &pattarn, int &count);
void BoyerMorreTest();
