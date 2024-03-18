#include "predictors.hpp"
class tournament{
    public:
        tournament(){
            correct = 0;
            selector_data = new char[2048];
            bimodal_predictor = new dbb(2048);
            gshare_predictor = new gshare(11);
        }
        void eval(bool behavior, const unsigned long long& addr){
            bool gshare_prediction = gshare_predictor->eval(behavior, addr);
            bool bimodal_prediction = bimodal_predictor->eval(behavior, addr);

            int index = addr & 2047;
            char selector_value = selector_data[index];
            int a = gshare_prediction - bimodal_prediction;
            if(a == 1 && selector_value < 3)
                selector_data[index]++;
            if(a == -1 && selector_value > 0)
                selector_data[index]--;
            if((selector_value >> 1) == 1)
                correct += gshare_prediction;
            else
                correct += bimodal_prediction;
        }
        int get_correct(){
            return correct;
        }
    private:
        int correct = 0;
        dbb* bimodal_predictor = 0;
        gshare* gshare_predictor = 0;
        char* selector_data = 0;
    
    
    
    
    
    /*
    public:
        tournament(){
            correct = 0;
            gshare_data = new unsigned char[2048];
            bimodal_data = new unsigned char[2048];
            selector_data = new unsigned char[2048];
            for(int i = 0; i < 2048; i++){
                gshare_data[i] = 3;
                bimodal_data[i] = 3;
                selector_data[i] = 0;
            }
            GHR = 0;
        }
        void eval(bool behavior, const unsigned long long& addr){
            int index = addr & 2047;
            int gindex = index ^ (GHR & 2047);
            char selector_val = selector_data[index];
            int mleh = ((int)((gshare_data[gindex] >> 1) == behavior)) - ((int)((bimodal_data[index] >> 1) == behavior));
        
            if(selector_val > 0 && mleh == -1)
                selector_data[index]--;
            else if(selector_val < 3 && mleh == 1)
                selector_data[index]++;

        
            GHR = (GHR << 1) + behavior;
            bool discrim = selector_val >> 1;
            
            char bval = bimodal_data[index];
            char gval = gshare_data[gindex];
            if(bval < 3 && behavior)
                bimodal_data[index]++;
            if(gval < 3 && behavior)
                gshare_data[gindex]++;

            if(bval > 0 && !behavior)
                bimodal_data[index]--;
            if(gval > 0 && !behavior)
                gshare_data[gindex]--;
            
            if(discrim)
                correct += (gval >> 1) == behavior;
            else   
                correct += (bval >> 1) == behavior;
            
        }

    private:
        int correct = 0;
        unsigned int GHR = 0;
        unsigned char* gshare_data = 0;
        unsigned char* bimodal_data = 0;
        unsigned char* selector_data = 0;*/
};