//
//  main.cpp
//  ARITHMETIC
//
//  Created by zengdada on 2022/4/12.
//

#import <iostream>
#import <stdio.h>
#import "sort.hpp"
#import "util.hpp"
#import <thread>
#include <unistd.h>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "BST.hpp"
#include "AVL.hpp"
#include <set>
#include <map>
using namespace std;

void test();
void testsort();

int main() {
    
    
    
    
    
    
    
    
    
    cout<<"测试链表，栈，队列，avl树"<<endl;
    test();
    
    cout<<"开始测试排序"<<endl;
    testsort();
    
    
    return 0;
}

void test(){
    LinkedList<int>::test();
    Stack<int>::test();
    Queue<int>::test();
    AVL<int>::test();
}

void testsort() {
    vector<int> intarr1 = zxx_util::getRandArr(sortCapacity, 0, 10000000);
    
    vector<int> intarr2 = vector<int>(intarr1);
    vector<int> intarr3 = vector<int>(intarr1);
    vector<int> intarr4 = vector<int>(intarr1);
    vector<int> intarr5 = vector<int>(intarr1);
    vector<int> intarr6 = vector<int>(intarr1);
    vector<int> intarr7 = vector<int>(intarr1);
    vector<int> intarr8 = vector<int>(intarr1);
    vector<int> intarr9 = vector<int>(intarr1);
    vector<int> intarr10 = vector<int>(intarr1);
    vector<int> intarr11 = vector<int>(intarr1);
    
    auto mylamthread1 = [&intarr1]{
        zxx_util::timeBlock("堆排序",[&intarr1](){
            zxx_sort<int>::heapsort(intarr1);
        });
    };
    std::thread mytobj1(mylamthread1);
    mytobj1.detach();
    
    auto mylamthread2 = [&intarr2]{
        zxx_util::timeBlock("归并排序",[&intarr2](){
            zxx_sort<int>::mergesort(intarr2);
        });
    };
    std::thread mytobj2(mylamthread2);
    mytobj2.detach();
    
    auto mylamthread3 = [&intarr3]{
        zxx_util::timeBlock("快速排序",[&intarr3](){
            zxx_sort<int>::quiksort(intarr3);
        });
    };
    std::thread mytobj3(mylamthread3);
    mytobj3.detach();
    
    auto mylamthread4 = [&intarr4]{
        zxx_util::timeBlock("希尔排序",[&intarr4](){
            zxx_sort<int>::shellsort(intarr4);
        });
    };
    std::thread mytobj4(mylamthread4);
    mytobj4.detach();
    
    auto mylamthread5 = [&intarr5]{
        zxx_util::timeBlock("希尔排序2",[&intarr5](){
            zxx_sort<int>::shellsort2(intarr5);
        });
    };
    std::thread mytobj5(mylamthread5);
    mytobj5.detach();
    
//    auto mylamthread6 = [&intarr6]{
//        zxx_util::timeBlock("插入排序",[&intarr6](){
//            zxx_sort<int>::insertsort(intarr6);
//        });
//    };
//    std::thread mytobj6(mylamthread6);
//    mytobj6.detach();
//
//    auto mylamthread7 = [&intarr7]{
//        zxx_util::timeBlock("选择排序",[&intarr7](){
//            zxx_sort<int>::selectionsort(intarr7);
//        });
//    };
//    std::thread mytobj7(mylamthread7);
//    mytobj7.detach();
//
//    auto mylamthread8 = [&intarr8]{
//        zxx_util::timeBlock("冒泡排序",[&intarr8](){
//            zxx_sort<int>::bubblesort(intarr8);
//        });
//    };
//    std::thread mytobj8(mylamthread8);
//    mytobj8.detach();
    
    auto mylamthread9 = [&intarr9]{
        zxx_util::timeBlock("计数排序",[&intarr9](){
            zxx_sort<int>::countSort(intarr9);
        });
    };
    std::thread mytobj9(mylamthread9);
    mytobj9.detach();
    
    auto mylamthread10 = [&intarr10]{
        zxx_util::timeBlock("基数排序",[&intarr10](){
            zxx_sort<int>::radixSort(intarr10);
        });
    };
    std::thread mytobj10(mylamthread10);
    mytobj10.detach();
    
    auto mylamthread11 = [&intarr11]{
        zxx_util::timeBlock("基数排序2",[&intarr11](){
            zxx_sort<int>::radix2Sort(intarr11);
        });
    };
    std::thread mytobj11(mylamthread11);
    mytobj11.detach();
    
    getchar();
}



