#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "serialize.cpp"

int main() {
  
  vector<int> vo, vi;
  vo.push_back(7);
  vo.push_back(11);
  cout << "vo[0]=" << vo[0] << ", vo[1]=" << vo[1] << endl;
  
  ofstream binof("out.bin", ios::binary);
    write_container(vo, binof);
  binof.close();
  vo[0]=999, vo[1]=1023;
  vo.push_back(2022);
  cout << "vo.size()=" << vo.size() << " and vo[0]=" << vo[0] << ", vo[1]=" << vo[1] << endl;
  
  ifstream binif("out.bin", ios::binary);
    read_container(vi,binif);
  binif.close();
  cout << "after vo -> file -> vi, vi[0]=" << vi[0] << ", vi[1]=" << vi[1] << endl << endl;
  
  
  // serialize/deserialize in text mode
  cout << "Now test the text implementation stage by stage:" << endl;
  ofstream textof("out.txt");
  textof << 3 << ' ' << 5 << ' ';
  // Now serialize vector 'vo':
  textof << vo.size() << ' ';
  for(auto & i: vo) {
    textof << i << ' ';
  }
  textof.close();
  
  ifstream textif("out.txt");
  int i, j;
  textif >> i >> j;
  cout << "Testing deserializing numbers: i=" << i << " and j=" << j << endl;
  
  cout << "Testing deserializing a container of ";
  int n;
  textif >> n;
  cout                                           << n << " elements." << endl;
  for(int i = 0; i < n; i++)
  {
    textif >> vi[i];
    cout << "read value " << vi[i] << " into \'vi\'... ";
  }
  cout << endl;
  
  textif.close();
  
  cout << "Now output a multi-line string." << endl;
  string mls = "This is\nAfter all...\nA poem";
  serialize_simple(cout, mls);
  ofstream textof_str("out.txt");
    serialize_simple(textof_str, mls);
  textof_str.close();
  ifstream textif_str("out.txt");
    mls.clear();
    deserialize_simple(textif_str, mls);
  textif_str.close();
  cout << endl << "Now \'mls\\ holds \"" << mls << '\"' << endl;
  
  return 0;
};
