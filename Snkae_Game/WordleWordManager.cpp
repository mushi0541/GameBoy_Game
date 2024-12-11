#include "WordleWordManager.h"
#include <fstream>
#include <cstdlib> 
#include <ctime>  
#include <iostream> 

using namespace std;

WordleWordManager::WordleWordManager(const string& filePath) : filePath(filePath) {}

string WordleWordManager::getRandomWord()
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open the file!" << endl;
        return "";
    }

    srand(static_cast<unsigned int>(time(0)));

    // Count the total number of words in the file
    string line;
    int wordCount = 0;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            ++wordCount;
        }
    }

    if (wordCount == 0)
    {
        cerr << "Error: No words found in the file!" << endl;
        return "";
    }

 
    int randomIndex = rand() % wordCount;

    // Reset file pointer to the beginning
    file.clear();
    file.seekg(0);

   
    int currentLine = 0;
    string randomWord;

    while (getline(file, line))
    {
        if (!line.empty() && currentLine == randomIndex)
        {
            randomWord = line;
            break;
        }
        ++currentLine;
    }

    file.close();
    return randomWord;
}
