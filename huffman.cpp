#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class Node {
	public:
		char character;
		int frequency;
		Node* left;
		Node* right;
		static Node* makeNode(Node* left, Node* right, char character, int frequency);
};

// remove function because already implement in the class
// creating new tree nodes
Node* Node::makeNode(Node* left, Node* right, char character, int frequency) {
	Node* node = new Node();
	node->character = character;
	node->frequency = frequency;
	node->left = left;
	node->right = right;

	return node;
}

// create minimum STL priority queue of node structure type
// structure will be used in ordering the heap
struct compare {  
	bool operator()(Node* l, Node* r) {
		return l->frequency > r->frequency;
	}
};

// ----- ENCODING STEP -----
// traverse tree and encode the characters
// store respective Huffman codes in a map
void encode(Node* root, string encodedString, unordered_map<char, string>& huffmanTree) {
	// return when pointer reaches beyond terminal leaf
	if (root == nullptr) return;

	// assign coding to character in map once pointer reaches terminal leaf
	if (!(root->left || root->right)) {
		huffmanTree[root->character] = encodedString;
	}

	// left branch is labelled as 0
	// right branch is labelled as 1
	encode(root->left, encodedString + "0", huffmanTree);
	encode(root->right, encodedString + "1", huffmanTree);
}

// ----- DECODING STEP -----
void decode(Node* root, string encodedString, int& index) {
	// return when pointer reaches beyond terminal leaf
	if (root == nullptr) return;

	// if pointer reaches terminal node, print character and return
	if (!(root->left || root->right)) {
		cout << root->character;
		return;
	}

	index++;

	// if 0 is encountered in traversal, decode along left branches
	if (encodedString[index] == '0')
		decode (root->left, encodedString, index);
	else	// decode along right branches
		decode (root->right, encodedString, index);
}

// ----- TREE GENERATION -----
// function to generate Huffman Tree
void generateTree(string inputText) {
	// create map to store frequency of each character
	unordered_map <char, int> frequencyMap;
	for (char character : inputText) {
		frequencyMap[character]++;
	}

	// create priority queue using the compare struct
	// this priority queue will keep track of active nodes
	priority_queue<Node*, vector<Node*>, compare> activeNodes;

	// generate a leaf node for each character
	// push this node to the active nodes queue
	for (auto pair : frequencyMap) {
		activeNodes.push(Node::makeNode(nullptr, nullptr, pair.first, pair.second));
	}

	// generate Huffman tree using active nodes
	// loop through all nodes until they all connect to form a tree
	// in that case the size of activeNodes will become 1
	while (!(activeNodes.size() == 1)) {
		// join the two least occuring characters to a common node
		Node* left = activeNodes.top();
		activeNodes.pop();
		Node* right = activeNodes.top();
		activeNodes.pop();

		// make the common node frequency as sum of their frequencies
		int frequencySum = left->frequency + right->frequency;

		// push the common node back to active nodes
		activeNodes.push(Node::makeNode(left, right, '\0', frequencySum));
	}

	// the root will store pointer to top of tree 
	Node* root = activeNodes.top();

	// traverse the tree and encode the text
	// store the character and encoded text pair in map
	unordered_map <char, string> encodedMap;
	encode(root, "", encodedMap);

	// print compressed string
	string compressedText = "";
	for (char character : inputText) {
		compressedText += encodedMap[character];
	}
	cout << "\nThe encoded text is:\n" << compressedText << endl;

	// show users the encoding used
	cout << "\nThe following encoding was used during compression:\n";
	for (auto pair : encodedMap) {
		cout << pair.first << "\t:\t" << pair.second << endl;
	}

	// decode the compressed string
	// display the decoded string to the user
	cout << "\nThe decompressed text is:\n";
	int index = -1;
	int compressedLength = compressedText.size();
	while (index < compressedLength - 2) {
		decode(root, compressedText, index);
	}

	// try creating compressed file
	try {
		// create empty file in same directory as the code
		ofstream compressedFile;
		compressedFile.open ("compressed.txt");

		//check if file was successfully opened for writing
		if (compressedFile.is_open()) {
			compressedFile << compressedText;
			compressedFile.close();
			cout << "\n\nYour file was successfully compressed!";
		}
		else cout << "Unable to create compressed file";
	}
	catch (const char* message) {
		cerr << message << endl;
	}

	// show % space saved by the user
	int originalLength = inputText.size();
	originalLength *= (8.0);
	// int encodedSize = encodedMap.size();
	float result = ((float)compressedLength / originalLength);
	cout << "\n\nOriginal Size: " << originalLength << " bits" << endl;
	cout << "Compressed Size: " << compressedLength << " bits"<< endl;
	// float savedSpace = (float)((originalLength - encodedSize) * 100) / originalLength;
	float savedSpace = result;
	cout << "\nYou saved " << (1 - savedSpace) * 100.00 << "%" << " space.";
}

int main() {
	fstream userFile;
	string userData;

	// open user file for READ operation
	// the program assumes file is store in same directory as itself
	userFile.open("data.txt",ios::in);

	// terminate program with error if file not found/opened
	if (!userFile) {
        cout << "Unable to open user file";
        exit(1);
    }

	cout << "The data read from file is:" << endl;
	if (userFile.is_open()) {
		while(getline(userFile, userData)) {
			cout << userData << "\n"; //print the data of the string
		}
		userFile.close(); //close the file object.
	}
	generateTree(userData);
	return 0;
}