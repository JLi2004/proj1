#include "predictors.h"
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
};
