#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include <unordered_map>
using namespace std;

class tweetFilter
{
private:
    vector<string>  bannedWords,
                    positiveWords,
                    negativeWords, 
                    allWords, 
                    mostFrequentWords; //TODO: complete this ! <<<+++>>>
    vector<int> bannedWordFrequency;
    // unordered_map<string, int> word_freq;
    // vector<string, int> mostFrequentWords; 

    string getAstriskReplacable(string bannedWord) { 
        return bannedWord.replace(int(bannedWord.length()/2), 1, "*");
    }

public:
    tweetFilter(string bannedFileName, string positiveFileName, string negativeFileName)
    {
        ifstream bannedFile(bannedFileName);
        ifstream positiveFile(positiveFileName);
        ifstream negativeFile(negativeFileName);
        string word = "";
        while(bannedFile >> word){
            bannedWords.push_back(word);
            bannedWordFrequency.push_back(0);
        }
        while(positiveFile >> word){
            positiveWords.push_back(word);
        }
        while(negativeFile >> word){
            negativeWords.push_back(word);
        }
        bannedFile.close();
        positiveFile.close();
        negativeFile.close();
    }

    void resetbannedWordFrequency(){
        int index=0;
        for(auto bannedword : bannedWords){
            bannedWordFrequency.at(index++) = 0;
        }
    }

    string wordToLower(string word){
        for (char& c : word) {
            c = std::tolower(c);
        }
        return word;
    }

    void saveWords(string tweet){
        string word="";
        for(int i=0; i<tweet.length(); i++){
            if(tweet[i]==' '||tweet[i]=='.'||tweet[i]==','||tweet[i]=='!'||tweet[i]=='?'||tweet[i]==':'||tweet[i]==';'){
                if(word!=""){ 
                    allWords.push_back(word);
                    // word_freq[word]++;
                }
                word="";
            }
            else{
                word += tweet[i];
            }
        }
    }

    string filterTweet(string tweet)
    {
        int wordindex = 0;
        string filteredTweet = tweet;
        for (auto bannedWord : bannedWords)
        {
            int index = wordToLower(filteredTweet).find(bannedWord);
            while (index != string::npos)
            {
                filteredTweet.replace(index, bannedWord.length(), getAstriskReplacable(bannedWord));
                bannedWordFrequency.at(wordindex)++ ;
                index = filteredTweet.find(bannedWord, index+1);
            }
            wordindex++ ;
        }
        return filteredTweet;
    }

    void filterFile(string inputFileName, string outputFileName) 
    {
        resetbannedWordFrequency();
        ifstream inputFile(inputFileName);
        ofstream outputFile(outputFileName);
        string line="";
        if(inputFile){
            cout << "\n\n>> The sentiment analysis of the file \'" << inputFileName << "\' is :-\n" << endl;
            while(getline(inputFile, line))
            {
                string filteredLine = filterTweet(line);
                outputFile << filteredLine << endl;
                saveWords(line);
                cout << filteredLine << " : " << sentimentAnalysis(filteredLine) << endl;
            }
            displayResults();
        }
        else{
            cout << "The file named \'" << inputFileName << "\' doesn't exist or is missing from this folder!" << endl;
        }
        inputFile.close(); 
        outputFile.close();
    }

    void displayResults()
    {
        int i=0;
        cout << "\n>> And the usage of banned words in it are :-\n" << endl;
        for(auto bannedWord : bannedWords)
        {
            cout << "\'" << bannedWord << "\' found " << bannedWordFrequency.at(i++) << " times" << endl; 
        }
    }

    string sentimentAnalysis(string tweet){
        int sentiment = 0;
        for (auto word : positiveWords)
        {
            int index = wordToLower(tweet).find(word);
            while (index != string::npos)
            {
                sentiment++ ;
                index = wordToLower(tweet).find(word, index+1);
            }
        }
        for (auto word : negativeWords)
        {
            int index = wordToLower(tweet).find(word);
            while (index != string::npos)
            {
                sentiment-- ;
                index = wordToLower(tweet).find(word, index+1);
            }
        }
        return (sentiment>=0)?(sentiment>0)?"Positive":"Neutral":"Negative";
    }
};

int main(){
    tweetFilter tf("banned.txt", "positive.txt", "negative.txt");
    tf.filterFile("tweets1.txt","tweets1Filtered.txt");
    tf.filterFile("tweets2.txt","tweets2Filtered.txt");
    tf.filterFile("tweets3.txt","tweets3Filtered.txt");
    tf.filterFile("tweets4.txt","tweets4Filtered.txt");
    return 0;
}
