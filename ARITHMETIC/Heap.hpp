//
//  Heap.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2023/8/30.
//

#ifndef Heap_h
#define Heap_h

#import <vector>
#include <functional>
template <typename Type, typename Compare = std::less<Type>>
class Heap {
private:
    vector<Type> *vec;
    Compare compare;
public:
    
    Heap(const vector<Type> &vct, Compare &fun):compare(fun){
        vec = new vector<Type>(vct);
        for (int i = (int)(vec->size()>>1)-1; i>-1; i--) {
            siftDown(i);
        }
    }
    ~Heap(){
        delete vec;
    }
    int size(){
        return vec->size();
    }
    bool isEmpty(){
        return vec->size() == 0;
    }
    void clear(){
        vec->clear();
    }
    void add(Type e){
        vec->insert(vec->end(), e);
        siftUp(vec->size()-1);
        
    }
    Type get(){
        return vec->at(0);
    }
    Type remove(){
        Type t = vec->erase(vec->begin());
        
        siftDown(0);
        return t;
    }
    Type replace(Type e){
        Type t = vec->front();
        vec->at(0) = e;
        siftDown(0);
        return t;
    }
    void siftUp(int index){
        Type e = vec->at(index);
        while (index>0) {
            int pidx = (index-1)>>1;
            Type pe = vec->at(pidx);
            // 大的排前
            if (compare!=nullptr ? compare(pe, e):pe >= e) {
                break;
            }
            vec[index] = pe;
            index = pidx;
        }
        vec[index] = e;
    }
    
    void siftDown(int index){
        Type e = vec->at(index);
        int half = (int)vec->size()>>1;
        
        while (index<half) {
            int childIndex = (index << 1)+1;
            Type child = vec->at(childIndex);
            int rightChildIndex = childIndex+1;
            
            if (rightChildIndex < vec->size() && compare(*vec->at(rightChildIndex), *child)) {
                child = vec->at(rightChildIndex);
                childIndex = rightChildIndex;
            }
            if (compare(*e, *child)) {
                break;
            }
            vec->at(index) = child;
            index = childIndex;
        }
        vec->at(index) = e;
    }
};

#endif /* Heap_h */
