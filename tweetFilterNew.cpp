#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class tweetFilter{
private:
    vector<string> bannedWords;
    vector<int> wordFrequency;
    vector<string> mostFrequentWords; //TODO: complete this ! <<<+++>>>

    string getAstriskReplacable(string bannedWord) { 
        return bannedWord.replace(int(bannedWord.length()/2), 1, "*");
    }

public:
    tweetFilter(string bannedFileName){
        ifstream inFile(bannedFileName);
        string word = "";
        while(inFile >> word){
            bannedWords.push_back(word);
            wordFrequency.push_back(0);
        }
        inFile.close();
    }

    void resetWordFrequency(){
        int index=0;
        for(auto bannedword : bannedWords){
            wordFrequency.at(index++) = 0;
        }
    }

    string wordToLower(string word){
        for (char& c : word) {
            c = std::tolower(c);
        }
        return word;
    }

    void readFile(){
        //
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
                wordFrequency.at(wordindex)++ ;
                index = filteredTweet.find(bannedWord, index+1);
            }
            wordindex++ ;
        }
        return filteredTweet;
    }

    void filterFile(string inputFileName, string outputFileName) 
    {
        resetWordFrequency();
        ifstream inputFile(inputFileName);
        ofstream outputFile(outputFileName);
        string line="";
        if(inputFile){
            while(getline(inputFile, line))
            {
                string filteredLine = filterTweet(line);
                outputFile << filteredLine << endl;
            }
            displayResults(inputFileName);
        }
        else{
            cout << "The file named \'" << inputFileName << "\' doesn't exist or is missing from this folder!" << endl;
        }
        inputFile.close(); 
        outputFile.close();
    }

    void displayResults(string fileName){
        int i=0;
        cout << "\n\n > For File : " << fileName << "\n" << endl;
        for(auto bannedWord : bannedWords){
            cout << "\'" << bannedWord << "\' found " << wordFrequency.at(i++) << " times" << endl; 
        }
    }
};

int main(){
    tweetFilter tf("banned.txt");
    tf.filterFile("tweets1.txt","tweets1Filtered.txt");
    tf.filterFile("tweets2.txt","tweets2Filtered.txt");
    tf.filterFile("tweets3.txt","tweets3Filtered.txt");
    tf.filterFile("tweets4.txt","tweets4Filtered.txt");
    return 0;
}
