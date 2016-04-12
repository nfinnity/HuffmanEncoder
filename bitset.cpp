
#include <bitset>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	bitset<50>	flags1;
	bitset<500>	flags2;
	bitset<5000>	flags3;
	fstream outfile("out.bin", ios::out | ios::binary);
	cout << sizeof(bitset<50>) << " "
	     << sizeof(bitset<500>) << " "
             << sizeof(bitset<5000>) << endl;
	outfile.close();
	return 0;
}
