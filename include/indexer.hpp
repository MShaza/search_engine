#ifndef INDEXER_H
#define INDEXER_H
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <sstream>
#include "id_generator.hpp"
#include <math.h>
#include <utility>
#include <vector>
#include <algorithm>
class searchEngine
{
private:
    std::unordered_map<std::string, std::map<int, int>> invertedIndex;
    std::map<int, std::string> documents;
    std::set<std::string> stopWords;
    int totalDocs;
    std::vector<std::string> tokenzie(const std::string& text);
public:
    searchEngine();
    void addDocument(const std::string& docText);
    void buildIndex();
    std::vector<std::pair<int, double>> search(const std::string& query);
    void loadDefaultStopWords();
    std::vector<std::string> testTokenize(const std::string& text);
    const std::unordered_map<std::string, std::map<int, int>>& getIndex() const;



};
#endif