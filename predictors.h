#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

class sbb{
    public:
        sbb(){
            data = new bool[1];
            correct = 0;
            mask = 0;
        }
        sbb(int tbl_size){
            data = new bool[tbl_size];
            for(int i = 0; i < tbl_size; i++)
                data[i] = 1;
            correct = 0;
            mask = tbl_size - 1;
        }
        ~sbb(){
            delete data;
        }
        bool eval(bool behavior, const unsigned long long& addr){
            int index = addr & mask;
            bool val = data[index];
            data[index] = behavior;
            correct +=  (val == behavior);
            return (val == behavior);
        }
        int get_correct(){
            return correct;
        }
    private:
        int correct;
        bool* data = 0;
        unsigned int mask;
};
class dbb{
        public:
        dbb(){
            correct = 0;
            data = new char[1];
            mask = 0;
        }
        dbb(int tbl_size){
            correct = 0;
            data = new char[tbl_size];
            for(int i = 0; i < tbl_size; i++)
                data[i] = 3;

            mask = tbl_size - 1;
        }
        ~dbb(){
            delete data;
        }
        bool eval(bool behavior, const unsigned long long& addr){
            int index = addr & mask;
            char val = data[index];
            if(val > 0 && behavior == false)
                data[index]--;
            else if(val < 3 && behavior == true)
                data[index]++;
            correct += (val >> 1) == behavior;
            return ((val >> 1) == behavior);
        }
        int get_correct(){
            return correct;
        }
    private:
        int correct = 0;
        char* data = 0;
        unsigned int mask;
};
class gshare{
    public:
        gshare(){
            correct = 0;
            data = new int[1];
            mask = 1;
        }
        gshare(int hist_size){
            data = new int[2049];
            for(int i = 0; i < 2048; i++)
                data[i] = 3;
            data[2048] = 0;
            mask = 0;
            for(int i = 0; i < hist_size; i++){
                mask = (mask << 1) + 1;
            }
            correct = 0;
        }
        ~gshare(){
            delete data;
        }
        bool eval(bool behavior, const unsigned long long& addr){
            int index = (addr & 2047) ^ (data[2048] & mask);
            char val = data[index];
            if(val > 0 && behavior == false)
                data[index]--;
            else if(val < 3 && behavior == true)
                data[index]++;
            data[2048] = behavior + (data[2048] << 1);
            correct += ((val >> 1) == behavior);
            return ((val >> 1) == behavior);
        }
        int get_correct(){
            return correct;
        }
    private:
        int correct = 0;
        int* data = 0;
        unsigned int mask;
};