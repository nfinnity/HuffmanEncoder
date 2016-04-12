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
    for (int i = 1; i < argc; i++)
    {
	    char ch;
	    bool isCode;
	    int index = 0;
	    int stopValue = 0;
	    string stringInput = "";
	    int code;
	    int location;
	    int asciiVal;
	    char character;
	    int stopper = 0;
	    int oneTime = 0;
	    string inputName = argv[i];
	if(inputName.find(".zip") != -1)
	{
    	ifstream infile(argv[i]);
    	string outfileName = "" + (string) argv[i];
    	outfileName = outfileName.substr(0, outfileName.length()-4);
	    ofstream outfile(outfileName.c_str());


		//If there is a character present in the file.
		if(infile.is_open())
		{
			infile.get(ch);
			//Keeps grabbing characters until a new line is found.
			//This value is the number of categories there are (letters).
			//This tells the program how many time it must run through the
			//following to grab the ASCII value and the corresponding code segment.
			while((int)ch != 10)
			{
				stringInput += ch;
				infile.get(ch);
			}
			//Converted to int and used as a the stopping index;
			stopValue = atoi(stringInput.c_str());
			stringInput = "";
			while (infile)
			{
				//Runs through this piece to grab all ASCII and corresponding code values
				if (index < stopValue)
				{
					infile.get(ch);
					//Stops when a space is reached (based on file formattting)
					while (isdigit(ch))
					{
						stringInput += ch;
						infile.get(ch);
					}
					//String is converted to an integer that represents the ASCII value
					asciiVal = atoi(stringInput.c_str());
					//Converts the ASCII value to a character
					character = asciiVal;
					//Adds the character to the character vector
					characters.push_back(character);
					stringInput = "";
					infile.get(ch);
					//Stops when a new line is reached (based on file formatting)
					while (isdigit(ch) && ((int)ch != 10))
					{
						stringInput += ch;
						infile.get(ch);
					}
					//Pushes the corresponding code onto the code vector.
					codes.push_back(stringInput);
					stringInput = "";
					index++;
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
						//Keeps running until a corresponding code value is found
						//and sets the location of where that corresponding value occurs
						while(isCode == false)
						{
							stringInput += ch;
							for (int i = 0; (i < codes.size()) && (isCode == false); i++)
							{
								if (stringInput == codes.at(i))
								{
									location = i;
									isCode = true;
								}
							}
							infile.get(ch);	
						}
					}
					
					//If a match was found, then grab the character and send it to the output file.
					if(location != -1)
					{
						character = characters.at(location);
						outfile << character;
					}
					isCode = false;
					stringInput = "";
					location = -1;
				}
			}	
				cout << endl;
				cout << "File \"" << (string) argv[i] << "\" Succesfully Inflated Back to Original" << endl;
				cout << endl;
				infile.close();	
			}
			else
			{
				cout << "The file \"" + (string) argv[i] + "\" is empty or cannot be found." << endl;
			}
		}
		else
		{
			cout << "The file \"" + (string) argv[i] + "\" is empty or cannot be found." << endl;
		}
	}
}