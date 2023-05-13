#include "../headers/BoyerMorre.h"
void BadCharHueristic(const std::string &str, int badCharPos[256])
{
    for (int i = 0; i < 256; i++)
        badCharPos[i] = -1;

    for (int i = 0; i < str.size(); i++)
        badCharPos[int(str[i])] = i; // setting the position of the characters to be at index i
}

int BoyerMorreSearch(const std::string &text, const std::string &pattarn)
{
    int badCharacterPos[256];
    //Prepare the array to hold the positions of the last occ. of the pattern characters
    BadCharHueristic(pattarn, badCharacterPos);

    int numberOfMatches = 0;
    int shiftAmount = 0;
    //Keep on searching until we run out of text
    while (shiftAmount <= text.size() - pattarn.size())
    {
        //Index to search in the pattern
        int index = pattarn.size() - 1;

        //Keep on looping until we find a mismatch or the index is just out of the bounds (-1)
        while (index > -1 && pattarn[index] == text[shiftAmount + index])
            index--;

        //If the index == -1 then we found a match and we want to see any other matches
        if (index == -1)
        {
            numberOfMatches += 1;
            //Condition to know whether we are matching at the end of the text or not
            if (shiftAmount + pattarn.size() < text.size())
                shiftAmount += pattarn.size() - badCharacterPos[int(text[shiftAmount + pattarn.size()])]; //Shift the text by the whole pattern
            else
                shiftAmount += 1; // shift it by 1 just to get out of the loops
        }
        else
            shiftAmount += std::max(1, index - badCharacterPos[int(text[shiftAmount + index])]);
    }
    return numberOfMatches;
}

void BoyerMorreTest()
{
    std::string text = "ABCDABCABCAS";
    std::string pattern = "ABC";
    int count = 0;
    std::cout << "Search found: " << BoyerMorreSearchCountable(text, pattern, count) << " Occ." << std::endl;
    std::cout << "Comparisons: " << count << std::endl;
}

int BoyerMorreSearchCountable(const std::string &text, const std::string &pattarn, int &count)
{
    //Resetting the count to 0
    count = 0;
    int badCharacterPos[256];
    //Prepare the array to hold the positions of the last occ. of the pattern characters
    BadCharHueristic(pattarn, badCharacterPos);

    int numberOfMatches = 0;
    int shiftAmount = 0;
    //Keep on searching until we run out of text
    while (shiftAmount <= text.size() - pattarn.size())
    {
        //Index to search in the pattern
        int index = pattarn.size() - 1;

        //Keep on looping until we find a mismatch or the index is just out of the bounds (-1)
        while (index > -1 && ++count && pattarn[index] == text[shiftAmount + index])
            index--;

        //If the index == -1 then we found a match and we want to see any other matches
        if (index == -1)
        {
            numberOfMatches += 1;
            //Condition to know whether we are matching at the end of the text or not
            if (shiftAmount + pattarn.size() < text.size())
                shiftAmount += pattarn.size() - badCharacterPos[int(text[shiftAmount + pattarn.size()])]; //Shift the text by the whole pattern
            else
                shiftAmount += 1; // shift it by 1 just to get out of the loops
        }
        else
            shiftAmount += std::max(1, index - badCharacterPos[int(text[shiftAmount + index])]);
    }
    return numberOfMatches;
}