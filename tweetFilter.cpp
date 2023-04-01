#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // Declaring and Initializing variables for counting, and storing the length of both arrays
    int count=0, len1=0, len2=0;

    // Declaring and Initializing array variables to store the words of file 
    string bannedWords[100], tweetWords[500];

    // Declaring a file stream variable for reading a file
    fstream currentFile;

    // Opening the banned words file to read its words
    currentFile.open( "test1.txt", ios::in );

    // Looping over all the words in the banned words file and saving it in an array
    while( currentFile )
    {
        // Saving each banned word line-by-line in an array
        getline( currentFile, bannedWords[len1++] );
    }
    // Closinig the Banned Words File
    currentFile.close();

    // Opening the 1st tweet file to read its words
    currentFile.open( "test2.txt", ios::in );

    // Looping over all the words in tweet file and saving it in an array
    while( currentFile >> tweetWords[len2++] );

    // Closinig the 1st Tweet File
    currentFile.close();
    
    // Looping Over the banned words 
    for( int i=0; i<len1-1; i++ ) 
    {
        // Resetting the count to count another word
        count=0; 

        // Looping Over the tweet words 
        for( int j=0; j<len2; j++ ) 
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

    // Ending the main function by returning 0
    return 0;
}
