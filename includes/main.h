//
// Created by Organa Longbottom on 25/11/2019.
//

#ifndef UNTITLED1_MAIN_H
#define UNTITLED1_MAIN_H

#include <map>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

template<typename K, typename V>
void print_map(std::unordered_map<K,V> const &m);

template<typename K, typename V>
void prints_map(std::map<K, V> ordered);

template<typename K, typename V>
void generate_prob(std::unordered_map<K, V> &dict, std::string filename);

#endif //UNTITLED1_MAIN_H
