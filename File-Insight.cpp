/*
Thomas Zemen
Program that takes any number of files as command line arguments from the user.
The program will then print out the following information for each, line count,
word count, character count, and the number of words beginning with each character. 
*/

#include <fstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>
 
using namespace std;

class word
{
  private:
   
   string line;
   int lineCount = 0;
   int charCount = 0;
   int wordCount = 0;
   

   //Array to store each letter
   char lowerCaseLetters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   char upperCaseLetters[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
   //Array to store letter count
   int letterCount[26];

   int temp_int;
   char temp_char;
   string temp_string;

 
  public:     

    //CONSTRUCTOR WHICH ACCEPTS THE FILE NAME
    word(char* file_name){

        //file variable
        fstream inFile(file_name);

        inFile.open(file_name);

        while(true){
            int temp_int;
            char temp_char;
        
            temp_int = inFile.get();
    
            if(temp_int == -1){
                cout << "EOF reached" << endl;
                break;
            }

            charCount++;

            temp_char = (char)temp_int;
        
            if(temp_char == '\n')
            {
                lineCount++; 
                wordCount++;
                LetterCount(temp_string);
                temp_string.clear();
                continue;
            }
            if(temp_char == ' ')
            {
                wordCount++;
                LetterCount(temp_string);
                temp_string.clear();
                continue;
            }

            //OTHERWISE ADD CHAR TO TEMPORARY STRING 
            temp_string.push_back(temp_char);
        
        }
        
        inFile.close();
    
    }

    void SetLines(int x)
    {
        lineCount = x;
    }
    void SetChars(int y)
    {
        charCount = y;
    }
    void SetWords(int z)
    {
        wordCount = z;
    }
    
    int GetLines(){
        return lineCount;
    }
    int GetWords(){
        return charCount;  
    }
    int GetChars(){
        return wordCount;
    }
    

    //COMPARE EACH FIRST CHARACTER IN VECTOR TO EACH ARRAY CHAR
    void LetterCount(string x){
        char firstChar = x[0];
        string vectorWord;
        for(int i = 0; i <= 26; i++){
          if(lowerCaseLetters[i] == firstChar){
             letterCount[i] = letterCount[i] + 1;
           } else if(upperCaseLetters[i] == firstChar){
                letterCount[i] = letterCount[i] + 1;
            }
        }  
    }

    void PrintLetterCount(){
        cout<<"The Letter count is listed as follows"<<endl;
        for(int i = 0; i<26; i++)
        {
            if(letterCount[i] == 0){
                continue;
            }
            cout<<"The letter "<< upperCaseLetters[i] << " is present "<< letterCount[i] << ", many times in this file" << endl;
        }

    } 
 
};


int main(int argc, char* argv[]) { 

    int buffer_size = 10;
    int buffer_count = 0;
    
    
    //Store every files line count here/ Use getter function in the for loop
    int * lineCount = (int *) malloc(buffer_size * sizeof(int));

    //Store every files word count here/ Use getter function in the for loop
    int * wordCount = (int *) malloc(buffer_size * sizeof(int));
    
    //Store every files char count here/ Use getter function in the for loop
    int * charCount = (int *) malloc(buffer_size * sizeof(int));

    //--------------BUFFER--------------//
    if(lineCount == NULL || wordCount == NULL  || charCount == NULL){
            cout << "malloc() failed!" << endl;
            return 1;
    }


    //ERROR CHECK IF IS THERE MORE THAN ONE ARGUEMENT BEING PASSED
    if (argc < 2) {
      cout<<"No argument passed. Program terminating"<<endl;
      return 1;
    } 


    //For Loop to go through each argument passed 
    for(int i = 0; i < argc; i++){
    
        //Initialize filename/ Start at argv[1]
        char* file_name = argv[i+1];

        //PASS FILE NAME TO CLASS OBJECT 
        word fileInfo(file_name);

        
        
        
        //BUFFER SIZE VALIDITY
        if(buffer_count >= buffer_size){
            cout << "Reallocating the buffer from " << buffer_size << " to " << buffer_size * 2 << endl;

            buffer_size = buffer_size * 2;
            //RESIZE ALL BUFFERS
            charCount = (int *) realloc( charCount, buffer_size * sizeof(int));
            lineCount = (int *) realloc( lineCount, buffer_size * sizeof(int));
            wordCount = (int *) realloc( wordCount, buffer_size * sizeof(int));

            if(charCount == NULL || lineCount == NULL || wordCount == NULL) {
                    cout << "realloc() failed!" << endl;
                    return 1;
            }
        }



        //STORE OBJECT DATA IN BUFFERS
        charCount[buffer_count] = fileInfo.GetChars();
        lineCount[buffer_count] = fileInfo.GetLines();
        wordCount[buffer_count] = fileInfo.GetWords();

        //PRINT DATA
        cout<< "For argument "<< i+1 <<endl;
        cout<< "There are "<< lineCount[buffer_count]<<" lines." << endl;
        cout<< "There are "<< wordCount[buffer_count]<<" words." << endl;
        cout<< "There are "<< charCount[buffer_count]<<" characters."<< endl;
        fileInfo.PrintLetterCount();
        cout<<""<<endl;
        cout<<""<<endl;


        buffer_count++;
    }

    
    return 0;
}
