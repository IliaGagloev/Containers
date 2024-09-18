#include"spisok.h"
#include<iostream>

List::List(const ValueType* values,size_t size){
    for(int i = 0;i < size;i++){
        push(values[i]);
    }
}

void List::push(const ValueType& value){
    node *temp = new node;
    temp->data = value;
    
    if(Tail != NULL){
        temp->prev= Tail;
        Tail->next = temp;
        Tail = temp;
    }else{
        temp->prev=NULL;
        Head=Tail=temp;
    }
    _size++;
}

void List::pop(){
    if(_size == 0)
        return;
    Tail = Tail->prev;
    _size--;
}
ValueType* List::getSequence() const{
    ValueType* NewData = new ValueType[_size];
    int i = 0;
    node *temp = Head;
    while(temp != NULL){
        NewData[i] = temp->data;
        temp = temp->next;
        i++;
    }    
    return NewData;
}
const ValueType& List::top() const{
    return Tail->data;
}

size_t List::size() const{
    return _size;
}

bool List::isEmpty() const{
    return _size == 0;
}