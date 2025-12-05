#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

void generateTrace(
    const std::vector<std::string>& words,
    std::size_t N,
    std::ofstream& out
    ) {

    //create double linked list and unordered map

    std::list<std::string> LRU_list; // beginning is the MRU and end is LRU
    std::unordered_map<std::string, std::list<std::string>::iterator> map_holder;
    map_holder.reserve(N*2);

    for ( const auto& word : words ) {
        //hit
        if ( map_holder.find(word) != map_holder.end() ) {
            auto nodeIt =  map_holder.find(word)->second;
            std::string key = *nodeIt;
            LRU_list.erase(nodeIt);
            LRU_list.push_front(key);
            map_holder[word] = LRU_list.begin();
            out << "I " << word << " scruntching" << std::endl;
        }else if (LRU_list.size() < N) {
            LRU_list.push_front(word);
            map_holder[word] = LRU_list.begin();
            out << "I " << word  << " scruntching" << std::endl;
        }else {
            const std::string& tomb = LRU_list.back();
            LRU_list.pop_back();
            out<<"E " << tomb << " scruntching" << std::endl;
            map_holder.erase(tomb);
            LRU_list.pop_back();
            LRU_list.push_front(word);
            map_holder[word] = LRU_list.begin();
            out << "I " << word  << "scruntching" << std::endl;
        }

    }

}


int main(int argc, char* argv[]) {

    std::size_t N = std::stoull(argv[1]);
    unsigned seed = std::stoul(argv[2]);
    std::string wordFile = argv[3];
    std::string outputFile = argv[4];

    std::vector<std::string> words;
    words.reserve(4 * N);

    std::ifstream fin(wordFile);
    if (!fin.is_open()) {
        std::cout << "Error: Cannot open word file.\n";
        return 1;
    }
    std::string w;
    while (fin >> w) {
        words.push_back(w);
        if (words.size() == 4 * N)
            break;
    }
    fin.close();

    if (words.size() < 4 * N) {
        std::cout << "Error: Word file does not have enough words.\n";
        return 1;
    }


    std::vector<std::string> access_stream;

    for (std::size_t i = 0; i < N; ++i) {
        access_stream.push_back(words[i]);
    }


    for (std::size_t i = N; i < 2 * N; ++i) {
        for (int k = 0; k < 5; ++k) {
            access_stream.push_back(words[i]);
        }
    }

    for (std::size_t i = 2 * N; i < 4 * N; ++i)
        for (int k = 0; k < 3; ++k)
            access_stream.push_back(words[i]);


    std::mt19937 rng(seed);
    std::shuffle(access_stream.begin(), access_stream.end(), rng);
    access_stream.reserve(12 * N);

    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cout << "Error: Cannot open output trace file.\n";
        return 1;
    }

    out << "lru_profile " << N << " " << seed << "\n";

    generateTrace(access_stream, N, out);

    return 0;
}





