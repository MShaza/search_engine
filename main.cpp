#include <iostream>
#include "indexer.hpp"

int main(){
    std::cout<<"[Debugh - main] Enter program"<<std::endl;
    searchEngine engine;
    engine.addDocument("ChatGPT iS tRansfOrming! chatgpt the World.");
    engine.addDocument("Work of the day");
    engine.addDocument("ChatGPT is amazing");
    //std::vector<std::string> tokens = engine.testTokenize("ChatGPT iS tRansfOrming! the World.");
    //for(const auto token :tokens){
    //    std::cout<<"[Debugh - main]"<<token<<std::endl;
    //}
    engine.buildIndex();
    auto results = engine.search("chatgpt work");
    /**auto index = engine.getIndex();
    for (const auto& [token, docMap] : index) {
        std::cout << token << " => ";
        for (const auto& [docID, freq] : docMap) {
            std::cout << "[" << docID << ": " << freq << "] ";
        }
        std::cout << "\n";
    }**/
    

    for (const auto& [docID, score] : results) {
    std::cout << "Doc " << docID << " — Score: " << score << "\n";
    }
    return 0;
}