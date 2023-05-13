#include "../headers/Functions.h"
#include "../headers/BoyerMorre.h"
#include "../headers/RapinKarp.h"
#include "../headers/bruteforce.hpp"
#include "../headers/KMP.h"
#include <random>
#include <string>
#include <iostream>
#include <iomanip>
std::vector<FileInput> ReadFiles(const std::vector<std::string> &fileNames)
{
    std::vector<FileInput> pattarns(fileNames.size());

    for (int i = 0; i < fileNames.size(); i++)
    {
        pattarns[i].documentName = fileNames[i];
        std::ifstream inputFile(pattarns[i].documentName);
        if (!inputFile.is_open())
        {
            std::cout << "Document: " << fileNames[i] << " was not opened\n";
            continue;
        }
        while (!inputFile.eof())
        {
            std::string sentence;
            std::getline(inputFile, sentence, '.');
            if (sentence.size() >= 1)
            {
                if (sentence[0] == ' ')
                    sentence.erase(sentence.begin());
                pattarns[i].patterns.push_back(sentence);
            }
        }
        inputFile.close();
    }
    return pattarns;
}

void CheckPlagarism(const std::string &testFile, const std::vector<FileInput> &pattarns, int threshold)
{
    std::string text;
    {
        std::ifstream inputFile(testFile);
        while (!inputFile.eof())
        {
            std::string temp;
            std::getline(inputFile, temp, '.');
            text += temp;
        }
        inputFile.close();
    }
    //Do the sae with the other algorithms

    std::vector<std::pair<std::string, int>> resultBoyerMoore;
    //BoyerMorre
    for (int i = 0; i < pattarns.size(); i++)
    {
        int occCount = 0;
        for (int j = 0; j < pattarns[i].patterns.size(); j++)
            occCount += BoyerMorreSearch(text, pattarns[i].patterns[j]);

        if (occCount >= threshold)
            resultBoyerMoore.push_back({pattarns[i].documentName, occCount});
    }
    std::vector<std::pair<std::string, int>> resultRapinKarp;
    //RapinKarp
    for (int i = 0; i < pattarns.size(); i++)
    {
        int occCount = 0;
        for (int j = 0; j < pattarns[i].patterns.size(); j++)
            occCount += RapinKarplookforpattern(pattarns[i].patterns[j], text, 101).occ;
        if (occCount >= threshold)
            resultRapinKarp.push_back({pattarns[i].documentName, occCount});
    }
    std::vector<std::pair<std::string, int>> resultbruteforce;
    //bruteforce
    int countingcomps;
    for (int i = 0; i < pattarns.size(); i++)
    {
        int occCountBruteforce = 0;
        for (int j = 0; j < pattarns[i].patterns.size(); j++)
            occCountBruteforce += bruteforce(text, pattarns[i].patterns[j], countingcomps);

        if (occCountBruteforce >= threshold)
            resultbruteforce.push_back({pattarns[i].documentName, occCountBruteforce});
    }

    std::vector<std::pair<std::string, int>> resultKMP;
    //KMP
    int kmpComp;
    for (int i = 0; i < pattarns.size(); i++)
    {
        int occKMP = 0;
        for (int j = 0; j < pattarns[i].patterns.size(); j++)
            occKMP += KMPSearch(pattarns[i].patterns[j], text, kmpComp);

        if (occKMP >= threshold)
            resultKMP.push_back({pattarns[i].documentName, occKMP});
    }

    std::cout << "BoyerMoore results: \n";
    for (int i = 0; i < resultBoyerMoore.size(); i++)
    {
        std::cout << "Document Name: " << resultBoyerMoore[i].first << ", Occurances: " << resultBoyerMoore[i].second << std::endl;
    }
    std::cout << "Rapin Karp results: \n";
    for (int i = 0; i < resultRapinKarp.size(); i++)
    {
        std::cout << "Document Name: " << resultRapinKarp[i].first << ", Occurances: " << resultRapinKarp[i].second << std::endl;
    }
    std::cout << "Brute Force results: \n";
    for (int i = 0; i < resultbruteforce.size(); i++)
    {
        std::cout << "Document Name: " << resultbruteforce[i].first << ", Occurances: " << resultbruteforce[i].second << std::endl;
    }
    std::cout << "KMP results: \n";
    for (int i = 0; i < resultKMP.size(); i++)
    {
        std::cout << "Document Name: " << resultKMP[i].first << ", Occurances: " << resultKMP[i].second << std::endl;
    }
}

std::ostream &operator<<(std::ostream &stream, FileInput &in)
{
    std::cout << "Document Name: ";
    stream << in.documentName;
    std::cout << "\nPattarns: \n";
    for (int i = 0; i < in.patterns.size(); i++)
    {
        stream << in.patterns[i] << std::endl;
    }
    stream << std::endl;
    return stream;
}

std::string CreateRandomString(int size)
{
    std::string str;
    str.resize(size);
    for (int i = 0; i < size; i++)
    {
        str[i] = rand() % 26 + 65;
    }
    return str;
}

void TestComparisons(int n, int m)
{
    srand(time(0));
    std::string text = CreateRandomString(n);
    std::string pattern = CreateRandomString(m);
    int count = 0;
    int occ = BoyerMorreSearchCountable(text, pattern, count);
    counts p = RapinKarplookforpattern(pattern, text, 101);
    int count2 = 0;
    int occ2 = bruteforce(text, pattern, count2);
    int count3 = 0;
    int occ3 = KMPSearch(pattern, text, count3);

    std::cout << count << ',' << p.comp << ',' << count2 << ',' << count3 << std::endl;
}

void TestPlagarism()
{
    std::string textFileName;
    std::cout << "Enter the text file name: \n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, textFileName);

    int n;

    std::cout << "Enter the number of the pattarn files used as a database: ";
    std::cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<std::string> pattarns;

    for (int i = 0; i < n; i++)
    {
        std::cout << "Enter the file name number: " << i + 1 << std::endl;
        std::string temp;
        std::getline(std::cin, temp);
        pattarns.push_back(temp);
    }
    auto fileInput = ReadFiles(pattarns);
    int threshold = 1;
    std::cout << "Enter the threshold (The number upon which we decide that there is a plagarism, by default it is 1)\n";
    std::cin >> threshold;
    CheckPlagarism(textFileName, fileInput, (threshold == 0) ? 0 : threshold);
}