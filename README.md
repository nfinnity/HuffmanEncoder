# HuffmanEncoder

OOD


Variables used in huffman.cpp:

    vector<HNode> nodes --> This is a vector of all of the HNodes created for every character that appears in the file.
    
    int current_max --> This is a variable that keeps track of the current maximum weight of all of the nodes in the vector.

    int numChars --> This is a variable that keeps track of how many categories (characters) exist in the file.

    bool built --> This is a variable that indicates whether or not the tree has been built.


Method used in huffman.cpp:

    HuffmanTree() --> Constructor

    void insert(char ch, int weight) --> inserts a character and its associated weight into a node of the Huffman tree

    bool inTree(char ch) --> returns a boolean value indicating whether a given character is stored in the tree

    int GetFrequency(char ch) --> returns the weight of a given character

    void build() -->  Builds the Huffman Tree

    string GetCode(char ch) --> returns the compressed code of a given character in the tree using recursion

    void PrintTable() --> displays the Huffman encoding table used in the compression process

    int numNodes() --> returns the number of nodes currently in Huffman tree

    void mergeNodes() --> Takes the two smallest nodes and merges them together.

    int lookUp(char ch) --> returns the index of a given character in tree

    int lookUp(HNode *input) --> reutrn the index of a given address in a tree

    int GetFrequency(int i) --> returns the weight at a given index

    string GetCode(int i) --> returns the compressed code of the character at a given index


Compressing and Uncompressing a sample file

    Sample file contents: aeiou

    Sample file zipped output:

    597 001  --> Character a

    101 000 --> Character e

    105 11  --> Character i

    111 10  --> Character o

    117 01  --> Character u

    Huffman Encoded Output: 001000111001


The file will take in the characters from the input file, tally up the frequencies, and create nodes with weights for the Huffman tree.

A huffman tree will be built once the entire file is processed, and codes will be generated from the built tree. 
The output file first 
contains the number of categories there are, and then proceeds to list the each category (letters) by their 
ASCII values as well as 
their corresponding codes. Once all categories have been displayed, the next line is the sequence of output
of the characters in order 
in the form of their codes.
The unzip file will read in the first number as a stopping index for how many 
times it must read input in in the form of the "category + code"
format. Once that index has been reached, it then proceeds to read 
in the code until a match has been found. When a match is found, the code
is decrypted and the character is sent back to the output file. 
This process is repeated until the end of the file is reached.
