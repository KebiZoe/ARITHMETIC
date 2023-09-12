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
#include "RBT.hpp"
#include <set>
#include <map>
#include "Heap.hpp"
#include "Union.hpp"
#include <assert.h>
#include "Graph.hpp"
using namespace std;

void test();
void testsort();
string daletou();
struct Person{
    string name;
    int age;
public:
    struct HashFunction{
        size_t operator()(const Person &p)const{
            size_t na = hash<string>{}(p.name);
            return na^hash<int>{}(p.age);
        }
    };
    Person(string n,int a):name(n),age(a){
        cout << "person create" << endl;
    }
    Person(const Person &p){
        this->name = p.name;
        this->age = p.age;
        cout << "person create" << endl;
    }
    ~Person(){}
    string toString(){
        return name + to_string(age);
    }
    friend ostream& operator<<(ostream &cout,Person);
};
void pri(Person &p){
    cout<<p.toString()<<endl;
}
template<>
struct hash<Person>{
    size_t operator()(const Person &p)const{
        return Person::HashFunction()(p);
    }
};
ostream& operator<<(ostream &cout,Person p){
    return cout << p.name << p.age; 
}
int main() {
//    unordered_map<int, Person> mp = unordered_map<int, Person>();
//    Person p = Person{"hh", 18};
//    mp.insert(tuple<int,Person>(1,p));
//    auto it = mp.begin();
//    cout << it->first <<endl;
//    cout << it->second <<endl;
//    pri(p);
//
//    string aa = "1234";
//    aa += "123";
    
//
    vector<int> _12_2 = {1,13,3,4,5,6,7,8,9,10,11,12};
    vector<Person*> pv = vector<Person*>();
    for (int i : _12_2) {
        pv.push_back(new Person(to_string(i),i));
    }
    cout<<_12_2.size()<<endl;
    cout<<_12_2.size()<<endl;
    {
        auto cmp = [](const Person &l,const Person &r)->bool{
            return l.age<=r.age;
        };
        Heap<Person *,decltype(cmp)> help(pv, cmp);
        
        cout<<_12_2.size()<<endl;
    }
    Union<int> *uf = new Union<int>();
    for (int i = 0; i < 12; i++) {
        uf->makeSet(i);
    }
//
//    uf->union_(0, 1);
//    uf->union_(0, 3);
//    uf->union_(0, 4);
//    uf->union_(2, 3);
//    uf->union_(2, 5);
//
//    uf->union_(6, 7);
//
//    uf->union_(8, 10);
//    uf->union_(9, 10);
//    uf->union_(9, 11);
//    assert(uf->isSame(2, 7) == false);
//    uf->union_(4, 6);
//    assert(uf->isSame(2, 7) == true);
//    cout<<"测试链表，栈，队列，avl树"<<endl;
//
////    test();
//    getchar();
////    cout<<"开始
//
//
//
//    return 0;
    
    int i = 1;
    string str;
    while (i<20230902) {
        str = daletou();
        i++;
    }
    cout << str << "- 恭喜中奖了" << endl;
    return 0;
}
string daletou(){
    vector<int> _35_5 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    vector<int> _12_2 = {1,2,3,4,5,6,7,8,9,10,11,12};
    
    vector<int> arr5 = {};
    
    while (arr5.size()<5) {
        int idx = arc4random()%(35-arr5.size());
        arr5.push_back(_35_5.at(idx));
        _35_5.erase(_35_5.begin()+idx);
    }
    
    std::sort(arr5.begin(), arr5.end(), [](int arg1,int arg2)->bool{
        return arg1<arg2;
    });
    string str = "";
    
    auto it1 = arr5.begin();
    while (it1!=arr5.end()) {
        str.append(std::to_string(*it1++));
    }
    
    vector<int> arr2 = {};
    
    while (arr2.size()<2) {
        int idx = arc4random()%(12-arr2.size());
        arr2.push_back(_12_2.at(idx));
        _12_2.erase(_12_2.begin()+idx);
    }
    
    std::sort(arr2.begin(), arr2.end(), [](int arg1,int arg2)->bool{
        return arg1<arg2;
    });
    auto it = arr2.begin();
    while (it!=arr2.end()) {
        str.append(std::to_string(*it++));
    }
    return str;
}
void test(){
    LinkedList<int>::test();
    Stack<int>::test();
    Queue<int>::test();
//    AVL<int>::test();
//    RBT<int>::test();
    
    // 测试红黑树的性能
    
    vector<int> intarr1 = zxx_util::getRandArr(sortCapacity, 0, 10000000);
    
    
    AVL<int> *avl;
    RBT<int> *rbt;
    auto mylamthread1 = [intarr1, &avl]{
        zxx_util::timeBlock("AVL树",[intarr1, &avl](){
            avl = new AVL<int>([](int a,int b)->int{
                return a-b;
            });
            for_each(intarr1.begin(), intarr1.end(), [=](int ar){
                avl->add(ar);
            });
        });
    };
    std::thread mytobj1(mylamthread1);
    mytobj1.detach();
    
    auto mylamthread2 = [intarr1, &rbt]{
        zxx_util::timeBlock("红黑树",[intarr1, &rbt](){
            rbt = new RBT<int>([](int a,int b)->int{
                return a-b;
            });
            for_each(intarr1.begin(), intarr1.end(), [=](int ar){
                rbt->add(ar);
            });
        });
    };
    std::thread mytobj2(mylamthread2);
    mytobj2.detach();
    
    getchar();
    
    auto mylamthread3 = [intarr1, &avl]{
        zxx_util::timeBlock("avl树移除",[intarr1, &avl](){
            for_each(intarr1.begin(), intarr1.end(), [=](int ar){
                avl->remove(ar);
            });
        });
    };
    std::thread mytobj3(mylamthread3);
    mytobj3.detach();
    auto mylamthread4 = [intarr1, &rbt]{
        zxx_util::timeBlock("红黑树移除",[intarr1, &rbt](){
            for_each(intarr1.begin(), intarr1.end(), [=](int ar){
                rbt->remove(ar);
            });
        });
    };
    std::thread mytobj4(mylamthread4);
    mytobj4.detach();
    getchar();
    getchar();
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



