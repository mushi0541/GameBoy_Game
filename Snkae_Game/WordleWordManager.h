#ifndef WORDLEWORDMANAGER_H
#define WORDLEWORDMANAGER_H

#include <string>

using namespace std;

class WordleWordManager 
{
public:
   
    WordleWordManager(const string& filePath);
    
    string getRandomWord();

private:
    string filePath; 

};

#endif 
