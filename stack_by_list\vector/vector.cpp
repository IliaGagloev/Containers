#include"VectorNew.h"
//#include<iostream>

using namespace std;
Vector::Vector(const ValueType* rawArray, const size_t size, float coef){
    if(coef <= 1){
        throw invalid_argument("Coef must be > 1");
    }
    _data = new ValueType[size];
    copy(rawArray, rawArray + size, _data);
    _multiplicativeCoef = coef;
    _capacity = size;
    _size = size;
}
Vector::Vector(const Vector& other) {
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new ValueType[_capacity];
    copy(other._data, other._data + _size, _data);  // Копируем элементы
}
Vector& Vector::operator= (const Vector &other) {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        ValueType *newData = new ValueType[_capacity];
        copy(other._data, other._data + _size, newData);
        delete[] _data; 
        _data = newData;
    }
    return *this;
}


Vector::Vector(Vector&& other) noexcept {
    _size = other._size;
    _capacity = other._capacity;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

Vector& Vector::operator=(Vector &&other) noexcept {
    if (this != &other) {
        delete[] _data; 
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

ValueType* Vector::getSequence() const{
    return _data;
}

size_t Vector::size()const{
    return _size;
}

size_t Vector::capacity()const{
    return _capacity;
}

bool Vector::isEmpty()const{
    return _size == 0;
}

double Vector::loadFactor()const{
    return _capacity/_size;
}
const ValueType& Vector::operator[](size_t idx)const{
    if(idx >= _size)
        throw "Out_of_range";
    else 
        return _data[idx];
}
ValueType& Vector::operator[](size_t idx){
    if(idx >= _size)
        throw "Out_of_range";
    else 
        return _data[idx];
}
void Vector::push(const ValueType& value){
    if(_capacity == 0)
        reserve(1 * _multiplicativeCoef);
    if(_size >= _capacity){
        reserve(_capacity*_multiplicativeCoef);
    }
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value){
    if(_capacity == 0)
        reserve(1 * _multiplicativeCoef);
    if(_size + 1 >= _capacity)
        reserve(_capacity*_multiplicativeCoef);
    if(_size < _capacity){
        _size++;
        for(int i = _size;i >0;i--){
            _data[i] = _data[i-1];
        }
        _data[0] = value;
    }
}

void Vector::pop(){
    if(_size == 0)
        throw "Error";
    else if(_size != 0)_size--;
}
const ValueType& Vector::top()const{
    return _data[_size - 1];
}
void Vector::popFront(){
    if(_size == 0)
        throw "Error";
    else{
        for(int i = 0;i < _size - 1;i++)
            _data[i] = _data[i+1];
        _size--;
    }
}

void Vector::erase(size_t pos, size_t count){
    if(pos + count >= _size){
        _size = pos;
    }else{
        for(int i = pos + count;i < _size;i++)
            _data[i - count] = _data[i];
        _size = _size - count;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    if(beginPos > endPos || beginPos >= _size)
        return;
    if(endPos >= _size){
        _size = beginPos;
    }else{
        int cnt = _size - endPos - 1;
        for(int i = 0;i < cnt;i++){
             _data[i + beginPos] = _data[endPos + i];
        }
        
        _size =_size - cnt;
    }
}

void Vector::insert(const ValueType& value, size_t pos){
    if(_capacity == 0)
        reserve(1 * _multiplicativeCoef);
    if(_size == _capacity)
        reserve(_capacity*_multiplicativeCoef);
    for(int i = _size;i > pos;i--)
        _data[i] = _data[i-1];
    _data[pos] = value;
    _size++;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos){
    if(_capacity == 0)
        reserve(1 * _multiplicativeCoef);
    while(_capacity < size + _size)
        reserve(_capacity* _multiplicativeCoef);
    ValueType* b = new ValueType[_size + size];
    for(int i = 0;i < size+_size;i++){
        if(i < pos)
            b[i] = _data[i];
        else if(i >= pos && i < pos+size)
            b[i] = values[i-pos];
        else
            b[i] = _data[i-size];
    }
    for(int i = 0;i < size + _size;i++)
        _data[i] = b[i];
    delete[] b;
    _size+=size;
}
void Vector::insert(const Vector& vector, size_t pos){
    if(_capacity == 0)
        reserve(1 * _multiplicativeCoef);
    while(_capacity < vector._size + _size)
        reserve(_capacity* _multiplicativeCoef);
    ValueType* b = new ValueType[_size + vector.size()];
    for(int i = 0;i < _size + vector.size();i++){
        if(i < pos)
            b[i] = _data[i];
        else if(i >= pos && i < pos+vector.size())
            b[i] = vector[i-pos];
        else
            b[i] = _data[i-vector.size()];
    }
    for(int i = 0;i < vector.size() + _size;i++)
        _data[i] = b[i];
    delete[] b;
    _size+=vector.size();
}
void Vector::reserve(size_t capacity){
    if(_capacity < capacity){
        ValueType* b = new ValueType[capacity];
        for(int i = 0;i < _size;i++)
            b[i] = _data[i];
        delete[] _data;
        _data = b;
        _capacity = capacity;
    }
}
void Vector::shrinkToFit(){
    _capacity = _size;
    ValueType *b = new ValueType[_size];
    for (int i = 0; i < _size; i++){
        b[i] = _data[i];
    }
    delete[] _data;
    _data = b;

}

long long Vector::find(const ValueType& value) const{
    for(int i = 0;i < _size;i++)
        if(_data[i] == value)
            return i;
    return -1;
}

Vector::Iterator::Iterator(ValueType* ptr) {
    _ptr = ptr; 
}

ValueType& Vector::Iterator::operator*() {
    return *_ptr; 
}

const ValueType& Vector::Iterator::operator*() const {
    return *_ptr; 
}

ValueType* Vector::Iterator::operator->() {
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr; 
}

bool Vector::Iterator:: operator!=(const Iterator& other) const {
    return _ptr != other._ptr;
}


Vector::Iterator Vector::begin() {
    return Iterator(_data);
}

Vector::Iterator Vector::end() {
    return Iterator(_data + _size);
}
Vector::~Vector(){
    delete[] _data;
}
