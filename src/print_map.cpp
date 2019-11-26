//
// Created by Oskar Boer on 25/11/2019.
//

#include "main.h"

using namespace std;

template<typename K, typename V>
void print_map(std::unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}
