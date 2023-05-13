#include "KMP.h"

void computeLPSArray(std::string pat, int M, int *lps, int &count)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M)
    {
        if (++count && pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];

            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(std::string pat, std::string txt, int &count)
{
    int M = pat.length();
    int N = txt.length();
    int lps[M];

    computeLPSArray(pat, M, lps, count);

    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < N)
    {
        if (++count && pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            counter++;
            j = lps[j - 1];
        }

        else if (i < N && ++count && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return counter;
}

void TestKMP()
{
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABA";
    int count = 0;
    int rep = KMPSearch(pat, txt, count);
    std::cout << count << std::endl;
    std::cout << rep << std::endl;
}