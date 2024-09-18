#include"Stack.h"
#include<iostream>

Stack::Stack(StackContainer container){
    if(container == StackContainer::Vector){
        _pimpl = new Vector;
    }else{
        _pimpl = new List;
    }
    _containerType = container;
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container){
    if(container == StackContainer::Vector){
        _pimpl = new Vector(valueArray, arraySize, 2.0f);
    }else{
        _pimpl = new List(valueArray, arraySize);
    }
    _containerType = container;
}
Stack::Stack(Stack&& moveStack) noexcept {
    _pimpl = moveStack._pimpl;
    _containerType = moveStack._containerType;
    moveStack._pimpl = nullptr;
}
Stack& Stack::operator=(Stack&& moveStack) noexcept {
    if (&moveStack != this){
        _pimpl = moveStack._pimpl;
        _containerType = moveStack._containerType;
         moveStack._pimpl = nullptr;
    }
    return *this;
};

Stack::Stack(const Stack& copyStack){
    StackContainer container = copyStack._containerType;
    if(copyStack.size() == 0 || copyStack._pimpl == nullptr){
        Stack(copyStack._containerType); 
    }

    else{
        if (container == StackContainer::Vector){
            _pimpl = new Vector(*dynamic_cast<Vector*>(copyStack._pimpl));
        }
        else if (container == StackContainer::List){
            _pimpl = new List(*dynamic_cast<List*>(copyStack._pimpl));
        }
    }
}

Stack& Stack::operator=(const Stack& copyStack){
    StackContainer container = copyStack._containerType;

    if (this != &copyStack){
        if(copyStack.size() == 0 || copyStack._pimpl == nullptr){
        Stack(copyStack._containerType);
    }
    else{
        ValueType * valueArray = copyStack._pimpl->getSequence();
        int Size = copyStack.size();
        delete _pimpl;
        if (container == StackContainer::Vector){
            _pimpl = new Vector(valueArray, Size);
        }
        else if (container= StackContainer::List){
            _pimpl = new List(valueArray, Size);
        }

        //delete[] valueArray;
        }
    }
    return *this;
} 


void Stack::push(const ValueType& value){
    _pimpl->push(value);
}

void Stack::pop(){
    _pimpl->pop();
}

const ValueType& Stack::top() const{
    return _pimpl->top();
}

bool Stack::isEmpty() const{
    return _pimpl->isEmpty();
}

size_t Stack::size() const{
    return _pimpl->size();
}

Stack::~Stack(){
    delete _pimpl;
}