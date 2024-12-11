#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <string>

using namespace std;

class WordManager 
{
public:
   
    WordManager(const string& filePath);

    
    string getRandomWord();
    string category;

private:
    string filePath; 

};

#endif 
