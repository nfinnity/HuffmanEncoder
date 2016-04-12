#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

typedef char String[15];

int main()
{
        fstream outfile("out.bin", ios::out | ios::binary);
        int outNum = 250;

        outfile.write ( (const char *) &outNum, (int) sizeof (int) );

	String s = "turkey";
	outfile.write(s, sizeof(String));

	vector<bool> v(10);  v.push_back(true);
	outfile.write((const char *) &v, sizeof(v));

	bitset<50> b;
	outfile.write((const char *) &b, sizeof(b));

        outfile.close();

        int inNum;  String t;
        fstream infile("out.bin", ios::in | ios::binary);

        infile.read( (char *) &inNum, (int) sizeof (int) );

        cout << "Num Read In Was : " << inNum << endl;
	infile.read( t, sizeof(String));
	cout << "String read in was " << t << endl;
	return 0;
}
