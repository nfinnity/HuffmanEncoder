#include "huffman.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;


HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;
    if (current_max < weight)
    	current_max = weight;
}

bool HuffmanTree:: inTree(char ch) {
	int i = 0;
	while(i <= nodes.size()-1)
	{
		if(nodes.at(i).ch == ch)
			return true;
		else
			i++;
	}
	return false;
}

int HuffmanTree:: GetFrequency(char ch) {
	int i = 0;
	while(i <= nodes.size()-1)
	{
		if(nodes.at(i).ch == ch)
			return nodes.at(i).weight;
		else
			i++;
	}
	return -1;
}

int HuffmanTree:: GetFrequency(int i) {

	if (i <= nodes.size()-1)
		return nodes.at(i).weight;
	else
		return -1;
}

int HuffmanTree:: lookUp(char ch) {
	int i = 0;
	while(i <= nodes.size()-1)
	{
		if (nodes.at(i).ch == ch)
			return i;
		else
			i++;
	}
	return -1;
}

int HuffmanTree:: lookUp(HNode *input) {
	int i = 0;
	while(i <= nodes.size()-1)
	{
		HNode *value = &(nodes.at(i));
		if (value == input)
			return i;
		else
			i++;
	}
	return -1;
}


string HuffmanTree:: GetCode(char ch) {
	int index = lookUp(ch);
	if(index != -1)
		return GetCode(index);
	else
		return ("Character is not included in this set.");

}


string HuffmanTree:: GetCode(int i) {
	if(nodes.at(i).parent == -1)
		return "";
	else
		return (GetCode(nodes.at(i).parent) + (char)(nodes.at(i).childType + '0'));
}

void HuffmanTree:: PrintTable() {
	int i = 0;
	int treeNum = 1;
	printf("%23s %26s %21s", "", "++++  ENCODING TABLE  ++++", "" );
	cout << endl;
	printf("%21s %16s %16s %16s ", "Character", "Weight", "Parent", "Child Type");
	cout << endl;
	while (i < nodes.size())
	{
		if (nodes.at(i).ch == '\0')
		{
			stringstream treeNumber;
			treeNumber << 'T' << treeNum;
			string name = treeNumber.str();
			printf("%5u %12s %16d %17d %14d", i, name.c_str(), nodes.at(i).weight, nodes.at(i).parent, nodes.at(i).childType);
			cout << endl;
			i++;
			treeNum++;
		}
		else
		{
			if (nodes.at(i).ch == 10)
				printf("%5u %12s %16d %17d %14d", i, "nl", nodes.at(i).weight, nodes.at(i).parent, nodes.at(i).childType);
			else if(nodes.at(i).ch == 32)
				printf("%5u %12s %16d %17d %14d", i, "sp", nodes.at(i).weight, nodes.at(i).parent, nodes.at(i).childType);
			else
				printf("%5u %12c %16d %17d %14d", i, nodes.at(i).ch, nodes.at(i).weight, nodes.at(i).parent, nodes.at(i).childType);
			cout << endl;
			i++;

		}
	}
}


int HuffmanTree:: numNodes() {
	return nodes.size();
}


void HuffmanTree:: build() {
	//Copy main vector
	int totalFrequency = 0;
	int treeNum = 1;

	//Count total frequency of all characters in file
	for (int i = 0; i <= nodes.size() - 1; i++)
		totalFrequency += nodes.at(i).weight;

	//Repeat until last entry's weight equals the total frequency (last node has been made).
	while (nodes.at(nodes.size()-1).weight != totalFrequency)
	{
		mergeNodes();
		treeNum++;
	}
}

void HuffmanTree:: mergeNodes()
{
	char name = '\0';
	//Find first smallest
	int i, j = 0;
	int index1, index2;
	int currentWeight = current_max;
	for (i = 0; i <= nodes.size() - 1; i++)
	{
		if ((nodes.at(i).weight < currentWeight) && (nodes.at(i).parent == -1))
		{
			index1 = i;
			currentWeight = nodes.at(i).weight;
		}
	}

	currentWeight = current_max;
	for (j = 0; j <= nodes.size() - 1; j++)
	{
		if ((nodes.at(j).weight < currentWeight) && (nodes.at(j).parent == -1) && (j != index1))
		{
			index2 = j;
			currentWeight = nodes.at(j).weight;
		}
	}

	int newNodeWeight = nodes.at(index1).weight + nodes.at(index2).weight;
	insert('\0', newNodeWeight);
	if (lookUp(&(nodes.at(index1))) < lookUp(&(nodes.at(index2))))
	{
		nodes.at(index1).childType = 1;
		nodes.at(index2).childType = 0;
	}
	else
	{
		nodes.at(index1).childType = 0;
		nodes.at(index2).childType = 1;
	}
	nodes.at(index1).parent = nodes.size()-1;
	nodes.at(index2).parent = nodes.size()-1;
}






