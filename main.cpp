#include <iostream>
#include <vector>
#include <fstream>

void loadData(std::vector<std::string> &wordList)
{
    std::string line;
    std::ifstream input("wordList.txt");
    if (input.is_open())
    {
        while (std::getline(input, line))
        {
            wordList.push_back(line);
        }
    }
}

std::string pickWord(const std::vector<std::string> &wordList)
{
    bool needSearch = true;
    srand(time(NULL));
    while (needSearch)
    {
        int position = rand() % wordList.size();
        std::string pickedWord = wordList.at(position);
        if (pickedWord.size() >= 3)
        {
            needSearch = false;
            return pickedWord;
        }
    }
    return "ERROR";
}

void findAllOccurances(std::vector<int> &vec, std::string data, std::string toSearch)
{
    // Get the first occurrence
    int pos = data.find(toSearch);
    // Repeat till end is reached
    while (pos != std::string::npos)
    {
        // Add position to the vector
        vec.push_back(pos);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + toSearch.size());
    }
}

void playHangMan()
{
    bool keepPlaying = true;
    int guesses = 5;

    std::vector<std::string> wordList;
    loadData(wordList);
    std::string word = pickWord(wordList);
    char wordArray[word.size()];

    for (int i = 0; i < word.size(); i++)
    {
        wordArray[i] = '-';
    }

    while (keepPlaying && guesses > 0)
    {
        for (size_t i = 0; i < word.size(); i++)
        {
            std::cout << wordArray[i];
        }
        std::cout << std::endl;
        std::cout << "Guesses Left: " << guesses << std::endl;
        char letter;
        std::cout << "Enter guess" << std::endl;
        std::cin >> letter;

        //If it was correct guess
        if (word.find(letter) != std::string::npos)
        {
            std::cout << "Correct guess" << std::endl;
            std::string letter_s = std::string(1, letter);
            std::vector<int> pos;
            findAllOccurances(pos, word, letter_s);
            for (auto &place : pos)
            {
                wordArray[place] = letter;
            }

            bool done = true;
            for (size_t i = 0; i < word.size(); i++)
            {
                if (wordArray[i] == '-')
                    done = false;
            }
            if (done)
            {
                std::cout << "Correctly guesses word: " << word << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "The word does not contain " << letter << std::endl;
            guesses--;
        }
    }
    std::cout << "Failed to guess word" << std::endl;
}

int main()
{
    playHangMan();
    return 0;
}