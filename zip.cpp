#include <sstream>
#include "huffman.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;


const int NumLetters = 256;
int set[NumLetters]; 
string setCodes[NumLetters];
int numberOfChars;
string buildData(HuffmanTree input);
string createTable();
vector<char> fileSequence;
double compressedSize;
double originalSize;
double ratio;

int main(int argc, char *argv[])
{
	cout << endl << endl;
    for (int i = 1; i < argc; i++)
    {
	    char ch;
    	ifstream infile(argv[i]);
    	string outfileName = "" + (string) argv[i] + ".zip";
	    ofstream outfile(outfileName.c_str());

	    //Initializes all character slots to 0 in array.
		for (char ch = char(0);  ch <= char(126);  ch++)
			set[ch] = 0;
		//Increments the slots of the characters that are encountered in the file.
		if(infile.good())
		{
			while (infile.get(ch))
			{
				fileSequence.push_back(ch);
				set[ch] += 1;
			}	

			//Declare tree
			HuffmanTree tree;
			//Insert nodes for each character (category) present in the file
			//into the Huffman tree.
			for (char ch = char(0); ch <= char(126); ch++)
			{
				if (set[ch] > 0)
				{
					tree.insert(ch, set[ch]);
					numberOfChars++;
				}
			}
			//Build tree
			tree.build();
			/*
			Obtains the codes for each of the characters and inserts them
			into the setCodes array.
			In the case of there being only one category, a value of zero
			is given as the code.
			*/
			for (char ch = char(0); ch <= char(126); ch++)
			{
				if (numberOfChars > 1)
				{
					if (set[ch] > 0)
						setCodes[ch] = tree.GetCode(ch);
				}
				else
				{
					if (set[ch] > 0)
						setCodes[ch] = "0";
				}	
			}

			cout << "PRINTING TABLE FOR FILE: " << "\"" << (string) argv[i] << "\"" << endl << endl;
			tree.PrintTable();

			/*
			Goes through each character and calculates the compressed size
			for each and adds it to the compressedSize variable.
			*/
			for (char ch = char(0); ch <= char(126); ch++)
			{
				if (set[ch] > 0)
				{
					compressedSize += set[ch]*setCodes[ch].length();
				}
			}
			originalSize = fileSequence.size()*8;
			ratio = 1 - ((compressedSize)/(originalSize));

			cout << "Compressed size: " << compressedSize << " bits    Original size: " << originalSize << " bits" << endl;
			printf("File successfully compressed to %.0f bits (%0.2f%% Less)", compressedSize, ratio);
			cout << endl << endl << endl;

			/*
			Creates strings for the ASCII value and codes, as well as the code sequence.
			Both strings are added and sent to the output file.
			*/
			string tableData = buildData(tree);
			string compressedInfo = createTable();
			string finalOutput = tableData + compressedInfo;
			outfile << finalOutput;
			cout << endl;
			/*
			All variables are intialized back to 0 and emptied.
			*/
			fileSequence.erase(fileSequence.begin(), fileSequence.end());
			numberOfChars = 0;
			compressedSize = 0;
			originalSize = 0;
			ratio = 0;
			for (char ch = char(0); ch <= char(126); ch++)
			{
				set[ch] = 0;
				setCodes[ch] = "0";
			}
			infile.close();	
		}
		else
		{
			cout << endl << "The file \"" + (string) argv[i] + "\" is empty or cannot be found." << endl << endl;
		}
    }
}

/*
Creates the string for the ASCII value and corresponding code.
*/
string buildData(HuffmanTree input)
{
	stringstream stream;
	stream << numberOfChars;
	string character = stream.str();
	string output = "" + character + "\n";

	for (char ch = char(0); ch <= char(126); ch++)
		{
			if (set[ch] > 0)
			{
				stream.str("");
				stream << (int)ch;
				string name = stream.str();
				output +=  name + " " + setCodes[ch] + "\n";
			}
		}
		return output;
}

/*
Creates the string for the code segment for the input.
*/
string createTable()
{
	string output;
	int i = 0;
	while (i < fileSequence.size())
	{
		char ch = fileSequence.at(i);
		output += setCodes[ch];
		i++;
	}
	return output;
}