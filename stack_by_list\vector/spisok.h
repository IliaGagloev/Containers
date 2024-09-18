#pragma once

#include<iostream>
#include"StackImplementation.h"

using ValueType = double;

struct node{
    ValueType data;
    node *prev = NULL, *next = NULL;
};


class List:virtual public IStackImplementation{
public:
    List() = default;
    List(const ValueType* values, size_t size);
    ~List() = default;
    List& operator=(const List& other) = default;
    void pop();
    void push(const ValueType& value)override;
    const ValueType& top()const override;
    ValueType* getSequence() const override;
    size_t size() const;
    bool isEmpty() const;
private:
    node *Head = NULL, *Tail = NULL;
    size_t _size = 0;
};