#include <fstream>
#include <bitset>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

int main()
{
        fstream outfile("out.bin", ios::out | ios::binary);
        bitset<10> b;
	b.set(1);

        outfile.write ( (const char *) &b, sizeof (b) );
        outfile.close();

	bitset<10> c;
        fstream infile("out.bin", ios::in | ios::binary);

        infile.read( (char *) &c, sizeof (c) );

        cout << "Item Read In Was : " << c << endl;
	return 0;
}
