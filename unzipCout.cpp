#include <sstream>
#include "huffman.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;


vector<string> codes;
vector<char> characters;

int main(int argc, char *argv[])
{
	for (int i = 0; i < 1000; i++)
	{
		cout << "NEW PROGRAM RUN HERE!!!!!!!" << endl;
	}

    for (int i = 1; i < argc; i++)
    {
    	cout << "First for loop" << endl;
	    char ch;
	    bool isCode;
	    int index = 0;
	    int stopValue = 0;
	    string stringInput = "";
	    int code;
	    int location;
	    int asciiVal;
	    char character;
	    int oneTime = 0;
    	ifstream infile(argv[i]);
    	string outfileName = "" + (string) argv[i];
    	outfileName = outfileName.substr(0, outfileName.length()-4);
	    ofstream outfile(outfileName.c_str());


		//If there is a character present in the file.
		if(infile.good())
		{
			cout << "First if statement" << endl;
			infile.get(ch);
			while((int)ch != 10)
			{
				stringInput += ch;
				infile.get(ch);
			}
			stopValue = atoi(stringInput.c_str());
			stringInput = "";
			cout << "Stopping value: " << stopValue << endl;
			cout << "Before first while loop, character is: " << ch << endl;
			while (infile)
			{
				cout << "Index value: " << index << endl;
				cout << "First while loop" << endl;
				if (index < stopValue)
				{
					infile.get(ch);
					cout << "Beginning char: " << ch << endl;
					while (isdigit(ch))
					{
						stringInput += ch;
						cout << "First isdigit char: " << ch << endl;
						infile.get(ch);
						cout << "First isdigit loop" << endl;
					}
					asciiVal = atoi(stringInput.c_str());
					cout << "Int value for character: " << asciiVal << endl;
					character = asciiVal;
					characters.push_back(character);
					cout << "Value added to character vector: " << characters.back() << endl;
					cout << endl;
					stringInput = "";
					infile.get(ch);
					while (isdigit(ch) && ((int)ch != 10))
					{
						cout << "Second isdigit char: " << ch << endl;
						stringInput += ch;
						cout << "Current string input: " << stringInput << endl;
						infile.get(ch);
						cout << "Second isdigit loop" << endl;
					}
					codes.push_back(stringInput);
					cout << "Code value for character: " << codes.back() << endl;
					stringInput = "";
					index++;
					cout << endl << endl;

					cout << "Exits first part" << endl;
				}
				else
				{
					if (oneTime < 1)
					{
						infile.get(ch);
						oneTime++;
					}
					if (infile)
					{
						cout << "Reaches else statement" << endl;
						while(isCode == false)
						{
							cout << "In second while" << endl;
							cout << "Next char in second while: " << ch << endl;
							stringInput += ch;
							for (int i = 0; (i < codes.size()) && (isCode == false); i++)
							{
								cout << "In second for loop" << endl;
								if (stringInput == codes.at(i))
								{
									location = i;
									isCode = true;
								}
							}
							infile.get(ch);	
						}
					}
					
					cout << "Exits second part" << endl;
					if(location != -1)
					{
						character = characters.at(location);
						cout << "Value in string input: " << stringInput << endl;
						cout << "Character value of matching code: " << character << endl;
						outfile << character;
					}
					isCode = false;
					stringInput = "";
					location = -1;
					cout << endl;
				}

			cout << "Looping here 2" << endl;	
			}		
			cout << "Looping here 1" << endl;	
		}
		else
		{
			cout << "The file \"" + (string) argv[i] + "\" is empty or cannot be found." << endl;
			return 0;
		}
		infile.close();
	}
}