//
//  util.cpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/4/12.
//

#import <iostream>
#import <stdio.h>
#import <vector>
#import <sys/time.h>
#import <string>
#import <functional>
#import <exception>
#import <typeinfo>
using namespace std;

class zxx_util{
public:
    static void printCurrentTime(){
        time_t timep=time(NULL);
        struct tm *p;
        p = localtime(&timep);
        printf("%d-%d-%d %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    }
    template<class T>
    static void timeBlock(std::string str, const T& func){
        struct timeval start, end;
        gettimeofday(&start,NULL);
        
        func();

        gettimeofday(&end,NULL);
        long usenc = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
        long senc = usenc/1000000;
        usenc = usenc%1000000;
        printf("%s耗时%ld:%ld\n", str.c_str(),senc,usenc);
    }
    
    template<class T>
    static std::vector<T> getRandArr(int capacity,T min,T max){
        std::vector<T> result = std::vector<T>();
        try {
            if (strcmp(typeid(T).name(), "f")==0||strcmp(typeid(T).name(), "d")==0) { // 浮点数默认保留两位小数
                for (int i = 0; i<capacity; i++) {
                    T tempV = arc4random()%((int)(max-min))+min-1+(arc4random()%100)*0.01;
                    result.push_back(tempV);
                }
            }else if(strcmp(typeid(T).name(), "c")==0){
                for (int i = 0; i<capacity; i++) {
                    T tempV = (char)(arc4random()%((int)max-(int)min)+int(min));
                    result.push_back(tempV);
                }
            }else if(strcmp(typeid(T).name(), "b")==0){
                for (int i = 0; i<capacity; i++) {
                    T tempV = ((arc4random()%10)>5) ? true : false;
                    result.push_back(tempV);
                }
            }else{
                for (int i = 0; i<capacity; i++) {
                    T tempV = arc4random()%((int)max-(int)min)+(int)min;
                    result.push_back(tempV);
                }
            }
        } catch (std::exception ex) {
            throw ex;
        }
        return result;
    }

    static std::vector<std::string> getRandStrArr(int capacity,int minlen,int maxlen){
        std::vector<std::string> result = std::vector<std::string>();
        for (int i = 0; i<capacity; i++) {
            int len = arc4random()%(maxlen-minlen)+minlen;
            std::string tempstr = std::string();
            for (int j = 0; j<len; j++) {
                char tempV = (char)(arc4random()%((int)'z'-(int)'a'+1))+(int)'a';
                tempstr.push_back(tempV);
            }
            result.push_back(tempstr);
        }
        return result;
    }
    
    // 大数加法
    string bigDatePlus(string &args, string &args2){
        string max, min;
        if (args.size()>args2.size()) {
            max = args;
            min = args2;
        }else{
            min = args;
            max = args2;
        }
        auto it = max.rbegin();
        auto it2 = min.rbegin();
        string res = "";
        int j = 0;
        while (it != max.rend()) {
            int a = *it - 48;
            it++;
            
            int b;
            if (it2!=min.rend()) {
                b = *it2 - 48;
                it2++;
            }else{
                b = 0;
            }
            
            int r = a+b+j;
            j = r/10;
            int g = r%10;
            res.insert(0, std::to_string(g));
        }
        if (j>0) {
            res.insert(0, std::to_string(j));
        }
        return res;
    }
    // 大数乘法
    string bigDateMultiply(string &args, string &args2){
        auto it = args.rbegin();
        // 保留上一轮的计算结果
        string pres = "";
        string bul = "";
        while (it != args.rend()) {
            int a = *it - 48;
            auto it2 = args2.rbegin();
            // 当前轮的计算结果
            string s = "";
            int j = 0;
            if (a!=0) {
                while (it2 != args2.rend()) {
                    int b = *it2 - 48;
                    int r = a*b+j;
                    int g = r%10;
                    s.insert(0, std::to_string(g));
                    j = r/10;
                    it2++;
                }
            }
            // s为一轮下来的结果需要参与下一轮的计算
            if (j>0) {
                s.insert(0, std::to_string(j));
            }
            s.append(bul);
            pres = bigDatePlus(pres, s);
            bul.push_back('0');
            
            it++;
        }
        return pres;
    }
    
    void bigDatatest(){
        std::string a = "1241354123414123";
        std::string b = "141234141142";
        std::cout << bigDateMultiply(a, b) << endl;
    }
    
    void test_getRandomArrs(){
        vector<double> rangarr = zxx_util::getRandArr(10000, 1.0, 10000.0);
        vector<char> rangarr1 = zxx_util::getRandArr(20, '0', 'z');
        vector<bool> rangarr2 = zxx_util::getRandArr(10, false, true);
        vector<string> rangarr3 = zxx_util::getRandStrArr(10, 2, 20);
    }
};

