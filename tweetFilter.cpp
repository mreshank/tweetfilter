#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void filterAndFixTweets( string fromFileName, string toFileName, string words[] )
{
    int count=0;
    ifstream fromFile(fromFileName);
    string currentLine="", word="";
    ofstream toFile(toFileName);

    // Looping over the file to read from
    while( fromFile )
    {
        // Checking if the file has a next line and saving it temporarily in the variable "currentLine"
        if(getline( fromFile, currentLine ))
        {
            // Adding a space to make sure the last word gets read 
            currentLine += " ";

            // Looping on the extracted line of string to get the number of words present in it
            for(int i = 0; i < currentLine.length(); i++)
            {
                // Checking if a word is completed, by comparing the character to a space ' '
                if(currentLine[i]==' ')
                {
                    // Counting the number of words in the variable 'count'
                    count++;
                }
            }

            // Looping over the current file to save the edited/new string with filtered tweets into a new file
            for (int i = 0; i < currentLine.length(); i++) 
            {
                // Checking if a word is reached to save it in another file
                if (currentLine[i] == ' ' ) 
                {
                    // Comparing the word to all the banned words in the list
                    for( int i=0; i<count; i++ )
                    {
                        // Comparing the current word in the string line with the 
                        if(words[i]==word)
                        {
                            word="***";
                        }
                    }
                    toFile << word + currentLine[i] ;
                    word = "";
                }
                else 
                {
                    word += currentLine[i];
                }
            }
            toFile << endl;
        }
    }
    
    // Closing both the files
    fromFile.close();
    toFile.close();
}

void filterAndShowTweets( string bannedWords[], int bannedWordCount, string tweetWords[], int tweetWordCount )
{
    int count=0;
    
    // Looping Over the banned words 
    for( int i=0; i<bannedWordCount-1; i++ ) 
    {
        // Resetting the count to count another word
        count=0; 

        // Looping Over the tweet words 
        for( int j=0; j<tweetWordCount; j++ ) 
        {
            // Checking if the banned word is found in the tweets any number of times
            if( bannedWords[i] == tweetWords[j] ) 
            {   
                // Counting the number of times the banned word is found in the tweet
                count++;
            }
        }
        // Printing the banned words along with the counts of their existance in the tweet
        cout << "\'" << bannedWords[i] << "\' found " << count << " times" << endl;
    }
}

int main()
{
    // Declaring and Initializing variables for counting, and storing the length of both arrays
    int count=0, bannedWordCount=0, tweetWordCount=0;

    // Declaring and Initializing array variables to store the words of file 
    string bannedWords[100], tweetWords[500];

    // Declaring a file stream variable for reading a file
    fstream currentFile;

    // Opening the banned words file to read its words
    currentFile.open( "banned.txt", ios::in );

    // Looping over all the words in the banned words file and saving it in an array
    while( currentFile )
    {
        // Saving each banned word line-by-line in an array
        getline( currentFile, bannedWords[bannedWordCount++] );
    }
    // Closinig the Banned Words File
    currentFile.close();

    // Opening the 1st tweet file to read its words
    currentFile.open( "tweets1.txt", ios::in );

    // Looping over all the words in tweet file and saving it in an array
    while( currentFile >> tweetWords[tweetWordCount++] );

    filterAndShowTweets(bannedWords, bannedWordCount, tweetWords, tweetWordCount);
    
    filterAndFixTweets("tweets1.txt", "tweets1Filtered.txt", bannedWords);

    // Closinig the 1st Tweet File
    currentFile.close();

    // Ending the main function by returning 0
    return 0;
}
 
