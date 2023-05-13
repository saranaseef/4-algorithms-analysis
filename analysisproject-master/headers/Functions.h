#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct FileInput
{
    std::string documentName;
    std::vector<std::string> patterns;
};

std::vector<FileInput> ReadFiles(const std::vector<std::string> &fileNames);

void CheckPlagarism(const std::string &testFile, const std::vector<FileInput> &pattarns, int threshold);

std::ostream &operator<<(std::ostream &stream, FileInput &in);

std::string CreateRandomString(int size);

void TestComparisons(int n, int m);

void TestPlagarism();