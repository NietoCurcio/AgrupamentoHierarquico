#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string getTag(string row) {
    string tag = "";
    int i = 1;
    while(i < 5) {
        tag += row[i];
        i++;
    } 
    return tag;
}

void mutableTest(int n[]) {
  n[0] = 10;
}


int main (int argc, char *argv[]) {
  // for(int i = 0; i < argc; i++) {
  //   printf("%s\n", argv[i]);
  // }
  // ofstream MyWriteFile("filename.csv");
  // MyWriteFile << 0.0000000000002;
  // MyWriteFile.close();

  string myText;
  ifstream MyReadFile("teste.graphml");

  while (getline (MyReadFile, myText)) {
    string row = getTag(myText);
    cout << row << endl;
  }
  MyReadFile.close();

  int a[] = {1,2,3};
  mutableTest(a);
  for(int i = 0; i < 3; i++) {
    printf("%d ", a[i]);
  }
}
