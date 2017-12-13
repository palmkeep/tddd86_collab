// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header
#include <vector>
#include <queue>
#include <map>

#include <algorithm>
#include <iostream>
#include <bitset>


#include "encoding.h"


//Creates a frequency table out of an input stream
map<int, int> buildFrequencyTable(istream& input)
{
    map<int, int> freqTable;
    char c;
    while (input.get(c))
    {
        if ( freqTable.find( (int)c ) != freqTable.end())
            freqTable[(int)c] += 1;
        else
            freqTable[(int)c] = 1;
    }

    if (input.eof())
    {
        freqTable[PSEUDO_EOF] = 1;
    }
    else
    {
        std::cout << "Error reading file" << std::endl;
    }
    for (auto it = freqTable.begin(); it != freqTable.end(); it++)
        cout << "freqTab: " << it->first << " oc: " << it->second << endl;

    return freqTable;
}

// Derefrences pointers to HuffmanNode's and compares them
class huffmanComp
{
public:
    huffmanComp() {}
    bool operator() (HuffmanNode* i, HuffmanNode* j)
    {
        return ( i->count > j->count);
    }
};

//Builds a Huffman encoding tree
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable)
{
    priority_queue< HuffmanNode*, vector<HuffmanNode*>, huffmanComp > leafs;

    // Create all leaf nodes
    for (map<int, int>::const_iterator it = freqTable.begin(); it != freqTable.end(); it++)
    {
        HuffmanNode* newNode = new HuffmanNode(it->first, it->second, nullptr, nullptr);
        leafs.push(newNode);
    }

    while (1 < leafs.size())
    {
        // Take the two least occuring characters and combine them in a new HuffmanNode
        // Remove two old node pointers and insert new node

        HuffmanNode* a = leafs.top();
        leafs.pop();
        HuffmanNode* b = leafs.top();
        leafs.pop();
        int sum = a->count + b->count;
        HuffmanNode* combNode = new HuffmanNode(NOT_A_CHAR, sum, a, b);

        leafs.push(combNode);  // Changes needed here if we want the exact same tree as in the examples
    }

    return leafs.top();
}


// Traverses the encoding tree and enters all encoded bitstrings into encodingmap. Helper function for buildEncodingMap
void gatherLeafNodes(const HuffmanNode* huffNode, map<int, string>& encodingMap, string& encoding)
{
    if (huffNode->isLeaf())
    {
        encodingMap.insert( std::pair<int, string>(huffNode->character, encoding));
    }
    else
    {
        encoding += "0";
        gatherLeafNodes(huffNode->zero, encodingMap, encoding);
        encoding += "1";
        gatherLeafNodes(huffNode->one, encodingMap, encoding);
    }
    encoding = encoding.substr(0, encoding.size()-1);
}

// Creates and returns an encoding map from an encoding tree
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    string emptyString = "";
    gatherLeafNodes(encodingTree, encodingMap, emptyString);

    return encodingMap;
}

// Encodes input given an encodingmap and sends the encoded data to the provided obistrem
void encodeData(istream& input, const map<int, string>& encodingMap, obitstream& output) {
    char c;
    while (input.get(c))   
    {
        string bitString = encodingMap.at(c);

        for (int i = 0; i < bitString.size(); i++)
        {
            if (bitString[i] == '0')
            {
                output.writeBit(0);
            }
            else
            {
                output.writeBit(1);
            }
        }
    }
    //EOF
    string bitString = encodingMap.at(PSEUDO_EOF);
    for (int i = 0; i < bitString.size(); i++)
    {
        if (bitString[i] == '0')
        {
            output.writeBit(false);
        }
        else
        {
            output.writeBit(true);
        }
    }
}

// Decodes input given an encoding tree and sends the decoded data to the provided obistrem
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int bit;
    int conseqZeroes = 0;
    HuffmanNode* currentNode = encodingTree;
    while ( (bit = input.readBit()) != -1)
    {

        if (bit)
        {
            conseqZeroes = 0;
            currentNode = currentNode->one;
        }
        else
        {
            conseqZeroes += 1;
            if (conseqZeroes == 9)
            {
                break;
            }
            currentNode = currentNode->zero;
        }

        if (currentNode->isLeaf())
        {
            if (currentNode->character == PSEUDO_EOF)
            {
                cout << "EOF" << endl;
                break;
            }
            output << (char)currentNode->character;
            currentNode = encodingTree;
        }
    }
}

