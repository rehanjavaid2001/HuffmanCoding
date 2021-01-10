//Rehan Javaid, rj3dxu, 11/11/20, huffmandec.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "huffmanenc.h"
using namespace std;

   void build_huff_tree(huffman_node *node, string letter, string prefix_code){
      if (prefix_code == ""){
	node->c = letter.at(0);
	return;
      }
      char char_one = prefix_code.at(0); 
      if (char_one == '0'){
	if(node -> left == nullptr){
	  node->left = new huffman_node;
	  node->left->right = NULL;
	  node->left->left = NULL;
	}
	build_huff_tree(node->left, letter, prefix_code = prefix_code.erase(0,1));
      }
      else{
	if (node -> right  == nullptr){
	  node->right = new huffman_node;
	  node->right->right = NULL;
	  node->right->left = NULL; 
	} 
	build_huff_tree(node->right, letter, prefix_code = prefix_code.erase(0,1));
      }
   }
// main(): we want to use parameters
int main (int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    // must be opened in binary mode as otherwise trailing whitespace is discarded
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }

    huffman_node* root = new huffman_node;
    root->left = NULL;
    root->right = NULL; 

    // read in the first section of the file: the prefix codes
    while (true) {
        string character, prefix;
        // read in the first token on the line
        file >> character;

        // did we hit the separator?
        if (character[0] == '-' && character.length() > 1) {
            break;
        }

        // check for space
        if (character == "space") {
            character = " ";
        }

        // read in the prefix code
        file >> prefix;
        // do something with the prefix code

	build_huff_tree(root, character, prefix); 
    }

    // read in the second section of the file: the encoded message
    stringstream sstm;
    while (true) {
        string bits;
        // read in the next set of 1's and 0's
        file >> bits;
        // check for the separator
        if (bits[0] == '-') {
            break;
        }
        // add it to the stringstream
        sstm << bits;
    }

    string allbits = sstm.str();
    // at this point, all the bits are in the 'allbits' string
 
    huffman_node* h1 = root;
    for(int i = 0; i < allbits.length(); i++){
      if (allbits.at(i) == '0'){
        h1 = h1->left; 
	if (h1->left == nullptr){
	  cout << h1->c;
	  h1 = root;
	} 
      }
      else if (allbits.at(i) == '1'){
        h1 = h1->right;
	if (h1->right == nullptr){
	  cout << h1->c;
	  h1 = root;
	}
      } 
    }
    cout << endl;
    file.close();
}
