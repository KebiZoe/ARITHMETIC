//
//  sort.cpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/4/12.
//

#import <stdio.h>
#import <math.h>
#import <vector>
#import "util.hpp"
#import <thread>
using namespace::std;
template<class Type>
class zxx_sort{
public:
    // -----------------------------冒泡排序-----------------------------
    ///冒泡排序
    static void bubblesort(vector<Type> &arr){
        for (int end=(int)arr.size()-1; end>0; end--) {
            int sortedIndex = 0;
            for (int begin=1; begin<=end; begin++) {
                if (arr[begin-1]>arr[begin]) {
                    swap(arr[begin-1], arr[begin]);
                    sortedIndex = begin;
                }
            }
            if (sortedIndex==1) {
                break;
            }
        }
    }
    // -----------------------------选择排序-----------------------------
    ///选择排序
    static void selectionsort(vector<Type> &arr){
        for (int end=(int)arr.size()-1; end>0; end--) {
            int max = arr[0];
            int maxindex = 0;
            for (int begin=1; begin<=end; begin++) {
                if (arr[begin]>max) {
                    max = arr[begin];
                    maxindex = begin;
                }
            }
            swap(arr[maxindex], arr[end]);
        }
    }
    // -----------------------------堆排序-----------------------------
    static void siftDown(vector<Type> &arr, int index, int heapSize){
        Type element = arr[index];
        int half = heapSize >> 1;
        while (index < half) { //
            int childIndex = (index << 1)+1;
            Type child = arr[childIndex];
            int rightChildIndex = childIndex+1;
            if (rightChildIndex < heapSize && arr[rightChildIndex] > child) {
                child = arr[rightChildIndex];
                childIndex = rightChildIndex;
            }
            if (element >= child) {
                break;
            }
            arr[index] = child;
            index = childIndex;
        }
        arr[index] = element;
    }
    /// 堆排序
    static void heapsort(vector<Type> &arr){
        int heapsortsize = (int)arr.size();
        for (int i = (heapsortsize >> 1)-1; i>=0; i--) {
            siftDown(arr, i, heapsortsize);
        }
        
        while (heapsortsize>1) {
            swap(arr[0], arr[--heapsortsize]);
            siftDown(arr, 0, heapsortsize);
        }
    }
    // -----------------------------插入排序-----------------------------
    static int searchbinary(vector<Type> &arr, int dest){
        // 已知dest前面的数据都是有序的
        int begin = 0;
        int end = dest;
        
        while (begin < end) {
            int middle = (begin+end) >> 1;
            if (arr[dest] > arr[middle]) { //在下半截取
                begin = middle+1;
            }else{
                end = middle;
            }
        }
        return begin;
    }
    static void insert(vector<Type> &arr,int res, int dest){
        Type value = arr[res];
        for (int i = res; i > dest; i--) {
            arr[i] = arr[i-1];
        }
        arr[dest] = value;
    }
    ///插入排序
    static void insertsort(vector<Type> &arr){
        for (int i = 1; i < arr.size(); i++) {
            insert(arr, i, searchbinary(arr, i));
        }
    }
    // -----------------------------归并排序-----------------------------
    static void _merge(vector<Type> &arr, int begin, int mid, int end){
        vector<Type> temp = vector<Type>(mid-begin);
        for (int i = begin; i<mid; i++) {
            temp[i-begin] = arr[i];
        }
        int li = 0;
        int cursor = begin;
        int ri = mid;
        while (li < mid - begin) {
            if (ri < end && temp[li]>arr[ri]) { //右边小
                arr[cursor++] = arr[ri++];
            }else{
                arr[cursor++] = temp[li++];
            }
        }
    }
    
    static void _msort(vector<Type> &arr, int begin, int end){
        if (end-begin < 2) {
            return;
        }
        int mid = (begin+end) >> 1;
        _msort(arr, begin, mid);
        _msort(arr, mid, end);
        _merge(arr, begin, mid, end);
    }
    /// 归并排序
    static void mergesort(vector<Type> &arr){
        int begin = 0;
        int end = (int)arr.size();
        _msort(arr, begin, end);
    }
    
