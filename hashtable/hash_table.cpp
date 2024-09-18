#include"HashTable.h"
#include<iostream>

//template <class T, class THash1, class THash2>

HashTable::HashTable(size_t size) noexcept{
    _capacity = size;
    _filled = 0;
    table.resize(size);
}

HashTable::~HashTable(){
    table.clear();
}

void HashTable::resize(){
    size_t past_buffer = _capacity;
    _capacity *= 2;
    _filled = 0;
    std::vector<std::list<std::pair<KeyType, ValueType>>> table_tmp = table;
    table.clear();
    table.resize(_capacity);
    for(int i = 0;i < past_buffer;i++){
        for(auto j = table_tmp[i].begin();j != table_tmp[i].end();j++){
            std::pair<KeyType, ValueType> tmp = *j;
            insert(tmp.first, tmp.second);
        }
    }

}

bool HashTable::find(const KeyType &key, ValueType &value)const{
    double tmp = value;
    size_t h1 = hash_function(key, 1);
    for(auto i = table[h1].begin(); i != table[h1].end();i++){
        std::pair<KeyType, ValueType> tmp = *i;
        if(tmp.first == key){
            value = tmp.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key){
    size_t h1 = hash_function(key, 2);
    for(auto i = table[h1].begin(); i != table[h1].end();i++){
        std::pair<KeyType, ValueType> tmp = *i;
        if(tmp.first == key){
            table[h1].erase(i);
            _filled--;
            break;
        }
    }
}

void HashTable::insert(const KeyType &key, const ValueType &value){
    if(getLoadFactor() > 0.75)
        resize();
    size_t h1 = hash_function(key, 1);
    table[h1].emplace_front(make_pair(key, value)); 
    _filled++;
}

double HashTable::getLoadFactor(){
    return (double)_filled/(double)_capacity;
}

size_t HashTable::hash_function(const KeyType &key, int y) const{
    int hash_result = 0;
    std::vector<int> power(9);
    power[0] = 1;
    for(int i = 1;i < 9;i++)
        power[i] = power[i-1]*10;
    int prost;
    if(y == 1)
        prost = power[8] + 7;
    else
        prost = power[8] + 9;
    for (int i = 0; key[i];++i)
        hash_result = (key[i]*power[i%9] + hash_result)%prost;
    hash_result = (hash_result * 2 + 1) % _capacity;
    return hash_result;
}

ValueType& HashTable::operator[](const KeyType &key){
    size_t h1 = hash_function(key, 1);
    std::pair<KeyType, ValueType> tmp;
    ValueType res = -1;
    auto i = table[h1].begin();
    for(i = table[h1].begin(); i != table[h1].end();i++){
        tmp = *i;
        if(tmp.first == key){
            res = tmp.second;
            break;
        }
    }
    return (*i).second;
}