#include "VaragesFunLibrary.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Final
{
public:

    typedef vector<string> StringArray;

    static void SpawnFile(int inNeed, string& outFilePath, bool isAllQualified)
    {
        outFilePath = "Users.dat";
        StringArray IDs = GetIDs(inNeed);
        ofstream ofs;
        ofs.open(outFilePath);
        for (string& str : IDs)
        {
            ofs << str << (str == IDs[inNeed - 1] ? "" : "\n");
        }
        ofs.close();
    }

private:

    static StringArray GetIDs(long inNeed)
    {
        StringArray result;
        for (long index = 0; index < inNeed; index++)
        {
            string randomID;
            do
            {
                randomID = RandomChar() + to_string(RandomNumber());
            } while (Repeated(result, randomID));
            result.push_back(randomID);
        }
        return result;
    }

    static long RandomNumber()
    {
        return (rand() % 90000 + 10000);
    }

    static char RandomChar()
    {
        return (rand() % 4 + 65);
    }

    static bool Repeated(StringArray inVector, string inString)
    {
        return (find(inVector.begin(), inVector.end(), inString) != inVector.end());
    }
};