    // -----------------------------快速排序-----------------------------
    static int _pivotingpoint(vector<Type> &arr, int begin, int end){
        int pivotingindex = arc4random()%(end-begin)+begin;
        Type pivotingvalue = arr[pivotingindex];
        swap(arr[begin], arr[pivotingindex]);
        end--;
        while (begin<end) {
            while (begin<end) {
                if (arr[end]>pivotingvalue) {
                    end--;
                }else{
                    swap(arr[begin++], arr[end]);
                    break;;
                }
            }
            while (begin<end) {
                if (arr[begin]<pivotingvalue) {
                    begin++;
                }else{
                    swap(arr[begin], arr[end--]);
                    break;;
                }
            }
        }
        arr[begin] = pivotingvalue;
        return begin;
    }
    static void _quik(vector<Type> &arr, int begin, int end){
        if (end-begin<2) {
            return;
        }
        //找轴点
        int mid = _pivotingpoint(arr, begin, end);
        _quik(arr, begin, mid);
        _quik(arr, mid, end);
    }
    ///快速排序
    static void quiksort(vector<Type> &arr){
        _quik(arr, 0, (int)arr.size());
    }
    
    // -----------------------------希尔排序-----------------------------
    // 计算步长，遍历列，遍历步长间隔，对列排序
    static vector<int> _setSquence(long lenth){
        vector<int> re = vector<int>();
        while ((lenth>>=1)>0) {
            re.push_back((int)lenth);
        }
        return re;
    }
    static vector<int> _setSquence2(long lenth){
        vector<int> re = vector<int>();
        int k = 0, step = 0;
        while (true) {
            if (k%2==0) {
                int p = pow(2, k>>1);
                step = 1+9*(p*p-p);
            } else{
                int p1 = pow(2, (k-1)>>1);
                int p2 = pow(2, (k+1)>>1);
                step = 1+8*p1*p2-6*p2;
            }
            if (step>=lenth) {
                break;
            }
            re.insert(re.begin(), step);
            k++;
        }
        return re;
    }
    /// 希尔排序
    static void shellsort(vector<Type> &arr){
        //希尔本人使用的步
        vector<int> steps = _setSquence(arr.size());
        for (int i = 0; i < steps.size(); i++) {
            int step = steps[i];
            for (int col = 0; col < step; col++) {
                for (int begin = col+step; begin<arr.size(); begin+=step) {
                    int cur = begin;
                    while (cur > col && arr[cur]<arr[cur - step]) {
                        swap(arr[cur], arr[cur-step]);
                        cur -= step;
                    }
                }
            }
        }
    }
    /// 希尔排序升级步长
    static void shellsort2(vector<Type> &arr){
        //希尔本人使用的步
        vector<int> steps = _setSquence2(arr.size());
        for (int i = 0; i < steps.size(); i++) {
            int step = steps[i];
            for (int col = 0; col < step; col++) {
                for (int begin = col+step; begin<arr.size(); begin+=step) {
                    int cur = begin;
                    while (cur > col && arr[cur]<arr[cur - step]) {
                        swap(arr[cur], arr[cur-step]);
                        cur -= step;
                    }
                }
            }
        }
    }
    /// 计数排序，适合一定范围内的整数进行排序
    static void countSort(vector<int> &arr){
        int min = arr[0];
        int max = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i]>max) {
                max = arr[i];
            }
            if (arr[i]<min) {
                min = arr[i];
            }
        }
        int lenth = max - min + 1;
        int *count = new int[lenth]{0};
        for (int i = 0; i < arr.size(); i++){
            count[arr[i]-min]++;
        }
        for(int i = 1; i < lenth; i++){
            count[i] += count[i-1];
        }
        int *output = new int[arr.size()]{0};
        for(int i = int(arr.size()-1); i > -1; i--){
            output[--count[arr[i]-min]] = arr[i];
        }
        for(int i = 0; i < arr.size(); i++){
            arr[i] = output[i];
        }
    }
    /// 基数排序，适用于整数排序，尤其是非负整数
    /// 依次对个位数，十位数，百位数千位数，万位数...进行排序
    static void radixSort(vector<int> &arr){
        int max = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i]>max) {
                max = arr[i];
            }
        }
        int *output = new int[arr.size()]{0};
        for(int divider = 1; divider <= max; divider *= 10){
            int couts[10] = {0};
            countingSort(arr, divider, output, couts);
        }
    }
private: static void countingSort(vector<int> &arr, int divider, int *output, int *counts){
        for(int i=0;i<arr.size();i++){
            counts[arr[i]/divider%10]++;
        }
        for(int i=1;i<10;i++){
            counts[i] += counts[i-1];
        }
        for(int i = int(arr.size()-1); i > -1; i--){
            output[--counts[arr[i]/divider%10]] = arr[i];
        }
        for(int i = 0; i < arr.size(); i++){
            arr[i] = output[i];
        }
    }
    
};

