#include "id_generator.hpp"
int generateId(){
    std::cout << "[DEBUG - generateId] Enter function"<< std::endl;
    std::ostringstream oss;
    //std::srand(std::time(nullptr));
    //oss<<"TRANX"<<std::rand() % 100000;
    std::random_device rd;                  // Non-deterministic random number generator (uses hardware entropy)
    std::mt19937 gen(rd());                 // Mersenne Twister engine (high-quality PRNG), seeded with `rd`
    std::uniform_int_distribution<> dis(10000, 99999); // Uniform distribution between 10,000 and 99,999
    oss << dis(gen);
    std::string strValue = oss.str();
    //std::cout << "The str value is: " << strValue << std::endl;
    int intValue = 0;
    try {
        intValue = std::stoi(strValue);
        //std::cout << "The integer value is: " << intValue << std::endl;
    } catch (const std::exception& e) {
        //std::cerr << "Error during conversion: " << e.what() << std::endl;
    }
    std::cout << "[DEBUG - generateId] Exit function successfully"<< std::endl;
    return intValue;
}