// Write a given char as a byte to output
void writeCharAsByte(const char ch, obitstream& output)
{
    int numBits = 7;
    for (int i = numBits; 0 <= i; i--)
    {
        if ((ch & (1 << i)) != 0)
        {
            cout << 1;
            output.writeBit(true);
        }
        else
        {
            cout << 0;
            output.writeBit(false);
        }
    }
    cout << endl;
}

void writeIntAsByte(const int input, const int numBytes, obitstream& output)
{
    int indexBit = 8*numBytes - 1;

    for (int i = indexBit; 0 <= i; i--)
    {
        if ((input & (1 << i)) != 0)
        {
            cout << 1;
            output.writeBit(true);
        }
        else
        {
            cout << 0;
            output.writeBit(false);
        }
    }

}

// Compresses an input file and sends it to provided output
void compress(istream& input, obitstream& output)
{
    string copyInput = "";
    char c;
    while (input.get(c))
    {
        copyInput += c;
    }
    istringstream freqStream(copyInput);

    map<int, int> freqTable = buildFrequencyTable(freqStream);

    HuffmanNode* encTree = buildEncodingTree(freqTable);
    map<int, string> encMap = buildEncodingMap(encTree);

    output.writeBit(true);
    writeCharAsByte(1, output);
    for (auto const & freq : freqTable) {
        int ch = freq.first;
        int occ = freq.second;
        if (ch == PSEUDO_EOF)
        {
            output.writeBit(false);
        }
        else
        {
            output.writeBit(true);
        }
        writeCharAsByte(ch, output);
        output.writeBit(true);
        cout << "occ: " << occ << " ";
        writeIntAsByte(occ, 4, output); // Encodes occurence as a byte long int
    }
    output.writeBit(true);
    writeCharAsByte(2, output);

    //Encodes input and sends it to output (obitstream)
    istringstream encStream(copyInput);
    encodeData(encStream, encMap, output);
}

// Converts a binary string to int
int binStrToDec(string num)
{
    int res;
    int b = 1;
    for (int i = num.size() - 1; 0 <= i; i--)
    {
        if (num.at(i) == '1')
        {
            res += b;
        }
        b *= 2;
    }
    return res;
}

// Decompresses an input file 9and sends it to provided output
void decompress(ibitstream& input, ostream& output)
{
    bool reachedEOF = false;
    bool reachedEOH = false;
    bool readingNumber = false;

    map<int, int> freqTable;
    while (!reachedEOH)
    {
        string data = "";
        int ch;

        bool readingEOF = false;
        if (!input.readBit())
        {
            readingEOF = true;
        }

        int i = 8;
        if (readingNumber)
        {
            i *= 4;
        }
        for (i; 0 < i; i--)
        {
            int bit = input.readBit();
            if (bit == -1)
            {
                reachedEOF = true;
                throw std::invalid_argument( "EOF in HEADER" );
            }
            else if (bit)
            {
                data += "1";
            }
            else
            {
                data += "0";
            }
        }
        cout << "Data: " << data << endl;

        if (data == "00000000" && readingEOF)
        {
            ch = PSEUDO_EOF;
            readingNumber = true;
        }
        else if (data == "00000001"){} // Start of HEAD
        else if (data == "00000010" && !readingNumber)
        {
            reachedEOH = true;
        }
        else if (!readingNumber)
        {
            ch = binStrToDec(data);
            readingNumber = true;
        }
        else
        {
            int occ = binStrToDec(data);
            cout << "ch: " << ch << " occ: " << occ << endl;
            freqTable[ch] = occ;
            readingNumber = false;
        }
    }

    HuffmanNode* encTree = buildEncodingTree(freqTable);

    decodeData(input, encTree, output);
}

// Removes all data associated with an encoding tree
void freeTree(HuffmanNode* node)
{
    if (node->isLeaf())
    {
        delete node;
    }
    else
    {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
