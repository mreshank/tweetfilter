#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string>

using namespace std; // Using standard namespace

// Declare class called tweetFilter
class tweetFilter
{

private:

    // Vector to store frequency of banned words
    vector<int> bannedWordFrequency;

    vector<string>  bannedWords, /* a vector that stores the number of times each banned word appears in the file being filtered.*/
                    positiveWords, /* a vector that stores positive words. */
                    negativeWords, /*  a vector that stores negative words. */
                    allWords, /* a vector that stores all words in the file being filtered. */
                    mostFrequentWords; /* a vector to store the most frequent words in the file being filtered. */

    // Private function to replace the middle of a banned word with asterisks
    string getAstriskReplacable(string bannedWord) 
    { 
        return bannedWord.replace( int( bannedWord.length()/2) , 1, "*");
    }

public:

    // Constructor to initialize banned, positive, and negative words
    tweetFilter(string bannedFileName, string positiveFileName, string negativeFileName)
    {
        // Opening banned words file
        ifstream bannedFile(bannedFileName);

        // Opening positive words file
        ifstream positiveFile(positiveFileName);

        // Opening negative words file
        ifstream negativeFile(negativeFileName);

        // Declare an empty string to read words from file
        string word = "";

        // Read each word from banned file
        while(bannedFile >> word)
        {
            // Add word to banned words vector
            bannedWords.push_back(word);
            // Add word frequency to banned words frequency vector
            bannedWordFrequency.push_back(0);
        }

        // Read each word from positive file
        while(positiveFile >> word)
        {
            // Add word to positive words vector
            positiveWords.push_back(word);
        }

        // Read each word from negative file
        while(negativeFile >> word)
        {
            // Add word to negative words vector
            negativeWords.push_back(word);
        }

        // Closing banned words file
        bannedFile.close();
        // Closing positive words file
        positiveFile.close();
        // Closing negative words file
        negativeFile.close();
    }

    // a method that sets all elements of the bannedWordFrequency vector to zero.
    void resetbannedWordFrequency()
    {
        int index=0;

        // Looping through each banned word
        for(auto bannedword : bannedWords)
        {
            // Reset banned word frequency to 0 and increment index for next iteration
            bannedWordFrequency.at(index++) = 0;
        }
    }

    // method to convert a string to lowercase (here a word to lowercase).
    string wordToLower(string word)
    {
        // Looping through each character in the word
        for (char& c : word) 
        {
            // Convert character to lowercase
            c = std::tolower(c);
        }

        // Return lowercase word
        return word;
    }

    // method to extract individual words from a tweet and stores them in a vector called allWords.
    void saveWords(string tweet)
    {
        // Declare an empty string to store a word
        string word="";

        // Looping through each character in the tweet
        for(int i=0; i<tweet.length(); i++)
        {
            // check if the current character is a delimiter
            if(tweet[i]==' '||tweet[i]=='.'||tweet[i]==','||tweet[i]=='!'||tweet[i]=='?'||tweet[i]==':'||tweet[i]==';')
            {
                // if word is not empty, then...
                if(word!="")
                { 
                    // push it into the allWords vector
                    allWords.push_back(word);
                }
                // reset the word
                word="";
            }
            else
            {
                // append the current character to the word
                word += tweet[i];
            }
        }
    }

    /*  a method that replaces banned words in a tweet with asterisks 
        and updates the bannedWordFrequency vector with the 
        number of times each banned word appears in the tweet.*/
    string filterTweet(string tweet)
    {
        int wordindex = 0;

        // create a copy of the original tweet for processing
        string filteredTweet = tweet;

        // looping through the banned words
        for (auto bannedWord : bannedWords)
        {
            // search for the banned word in the filtered tweet converted to lower case (case-insensitive) 
            int index = wordToLower(filteredTweet).find(bannedWord);

            // while the banned word is found in the filtered tweet
            while (index != string::npos)
            {
                // replace the banned word with asterisks
                filteredTweet.replace(index, bannedWord.length(), getAstriskReplacable(bannedWord));

                // increment the frequency count for the banned word
                bannedWordFrequency.at(wordindex)++ ;

                // search for the banned word again from the next position
                index = filteredTweet.find(bannedWord, index+1);
            }
            // increment the word index
            wordindex++ ;
        }
        // return the filtered tweet
        return filteredTweet;
    }

