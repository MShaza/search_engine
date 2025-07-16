#include "indexer.hpp"

searchEngine::searchEngine()
{
    totalDocs = 0;
    loadDefaultStopWords();
}
void searchEngine::loadDefaultStopWords()
{
    stopWords = {"the", "is", "and", "a", "of", "in", "to", "with"};
}
std::vector<std::string> searchEngine::testTokenize(const std::string &text)
{
    std::vector<std::string> tokens = tokenzie(text);
    return tokens;
}
std::vector<std::string> searchEngine::tokenzie(const std::string &text)
{
    std::cout << "[Debug - searchEngine::testTokenize] Enter Function" << std::endl;
    std::string convertedDoc = "";
    std::vector<std::string> tokens;
    if (text.length() < 0)
    {
        std::cout << "[Debug - searchEngine::testTokenize] Document is empty" << std::endl;
        return tokens;
    }
    std::cout << "[Debug - searchEngine::testTokenize] Remove non-alphanumeric charaters" << std::endl;
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = c + 32;
            }
            convertedDoc += c; // append the converted character
        }
        else
        {
            convertedDoc += ' ';
        }
    }
    std::cout << "[Debug - searchEngine::testTokenize] Generates token" << std::endl;
    std::stringstream ss(convertedDoc);
    std::string word;
    while (ss >> word)
    {
        if (stopWords.find(word) == stopWords.end())
        {
            tokens.push_back(word);
        }
    }
    std::cout << "[Debug - searchEngine::testTokenize] Function ended succesfully" << std::endl;

    return tokens;
}
void searchEngine::addDocument(const std::string &docText)
{
    std::cout << "[Debug - searchEngine::addDocument] Function enter" << std::endl;
    int docId = generateId();
    documents[docId] = docText;
    std::cout << "[Debug - searchEngine::addDocument] ID: "<< docId << ", Contect: "<< docText<< std::endl;
    totalDocs++;
    std::cout << "[Debug - searchEngine::addDocument] Function ended succesfully" << std::endl;
}
void searchEngine::buildIndex()
{
    for (const auto &[docId, content] : documents)
    {
        std::vector<std::string> tokens = tokenzie(content);
        for (const std::string &token : tokens)
        {
            invertedIndex[token][docId]++;
        }
    }
}
std::vector<std::pair<int, double>> searchEngine::search(const std::string &query)
{
    std::cout << "[Debug - searchEngine::search] Function ended search" << std::endl;
    std::vector<std::string> tokens = tokenzie(query);
    std::unordered_map<int, double> docScores;
    double tokenFrequency = 0;
    double IDF = 0;
    double relevanceScore = 0;
    std::vector<std::pair<int, double>> results;
    for (const auto &token : tokens)
    {
        auto it = invertedIndex.find(token);
        if (it != invertedIndex.end())
        {
            const std::map<int, int> &docFrequencies = it->second;
            for (const auto &pair : docFrequencies)
            {
                tokenFrequency = static_cast<double>(pair.second);
                 IDF = std::log(static_cast<double>(totalDocs) / tokenFrequency);
                 relevanceScore = IDF * tokenFrequency;
                docScores.insert({pair.first, relevanceScore});
               
            }
        }
        else
        {
           std::cout << "[Debug - searchEngine::search] Token: " << token << " not found"  << std::endl;
        }
    }
     for(const auto pair : docScores){
           results.push_back(pair);
        }
      std::sort(results.begin(), results.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second; // Sort by score in descending order
              });
    return results;
}
const std::unordered_map<std::string, std::map<int, int>> &searchEngine::getIndex() const
{
    return invertedIndex;
}