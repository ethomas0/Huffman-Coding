// HuffmanCoding.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

int main()
{

	
	
	/*Test 1*/
	HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");
	cout << tree.getCode('H');
	tree.printTree();
	/*tree.printCodes();*/
	cout << "Code L :" <<tree.getCode('L') << endl;
	
	//Test 2
	std::ifstream bigtext("Bigo.txt");
	std::string big((std::istreambuf_iterator<char>(bigtext)), std::istreambuf_iterator<char>());
	HuffmanTree bill(big);
	bill.printCodes();
	vector<char> encoded55 = bill.encode(big);
	bill.printBinary(encoded55);
	cout << endl;
	cout << bill.decode(encoded55) << endl;



	HuffmanTree tree("the brown dog jumps over the lazy fox");
	tree.printCodes();
	vector<char> encoded = tree.encode("the brown dog jumps over the lazy fox");
	tree.printBinary(encoded);
	cout << endl;
	cout << tree.decode(encoded) << endl;
	tree.printCodes();
	system("pause");

	/*test 2*/
	std::ifstream frequencyStream("Bigo.txt");
	HuffmanTree tree2(frequencyStream);
	/*tree2.printTree();
	tree2.printCodes();
*/
	tree2.compressFile("BigO.bin", "Bigo.txt");
	 tree2.printCodes();
	tree2.uncompressFile("BigO.bin", "BigORebuilt.txt");
	tree2.printTree();
	tree2.printCodes();*/

	Test 3
	std::ifstream frequencyStream("20000leagues.txt");
	HuffmanTree tree2(frequencyStream);
	tree2.printTree();
	tree2.printCodes();
	cout << "Code L :" << tree2.getCode('L') << endl;
	tree2.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
	tree2.uncompressFile("20000leaguesComp.bin", "20000leaguesRebuilt.txt");
	tree2.printTree();
	tree2.printCodes();

	// Try Other Files
	
	// read in text file create string - might be useful
	/*std::ifstream bigtext("20000leagues.txt");
	std::string big((std::istreambuf_iterator<char>(bigtext)), std::istreambuf_iterator<char>());
*/



	cout << endl;
	system("pause");
    return 0;
}

