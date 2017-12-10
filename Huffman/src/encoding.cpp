// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header
#include <vector>
#include <map>

#include <algorithm>
#include <iostream>
#include <bitset>


#include "encoding.h"
// TODO: include any other headers you need


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

    return freqTable;
}



// Derefrences pointers to HuffmanNode's and compares them
bool huffmanNodePointerComparison (HuffmanNode* i, HuffmanNode* j)
{
    return ( *i < *j);
}

//Builds a Huffman encoding tree
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable)
{
    vector<HuffmanNode*> leafs;

    // Create all leaf nodes
    for (map<int, int>::const_iterator it = freqTable.begin(); it != freqTable.end(); it++)
    {
        HuffmanNode* newNode = new HuffmanNode(it->first, it->second, nullptr, nullptr);
        leafs.push_back(newNode);
    }

    while (1 < leafs.size())
    {
        std::sort(leafs.begin(), leafs.end(), huffmanNodePointerComparison);

        // Take the two least occuring characters and combine them in a new HuffmanNode
        // Remove two old node pointers and insert new node
        int tot = leafs[leafs.size() - 1]->count + leafs[leafs.size() - 2]->count;
        HuffmanNode* combNode = new HuffmanNode(NOT_A_CHAR, tot, leafs[leafs.size() - 1], leafs[leafs.size() - 2]);
        leafs.pop_back();
        leafs.pop_back();           // Remove the two pointers that where placed in the new node
        leafs.push_back(combNode);  // Changes needed here if we want the exact same tree as in the examples
    }

    return leafs.front();
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
    HuffmanNode* currentNode = encodingTree;
    while ( (bit = input.readBit()) != -1)
    {
        if (bit)
            currentNode = currentNode->one;
        else
        {
            currentNode = currentNode->zero;
        }

        if (currentNode->isLeaf())
        {
            output << (char)currentNode->character;
            currentNode = encodingTree;
        }
    }
}

// Compresses an input file and sends it to provided output
void compress(istream& input, obitstream& output)
{
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* encTree = buildEncodingTree(freqTable);
    map<int, string> encMap = buildEncodingMap(encTree);

    //WRITE STAGE
    output.put((int)'{');
    cout << "{";
    bool firstChar = true;
    for (auto const & freq : freqTable) {
        if (!firstChar)
        {
            output.put((int)',');
            output.put((int)' ');
            cout <<  ", ";
        }
        else
        {
            firstChar = false;
        }
        int ch = freq.first;
        int occ = freq.second;
        output.put(ch);
        output.put(':');
        output.put(occ); // Encodes occurence as a byte long int

        cout << ch << ":" << occ;
    }
    output.put('}');
    cout << "}";


    //Encodes input and sends it to output (obitstream)
    encodeData(input, encMap, output);
}

// Decompresses an input file and sends it to provided output
void decompress(ibitstream& input, ostream& output)
{
    // TODO: implement this functionleafs.push_back(combNode);
}

// Removes all data associated with an encoding tree
void freeTree(HuffmanNode* node)
{
    // TODO: implement this function
}
