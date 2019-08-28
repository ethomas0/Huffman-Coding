#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>    
#include <algorithm>
#include <iomanip> 
#include <bitset>
#include <map>
#include <sstream>
using namespace std;

inline bool HuffmanTree::getBit(unsigned char byte, int position) const
{

	return (byte  & BITMASK[position]);
}
// Usage
//mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const
{
	return  byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream & out) const
{
	for (size_t i = 0; i < sizeof(char) * 8; i++)
	{
		if (getBit(binary, i))
		{
			out << 1;
		}
		else
		{
			out << 0;
		}
	}
}
void HuffmanTree::printBinary(vector<char> bytes, std::ostream & out) const
{
	for (char byte : bytes)
	{
		printBits(byte, out);
		out << "-";
	}
}

string HuffmanTree::getCode(char letter) const
{
	string code = "";
	BinaryNode *curr = root;
	while (curr->left != nullptr && curr->right != nullptr)
	{
		if (curr->left != nullptr && curr->left->element.find(letter) != -1)//if element is not found continue down
		{
			curr = curr->left;
			code += "0";
		}
		else if (curr->right->element.find(letter) != -1)//  same as above but going right
		{
			curr = curr->right;
			code += "1";
		}
		else
		{
			return "Did not find";
		}
		
	}
	return code;	
}



void HuffmanTree::makeEmpty(BinaryNode * t)//uses recurssion to delete
{
	if (t == nullptr)
	{
		return;
	}
	
	makeEmpty(t->left);	
	makeEmpty(t->right);		
	delete t;


}



void HuffmanTree::printTree(BinaryNode *node, std::ostream & out) const//recurssion to print
{
	if (node == nullptr)
	{
		return;
	}
	printTree(node->left, out);
	out << node->element << " : " << node->frequency << endl;
	printTree(node->right, out);

}



void HuffmanTree::printCodes(BinaryNode *node, std::ostream & out, string code) const
{
	if (node != nullptr && node->left != nullptr)
	{
		printCodes(node->left, out, code + "0");
	}

	if (node != nullptr && node->right != nullptr)
	{
		printCodes(node->right, out, code + "1");
	}

	if (node != nullptr && node->right == nullptr && node->left == nullptr)
	{
		cout << node->element << " : " << code << endl;
	}
}

void HuffmanTree::saveTree(BinaryNode * current, map<int, string> &mapOfTree, int index)
{
	
}


void HuffmanTree::saveTree(std::ostream & compressedFileStream)
{
	
	
}

void HuffmanTree::rebuildTree(BinaryNode * node, int index, map<int, string> &mapOfTree)
{
	
		

}

void HuffmanTree::rebuildTree(ifstream & compressedFile)
{

	

}








HuffmanTree::BinaryNode * HuffmanTree::buildTree(string frequencyText)
{
	priority_queue<HuffmanTree::BinaryNode *, vector<HuffmanTree::BinaryNode *>, compareBinaryNodes > nodes;
	int frequencyStorage[256] = {0};
	
	for (int i = 0; i < frequencyText.length(); i++)
	{
		frequencyStorage[frequencyText[i]] ++;
	}
	
	for (int i = 0; i < 256; i++)
	{
		if (frequencyStorage[i] != 0)
		{	
			string convertChar; 
			convertChar.push_back((char)i); // converting char to string
			nodes.push(new BinaryNode(convertChar, frequencyStorage[i]));

		}

	}
	while (nodes.size() > 1)
	{
		BinaryNode *temp1 = nodes.top();
		nodes.pop();
		BinaryNode *temp2 = nodes.top();
		nodes.pop();
		BinaryNode *combined = new BinaryNode((temp1->element + temp2->element),(temp1->frequency + temp2->frequency));
		combined->left = temp1;
		combined->right = temp2;
		nodes.push(combined);
	}

	return nodes.top();

}



HuffmanTree::HuffmanTree(string frequencyText)
{

	root = buildTree(frequencyText);

}

