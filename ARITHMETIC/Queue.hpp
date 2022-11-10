//
//  Queue.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/6/7.
//

#ifndef Queue_hpp
#define Queue_hpp

#import <stdio.h>
#import "Stack.hpp"

template <class Type>
class Queue{
private:
    Stack<Type> *inStack;
    Stack<Type> *outStack;
public:
    Queue<Type>(){
        inStack = new Stack<Type>();
        outStack = new Stack<Type>();
    };
    ~Queue<Type>(){
        delete inStack;
        delete outStack;
    };
    int size(){
        return inStack->size()+outStack->size();
    };
    bool isEmpty(){
        return inStack->size()+outStack->size()==0;
    };
    void enQueue(Type value){
        inStack->push(value);
    };
    Type deQueue(){
        if (outStack->size()==0) {
            while (inStack->size()>0) {
                outStack->push(inStack->pop());
            }
        }
        return outStack->pop();
    };
    Type front(){
        if (outStack->size()==0) {
            while (inStack->size()>0) {
                outStack->push(inStack->pop());
            }
        }
        return outStack->top();
    };
    static void test(){
        Queue<int> *q = new Queue<int>();
        q->enQueue(1);
        q->enQueue(2);
        q->enQueue(3);
        q->enQueue(4);
        q->enQueue(5);
        assert(q->front()==1);
        assert(q->deQueue()==1);
        assert(q->size()==4);
        assert(q->isEmpty() == false);
        delete q;
    }
};

#endif /* Queue_hpp */
