class btb{
    public:
        btb(){
            bimodal = new char[512];
            addrTable = new unsigned long long[512];
            correct = 0;
            attempted = 0;
            for(int i = 0; i < 512; i++){
                bimodal[i] = 3;
                addrTable[i] = 0;
            }
        }
        void eval(bool behavior, const unsigned long long& addr, const unsigned long long target){
            int index = addr & 511;
            char val = bimodal[index];
            if(val < 3 && behavior == true)
                bimodal[index]++;
            else if(val >0 && behavior == false)
                bimodal[index]--;
            if((val >> 1) == true){
                //predict stuff
                attempted++;
                if(addrTable[index] == target)
                    correct++;
                }
            if(behavior == true){
                addrTable[index] = target;
            }
        }

        int get_attempted(){
            return attempted;
        }
        int get_correct(){
            return correct;
        }
    private:
        int attempted = 0;
        int correct = 0;
        char* bimodal = 0;
        unsigned long long* addrTable = 0;
};  