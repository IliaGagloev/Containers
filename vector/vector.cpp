#include "VectorNew.h"
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <iostream>
using namespace std;

Vector::Vector(const ValueType* rawArray, const size_t size, float coef){
    _size = size; //! текущий размер
    _capacity = _size;
    _multiplicativeCoef = coef; 
    _data = new ValueType[_size];
    for (size_t i = 0; i<size; i++){
	    _data[i]=rawArray[i];
    }
}

Vector::Vector(const Vector& other){
    _size = other._size; //! текущий размер
    _capacity = _size;
    _multiplicativeCoef = other._multiplicativeCoef; 
    _data = new ValueType[_size];
    memcpy(_data, other._data, _size*sizeof(ValueType));
}

Vector& Vector::operator=(const Vector& other)  {
    if (this == &other){
        return *this;
    }
    delete[] _data;
    _size = other._size; //! текущий размер
    _capacity = _size;
    _multiplicativeCoef = other._multiplicativeCoef; 
    _data = new ValueType[_size];
    memcpy(_data, other._data, _size*sizeof(ValueType));
    return *this;
}

Vector::Vector(Vector&& other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other){
        return *this;
    }
    _data = other._data;
    _size = other._size; //! текущий размер
    _capacity = _size;
    return *this;
}

Vector::~Vector(){
    delete[] _data;
}

void Vector::pushBack(const ValueType& value){
    if (0 == _capacity){
        _capacity = _multiplicativeCoef;
        _size = 0;
        _data = new ValueType[(size_t)_multiplicativeCoef];
    }
    if (_size == _capacity){
        _capacity = _capacity * _multiplicativeCoef;
        _data = (ValueType*) realloc (_data, _capacity*sizeof(ValueType));
    }
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value){
    if (0 == _capacity){
        _capacity = _multiplicativeCoef;
        _size = 0;
        _data = new ValueType[(size_t)_multiplicativeCoef];

    }
    if (_size == _capacity){
        _capacity = _capacity * _multiplicativeCoef;
        _data = (ValueType*) realloc (_data, _capacity*sizeof(ValueType));
    }
    _size++;
    for (int i = _size-1; i>=0; i--){
        _data[i+1]=_data[i];
    }
    _data[0] = value;
}

void Vector::insert(const ValueType &value, size_t pos) {
  if (_capacity == 0) {
    _capacity = 1;
    if (_data == nullptr) {
      _data = new ValueType[1];
    }
    _size = 1;
  }

  if (pos <= _size) {
    if (_size >= _capacity) {
      reserve(_capacity * _multiplicativeCoef);
    }
    memmove(_data + pos + 1, _data + pos, sizeof(ValueType) * (_size - pos));
    _data[pos] = value;
    ++_size;
  }
}

void Vector::insert(const ValueType *values, size_t size, size_t pos) {
  if (_capacity == 0) {
    _capacity = 1;
    if (_data == nullptr) {
      _data = new ValueType[1];
    }
    _size = 1;
  }
  if (pos <= _size) {
    if (_size + size - 1 >= _capacity) {
      reserve((_capacity + size) * _multiplicativeCoef);
    }
    memmove(_data + pos + size, _data + pos, sizeof(ValueType) * (_size - pos));
    for (size_t i = 0; i < size; i++) {
      _data[i + pos] = values[i];
    }
    _size += size;
  }
}


void Vector::insert(const Vector &vector, size_t pos) {
  if (_capacity == 0) {
    _capacity = 1;
    if (_data == nullptr) {
      _data = new ValueType[1];
    }
    _size = 1;
  }
  if (pos <= _size) {
    size_t size = vector.size();
    if (_data == nullptr) {
      _data = new ValueType[vector.size()];
      _size = size;
      _capacity = size;
      for (size_t i = 0; i < size; i++) {
        _data[i] = vector[i];
      }
    } else {
      if (_size + size - 1 >= _capacity) {
        reserve((_capacity + size) * _multiplicativeCoef);
      }
      memmove(_data + pos + size, _data + pos,
              sizeof(ValueType) * (_size - pos));
      for (size_t i = 0; i < size; i++) {
        _data[i + pos] = vector[i];
      }
      _size += vector.size();
    }
  }
}

void Vector::popBack() {
  if (_size != 0) {
    --_size;
    return;
  }
  throw std::out_of_range("Out of range");
}

void Vector::popFront() {
  if (_size != 0) {
    memmove(_data, _data + 1, _size);
    --_size;
    return;
  }
  throw std::out_of_range("Out of range");
}

void Vector::erase(size_t pos, size_t count) {
  if (pos + count > _size) {
    _size = pos >= _size ? _size : pos;
  } else {
    size_t difference = _size - pos - count;
    for (size_t i = 0; i < difference; ++i) {
      (*this)[i + pos] = (*this)[i + pos + count];
    }
    _size = _size - count;
  }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
  if (beginPos < endPos) {
    erase(beginPos, endPos - beginPos);
  }
}

size_t Vector::size() const{
    return _size;
  }

size_t Vector::capacity() const{
    return _capacity;
  }
  
double Vector::loadFactor() const {
    return (double)_size/(double)_capacity;
}


ValueType& Vector::operator[](size_t idx){
	return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const {
	return _data[idx];
}

long long Vector::find(const ValueType& value) const{
	for (int i =0; i<_size; i++){
		if (_data[i] == value){
			return i;
		}
	}
	return -1;
}

void Vector:: reserve(size_t capacity){
	if (capacity > _capacity){
		_capacity = capacity;
		ValueType *tmp = new ValueType[_capacity];
		for (size_t i = 0; i<_size; i++){
			tmp[i] = _data[i];
		}
		delete[] _data;
		_data = tmp;
	}
}

void Vector::shrinkToFit(){
    	if (_size < _capacity){
		_capacity = _size;
		ValueType *tmp = new ValueType[_capacity];
		for (size_t i = 0; i<_size; i++){
			tmp[i] = _data[i];
		}
		delete[] _data;
		_data = tmp;
	}
}


Vector::Iterator::Iterator(ValueType* ptr){
    _ptr = ptr;
}

ValueType& Vector::Iterator:: operator*(){
    return *_ptr;
}

 const ValueType& Vector::Iterator:: operator*() const {
    return *_ptr;
 }

 ValueType* Vector::Iterator:: operator->(){
    return _ptr;
 }

 const ValueType* Vector::Iterator:: operator->() const {
    return _ptr;
 }

  Vector::Iterator Vector::Iterator:: operator++(){
    return Iterator(++_ptr);
 }

 Vector::Iterator Vector::Iterator:: operator++(int){
    return Iterator(_ptr++);
 }

 bool Vector::Iterator::operator==(const Iterator& other) const {
    return (this->_ptr == other._ptr);
 }

 bool Vector::Iterator::operator!=(const Iterator& other) const {
    return (this->_ptr != other._ptr);
 }

Vector::Iterator Vector::begin(){
    return Iterator(_data);
 }  
 
 Vector::Iterator Vector::end(){
    return Iterator(&_data[_size]);
 }
