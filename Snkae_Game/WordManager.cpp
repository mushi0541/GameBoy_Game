#include "WordManager.h"
#include <fstream>
#include <cstdlib> 
#include <ctime>  
#include <iostream> 

using namespace std;

WordManager::WordManager(const string& filePath) : filePath(filePath) {}

string WordManager::getRandomWord() 
{
    ifstream file(filePath);
    if (!file.is_open()) 
    {
        cerr << "Error: Could not open the file!" << endl;
        return "";
    }

    srand(static_cast<unsigned int>(time(0))); 

    // Count the number of categories in the file
    string line;
    int categoryCount = 0;
    while (getline(file, line)) {
        if (!line.empty() && line[0] == '[' && line.back() == ']') {
            ++categoryCount;
        }
    }

    if (categoryCount == 0) 
    {
        cerr << "Error: No categories found in the file!" << endl;
        return "";
    }

    // Pick a random category
    file.clear();
    file.seekg(0);
    int randomCategory = rand() % categoryCount;
    int currentCategory = -1;

    while (getline(file, line)) {
        if (!line.empty() && line[0] == '[' && line.back() == ']') 
        {
            ++currentCategory;
            if (currentCategory == randomCategory) 
            {
                category = line.substr(1, line.size() - 2); // Extract category name
                break;
            }
        }
    }

    // Read words for the selected category
    string words[10];
    int wordCount = 0;

    while (getline(file, line) && wordCount < 10) 
    {
        if (line.empty() || (line[0] == '[' && line.back() == ']')) 
        {
            break; // Stop if we reach the next category
        }
        words[wordCount++] = line;
    }

    if (wordCount == 0) 
    {
        cerr << "Error: No words found for the category!" << endl;
        return "";
    }

    string randomWord = words[rand() % wordCount];
    file.close();
    return randomWord;
}
