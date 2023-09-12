//
//  Stack.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/6/7.
//

#ifndef Stack_hpp
#define Stack_hpp

#import <stdio.h>
#import "LinkedList.hpp"

template <class Type>
class Stack{
private:
    LinkedList<Type> *list;
public:
    Stack(){
        list = new LinkedList<Type>();
    };
    ~Stack(){
        delete list;
    };
    int size(){
        return list->size();
    };
    bool isEmpty(){
        return list->size()==0;
    };
    void push(Type value){
        list->insert(0, value);
    };
    Type pop(){
        return list->pop_front();
    };
    Type top(){
        return list->at(0);
    };
    
    void static test(){
        Stack<int> *s = new Stack<int>();
        s->push(1);
        s->push(2);
        s->push(3);
        s->push(4);
        assert(s->size()==4);
        assert(s->top()==4);
        assert(s->pop()==4);
        assert(s->isEmpty()==false);
    }
};

#endif /* Stack_hpp */
