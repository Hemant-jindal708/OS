#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <climits>

#define SIZE 10
using namespace std; // Using the standard namespace

vector<int> dataArray = {3, 7, 2, 9, 12, 5, 6, 8, 15, 4};

int sum = 0;
int maxVal = INT_MIN;
int minVal = INT_MAX;

mutex mtx;

void calculateSum(){
    int localSum=0;
    for(int i:dataArray){
        localSum+=i;
    }
    lock_guard<mutex>lock(mtx);
    sum=localSum;
}

void findMax(){
    int localMax = INT_MIN;
    for(int i:dataArray){
        if(i>localMax){
            localMax=i;
        }
    }
    lock_guard<mutex> lock(mtx);
    maxVal=localMax;
};

void findMin(){
    int localMin = INT_MAX;
    for(int val:dataArray){
        if(val<minVal){
            localMin=val;
        }
    }
    lock_guard<mutex>lock(mtx);
    minVal=localMin;
}

int main(){
    thread sumThread(calculateSum);
    thread maxThread(findMax);
    thread minThread(findMin);

    sumThread.join();
    maxThread.join();
    minThread.join();

    cout<<"sum is:"<<sum<<endl;
    cout<<"max is:"<<maxVal<<endl;
    cout<<"min is:"<<minVal<<endl;
}