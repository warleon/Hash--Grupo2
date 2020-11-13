#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
//#include <unordered_map>
#include <utility>
#include "hashchain.h"

#define unordered_map Hash

using namespace std;
using namespace std::chrono;

vector<pair<string, string>> loadCSV(string file);

int main(){
  vector<pair<string, string>> data = loadCSV("data_small.csv");
  unordered_map<string, string> map(10);//cambiar por el hash a implementar
  auto start = high_resolution_clock::now();  
  for (auto par : data)
    map.insert(par.first,par.second);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout <<map["ASMATH MOSAR"]<< endl;
  cout <<map["SCIBA JENNIFER"]<< endl;
  cout <<map["BASHUNGWA CHRISTINA"]<< endl;
  cout <<map["BRISKI JOANNA"]<< endl;
  //cout <<map[""]<< endl;
  //cout <<map[""]<< endl;
}

vector<pair<string, string>> loadCSV(string file)
{
  vector<pair<string, string>> data;
  fstream fin;
  fin.open(file, ios::in);
  vector<string> row;
  string line, word, temp;
  int i = 0;
  while (!fin.eof())
  {
    row.clear();
    getline(fin, line);
    if (i++ == 0)
      continue;
    stringstream s(line);
    while (getline(s, word, ';'))
    {
      row.push_back(word);
    }
    if (row.size() == 2)
      data.push_back({row[0], row[1]});
  }
  return data;
}
