#include <iostream>
#include <string>
#include <cstring>
#include "../headers/RapinKarp.h"
using namespace std;
#define n 256

counts RapinKarplookforpattern(const std::string &pat, const std::string &text, int prime)
{
	counts pair;
	int comparisons_count = 0;
	int occurrances_count = 0;
	int l1 = pat.length(), l2 = text.length(), i, j, patternhash = 0, texthash = 0, a = 1;
	for (i = 0; i < l1 - 1; i++)
		a = (a * n) % prime;
	if (l1 > l2)
		return {0, 0};
	for (i = 0; i < l1; i++)
	{
		patternhash = (n * patternhash + pat[i]) % prime;
		texthash = (n * texthash + text[i]) % prime;
	}
	for (i = 0; i <= l2 - l1; i++)
	{
		if (++comparisons_count && patternhash == texthash)
		{
			for (j = 0; j < l1; j++)
			{
				if (++comparisons_count && text[i + j] != pat[j])
					break;
			}

			if (j == l1)
				++occurrances_count;
		}
		if (i < (l2 - l1))
		{
			texthash = (n * (texthash - text[i] * a) + text[i + l1]) % prime;
			if (++comparisons_count && texthash < 0)
				texthash += prime;
		}
	}
	pair.comp = comparisons_count;
	pair.occ = occurrances_count;
	return pair;
}
void algorithmtest()
{
	char txt[] = "Messi Neymar and Messi Messi Messi Messi";
	char pat[] = "Messi";
	int q = 101;
	cout << RapinKarplookforpattern(pat, txt, q).occ;
}