    /*  a method that filters a file by reading it line by line, 
        filtering each line using the filterTweet method, 
        writing the filtered lines to a new file, 
        and displaying the sentiment analysis of each filtered line. 
        It also calls the saveWords method to store all words in the file in the allWords vector, 
        and the displayResults method to display the banned words in the file and their frequencies. */
    void filterFile(string inputFileName, string outputFileName) 
    {
        // reset the frequency count for banned words
        resetbannedWordFrequency(); 

        // open the input file
        ifstream inputFile(inputFileName); 

        // open the output file
        ofstream outputFile(outputFileName);

        string line="";

        // check if the input file is opened successfully
        if(inputFile)
        {
            // print the heading for the sentiment analysis report
            cout << "\n\n>> The sentiment analysis of the file \'" << inputFileName << "\' is :-\n" << endl;
            
            // loop through each line in the input file
            while(getline(inputFile, line))
            {
                // filter the line using the filterTweet function
                string filteredLine = filterTweet(line);

                // write the filtered line to the output file
                outputFile << filteredLine << endl;

                // save the words from the line to the allWords vector
                saveWords(line);

                // print the filtered line and its sentiment analysis
                cout << filteredLine << " : " << sentimentAnalysis(filteredLine) << endl;
            }
            // display the final results of the sentiment analysis
            displayResults();
        }
        else
        {
            // print an error message if the input file cannot be opened
            cout << "The file named \'" << inputFileName << "\' doesn't exist or is missing from this folder!" << endl;
        }
        // close the input file
        inputFile.close(); 

        // close the output file
        outputFile.close();
    }

    // Define a function to display the usage frequency of banned words in filtered tweets
    void displayResults()
    {
        int i=0;

        cout << "\n>> And the usage of banned words in it are :-\n" << endl;

        // Looping through each banned word
        for(auto bannedWord : bannedWords)
        {
            // Display the banned word and its frequency
            cout << "\'" << bannedWord << "\' found " << bannedWordFrequency.at(i++) << " times" << endl; 
        }
    }

    // Defining a function to perform sentiment analysis on a tweet and return the result
    string sentimentAnalysis(string tweet)
    {
        // Initialize a counter variable to analyse the check through +1 and -1 pointing on sentiments 
        int sentimentCount = 0;

        // Looping through each positive word
        for (auto word : positiveWords)
        {
            // Find the index of the positive word in the tweet
            int index = wordToLower(tweet).find(word);

            // If the positive word is found in the tweet
            while (index != string::npos)
            {
                // Increase the sentiment count
                sentimentCount++ ;

                // Search for the next occurrence of the positive word
                index = wordToLower(tweet).find(word, index+1);
            }
        }
        // Looping through each negative word
        for (auto word : negativeWords)
        {
            // Find the index of the negative word in the tweet
            int index = wordToLower(tweet).find(word);

            // If the negative word is found in the tweet
            while (index != string::npos)
            {
                // Decrease the sentiment count
                sentimentCount-- ;

                // Search for the next occurrence of the negative word
                index = wordToLower(tweet).find(word, index+1);
            }
        }
        // Determining the sentiment of the tweet based on the sentiment count and returning it
        return (sentimentCount>=0)?(sentimentCount>0)?"Positive":"Neutral":"Negative";
    }

};

int main(){
    // Create a tweetFilter object with specified files for banned, positive and negative words
    tweetFilter tf("banned.txt", "positive.txt", "negative.txt");

    // Filter the first input tweet file and save the result to the first output tweet file
    tf.filterFile("tweets1.txt","tweets1Filtered.txt");

    // Filter the second input tweet file and save the result to the second output tweet file
    tf.filterFile("tweets2.txt","tweets2Filtered.txt");

    // Filter the third input tweet file and save the result to the third output tweet file
    tf.filterFile("tweets3.txt","tweets3Filtered.txt");

    // Filter the fourth input tweet file and save the result to the fourth output tweet file
    tf.filterFile("tweets4.txt","tweets4Filtered.txt");
    
    // End of the program
    return 0; 
}
