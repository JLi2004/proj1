#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "predictors.hpp"  
#include "tournament.hpp"
#include "btb.hpp"
using namespace std;

sbb** initalize_single_bit_obj(){
    sbb** taken_arr = new sbb*[8];
    for(int i = 0; i < 8; i++)
        taken_arr[i] = new sbb(16 << i);
  return taken_arr;
}
dbb** initalize_double_bit_obj(){
  dbb** taken_arr = new dbb*[8];
  for(int i = 0; i < 8; i++)
    taken_arr[i] = new dbb(16 << i);
  return taken_arr;
}
gshare** initalize_gshare_obj(){
  gshare** taken_arr = new gshare*[9];
  for(int i = 0; i < 9; i++)
    taken_arr[i] = new gshare(3 + i);

  return taken_arr;
}



int main(int argc, char *argv[]) {
  int single_actual[] = {1272056, 1271610, 0, 1635134, 1756616, 1999124, 1999353, 1999526};
  int double_actual[] = {1472734, 1475763, 0, 1800746, 1876864, 1999472, 1999581, 1999665};
  int gshare_actual[] = {1999630, 1939177, 1999563, 1999597, 1999592, 1999601, 1999579, 1999510, 1999561};
  sbb** singleBits = initalize_single_bit_obj();
  dbb** doubleBits_independent = initalize_double_bit_obj();
  gshare** gshare_independent = initalize_gshare_obj();
  tournament* tourny = new tournament();
  btb* target_buffer = new btb();
  // Temporary variables
  unsigned long long addr;
  string behavior, line;
  unsigned long long target;

  //ifstream infile("examples\\test_input.txt");
  //ifstream infile("C:\\Users\\hii\\Desktop\\proj1\\project1\\traces\\short_trace1.txt");
  if(argc < 3){
    perror("not enough args");
    return 1;
  }
  ifstream infile(argv[1]);

  int correct_T = 0;
  int correct_NT = 0;
  int total = 0;
  bool action;
  int i;
  while(getline(infile, line)) {
    // Now we have to parse the line into it's two pieces
    stringstream s(line);
    s >> std::hex >> addr >> behavior >> std::hex >> target;
    if(behavior == "T"){
      action = true;
      correct_T++;
    } 
    else if(behavior == "NT"){
      action = false;
      correct_NT++;
    }
    
    for(i = 0; i < 8; i++){
      singleBits[i]->eval(action, addr);
      doubleBits_independent[i]->eval(action, addr);
    }
    for(i = 0; i < 9; i++)
      gshare_independent[i]->eval(action, addr);
    tourny->eval(action, addr);
    target_buffer->eval(action, addr, target);
    total++;
  }
  ofstream outfile(argv[2]);

  
  outfile << correct_T << "," << total << ";" << endl << correct_NT << "," << total << ";" << endl;
  for(int i = 0; i < 8; i++){
    if(i == 2) continue;
    outfile << singleBits[i]->get_correct() << "," << total << ";";
    if(i != 7)
      outfile << " ";
    //cout << (singleBits[i]->get_correct() == single_actual[i]) << ", ";
  }
  outfile << endl;
  for(int i = 0; i < 8; i++){
    if(i == 2) continue;
    outfile << doubleBits_independent[i]->get_correct() << "," << total << ";";
    if(i != 7)
      outfile << " ";
    //cout << (doubleBits_independent[i]->get_correct() == double_actual[i]) << ", ";
  }
  outfile << endl;
  for(int i = 0; i < 9; i++){
    outfile << gshare_independent[i]->get_correct() << "," << total << ";";
    if(i != 8)
      outfile << " ";
    //cout << (gshare_independent[i]->get_correct() ==  gshare_actual[i]) << ", ";
  }
  
  outfile << endl << tourny->get_correct() << "," << total << ";" << endl;
  outfile << target_buffer->get_correct() << "," << target_buffer->get_attempted() << ";" << endl;
   
  return 0;
}