HuffmanTree::HuffmanTree(ifstream & frequencyStream)
{

	
	std::string frequencyText((std::istreambuf_iterator<char>(frequencyStream)), std::istreambuf_iterator<char>());
	frequencyStream.close();
	if (frequencyText.size() > 0)
	{
		root = buildTree(frequencyText);
	}


}

HuffmanTree::~HuffmanTree()
{
	makeEmpty();
};
void HuffmanTree::printCodes(std::ostream & out) const
{
	printCodes(root, out, "");
}


void HuffmanTree::printTree(std::ostream & out) const
{
	printTree(root, out);
}

void HuffmanTree::makeEmpty()
{
	makeEmpty(root);
}
string HuffmanTree::decode(vector<char> encodedBytes)//decodes from right to left
{
	string decoded;
	BinaryNode *curr = root;
	for (int i = 0; i < encodedBytes.size(); i++)
	{
		
		for (int j = 7; totalBits != 0 && j >= 0  ; j--)// should use EOF if you can but I used created totalBits to do the same thing
		{
			if (getBit(encodedBytes[i], j))
			{
				
				curr = curr->right;
				--totalBits;

				
			}
			else
			{
							
					curr = curr->left;
					--totalBits;

					
				
			}
			if (curr->left == nullptr && curr->right == nullptr)
			{
				decoded += curr->element;
				curr = root;
			}
		}
				
	}
	
	return decoded;
}


vector<char> HuffmanTree::encode(string stringToEncode)// encodes from right to left
{

	buildTree(stringToEncode);
	vector<char> encoded;

	char store = 0;
	int count = 7;
	//stringToEncode.push_back(EOFCharacter);
	//stringToEncode.push_back(EOFCharacter);
	for (int i = 0; i < stringToEncode.size(); i++)
	{
		BinaryNode *curr = root;
		char letter = stringToEncode[i];
		

		while (curr->left != nullptr && curr->right != nullptr)
		{
			
			if (curr->left != nullptr && curr->left->element.find(letter) != string::npos)
			{
				
				curr = curr->left;				
				++totalBits;
				count -= 1;
				
			}
			else 
			{
				
				curr = curr->right;
				++totalBits;
				store = setBit(store, count);
				count -= 1;
				
			}
			if (count < 0) // resets everything if a char has a total of 8 bits
			{
				encoded.push_back(store);
				store = 0;
				count = 7;

			}


		}
		
		
	}
	if (count != 7) // pushes the rest onto the vector 
	{
		encoded.push_back(store);
	}
	return encoded;
}


void HuffmanTree::uncompressFile(string compressedFileName, string uncompressedToFileName)
{
	
	ifstream fin(compressedFileName,  ios::binary);
	if (fin.fail())
	{
		cout << "unable to open read file";
		return;
	}

	ostringstream ss; // this was copied from hints
	ss << fin.rdbuf();
	const string& s = ss.str();
	vector<char>encoded(s.begin(), s.end());
	
	fin.close();
	string decoded = decode(encoded);
	ofstream fout(uncompressedToFileName);
	if (fout.fail())
	{
		cout << "unable to open write file";
		return;
	}
	fout << decoded;
	fout.close();
	
}



void HuffmanTree::compressFile(string compressToFileName, string uncompressedFileName, bool buildNewTree)
{
	
	vector<char>encoded;
	ifstream fin(uncompressedFileName);
	
	if (fin.fail())
	{
		cout << "unable to open read file";
		return;
	}
	
	string big((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>()); // from hints to
	encoded = encode(big);
	fin.close();
	
	ofstream fout(compressToFileName, ios::out | ios::binary);
	if (fout.fail())
	{
		cout << "unable to open write file";
		return;
	}
	
	fout.write(reinterpret_cast<const char*>(&encoded[0]), encoded.size() * sizeof(char));// this to
	fout.close();

	

}


