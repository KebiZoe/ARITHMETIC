//
//  LinkedList.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/6/5.
//  单向链表

#ifndef LinkedList_hpp
#define LinkedList_hpp

#import <stdio.h>
#import <vector>

template <class Type>
struct ListNode {
public:
    ListNode<Type> *next;
    Type value;
    ListNode(Type arg): value(arg), next(NULL){
    };
    ~ListNode(){
    };
};

template <class Type>
class LinkedList {
private:
    ListNode<Type> *header;
    int lenth;
    ListNode<Type> *node(int index);
public:
    LinkedList(){
        header = new ListNode<Type>(NULL);
        lenth = 0;
    };
    LinkedList(std::vector<Type> *arr){
        header = new ListNode<Type>(NULL);
        ListNode<Type> *temp = header;
        for (int i = 0; i<arr->size(); i++) {
            ListNode<Type> *node = new ListNode<Type>(arr->at(i));
            temp->next = node;
            temp = node;
        }
        lenth = (int)arr->size();
    };
    ~LinkedList(){
        ListNode<Type> *temp = header->next;
        for (int i = 0; i<lenth; i++) {
            ListNode<Type> *node = temp->next;
            delete temp;
            temp = node;
        }
        delete header;
        lenth = 0;
    };
    Type pop_back(){
        ListNode<Type> *temp = fnode(lenth-1);
        Type retvalue = temp->next->value;
        delete (temp->next);
        temp->next = NULL;
        lenth--;
        return retvalue;
    };
    Type pop_front(){
        if (lenth==0) {
            throw std::logic_error("has empty");
        }
        ListNode<Type> *temp = header->next;
        Type retvalue = temp->value;
        header->next = temp->next;
        delete temp;
        lenth--;
        return retvalue;
    };
    bool insert(int index, Type value){
        ListNode<Type> *temp = fnode(index);
        ListNode<Type> *node = new ListNode<Type>(value);
        node->next = temp->next;
        temp->next = node;
        lenth++;
        return true;
    };
    bool erase(int index){
        ListNode<Type> *temp = fnode(index);
        ListNode<Type> *node = temp->next;
        if (node != NULL) {
            temp->next = node->next;
            delete node;
            lenth--;
        }else{
            throw std::out_of_range("超出范围");
        }
        return true;
    };
    ListNode<Type>* fnode(int index){
        if ((index>lenth||index<0)) {
            throw std::out_of_range("超出范围");
        }
        ListNode<Type> *temp = header;
        for (int i = 0; i<index; i++) {
            temp = temp->next;
        } // temp 为index节点的前驱节点
        return temp;
    }
    Type at(int index){
        return fnode(index+1)->value;
    };
    int size(){
        return lenth;
    };
    
    
    void static test(){
        std::vector<int> *rangarr3 = new std::vector<int>({1,2,3,4,5});
        LinkedList<int> *list = new LinkedList(rangarr3);
        assert(list->LinkedList<int>::pop_back()==5); //1,2,3,4
        list->LinkedList<int>::insert(2, 5); //1,5,
        assert(list->LinkedList<int>::at(2)==5);
        assert(list->LinkedList<int>::pop_front()==1);
        assert(list->LinkedList<int>::erase(3)==true);
        assert(list->LinkedList<int>::size()==3);
        delete list;
    }
};




#endif /* Li*nkedList_hpp */
