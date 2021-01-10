//Rehan Javaid, rj3dxu, 11/11/2020, huffmanenc.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include "heap.h"

using namespace std;


vector<string> prefixCodes; 

  int checkContainer(vector<huffman_node*> v1, char g) {
     for (int i = 0; i < v1.size(); i++){
       if (v1[i]->c == g){
	 return i;
       } 
     }
     return -1;
  }

map<char, string> prefixCodeMap;

void determine_prefix_codes(huffman_node* node, string path_taken){
  if(node->right == NULL || node->left == NULL){
    prefixCodeMap[node->c] = path_taken; 
  }
  else {
    determine_prefix_codes(node->right, path_taken+"1");
    determine_prefix_codes(node->left, path_taken+"0");
  }
}

// we want to use parameters
int main(int argc, char** argv) {

  //create array to hold frequency of each char
  int freq[256];
  for (int i = 0; i <= 255; i++){
    freq[i] = 0;
  }

    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    ifstream file(argv[1]);
    
    if (!file.is_open()) {
        cout << "Unable to open '" << argv[1] << "' for reading" << endl;
        exit(2);
    }
    
    // read in characters one by one, until reading fails (we hit the end of the file)
    char g;
    vector<huffman_node*> v1;
    
    while (file.get(g)) {
      if ((g < ' ') || (g > '~')){
	continue;
      }
      freq[g]++;
      huffman_node* huffPtr= new huffman_node;
      huffPtr -> c = g;
      huffPtr -> frequency = freq[g];
      if (v1.size() == 0){
	v1.push_back(huffPtr);
      }
      if (checkContainer(v1,g) != -1){
	v1[checkContainer(v1,g)]->frequency = freq[g];
      }
      if (checkContainer(v1,g) == -1){
	v1.push_back(huffPtr);
      }  
    }

    binary_heap b1(v1);

    while (b1.size() > 1){
      huffman_node* leftNode = b1.deleteMin();
      huffman_node* rightNode = b1.deleteMin();
      huffman_node* newNode = new huffman_node;
      newNode -> left = leftNode;
      newNode -> right = rightNode;
      newNode -> frequency = (leftNode->frequency) + (rightNode->frequency);
      b1.insert(newNode);
    }

    file.clear(); // Clears the _state_ of the file, not its contents!
    file.seekg(0);
    
    determine_prefix_codes(b1.findMin(), "");

    for (int i = 0; i < v1.size(); i++){
      if (v1[i]->c == ' '){
	cout << "space " << prefixCodeMap.at(v1[i]-> c) << endl;
      }
      else{
	cout << v1[i]->c << " " << prefixCodeMap.at(v1[i] -> c) << endl;
      }
    }

    cout << "----------------------------------------" << endl;


    
    while (file.get(g)) {
      if ((g < ' ') || (g > '~')){
	continue;
      }
      cout << prefixCodeMap.at(g)  << " ";
    }


    file.close();


    
    int numBits = 0;
    for (int i = 0; i < v1.size(); i++){
      numBits += v1[i]->frequency*(prefixCodeMap.at(v1[i]->c).length());
    }


    float cost = 0.0;
    for (int i = 0; i < v1.size(); i++){
      float divide = ((float)freq[v1[i]->c])/(b1.findMin()->frequency);
      float value = divide * (prefixCodeMap.at(v1[i]->c).length());
      cost += value; 
    }
    cout << endl; 

    cout << "----------------------------------------" << endl;

    cout << "There are a total of " << b1.findMin() -> frequency << " symbols that are encoded." << endl;
    cout << "There are " << v1.size() << " distinct symbols used." << endl; 
    cout << "There were " << 8*(b1.findMin() -> frequency) << " bits in the original file" << endl;
    cout << "There were " << numBits << " in the compressed file." << endl;
    cout << "This gives a compression ratio of " << (float) (8*(b1.findMin() -> frequency))/ numBits << "." << endl;
    cout << "The cost of the Huffman tree is " << cost << " bits per character." << endl; 
    
}
