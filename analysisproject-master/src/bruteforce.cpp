#include <iostream>
#include "../headers/bruteforce.hpp"
#include <string>
#include <cstring>
using namespace std;

int bruteforce(string pattern, string text, int &countcomp)
{
    int countocc = 0, k = 0;
    int difference = pattern.length() - text.length();
    for (int i = 0; i <= difference; i++)
    {
        int j = 0;
        while ((j < text.length()) && ++countcomp && (pattern[i + j] == text[j]))
        {
            j++;
        }
        if (++countcomp && j == text.length())
        {
            countocc++;
        }
    }
    return countocc;
}
void bruteforcetest()
{
    string pattern = "Hello there friends. How are you friends?";
    string text = "friends";
    int comp = 0;
    int position = bruteforce(pattern, text, comp);

    if (position == 0)
    {
        cout << "The inserted text  is not found" << endl;
    }
    else
    {
        cout << "The number of occurences is " << position << endl;
    }
}
