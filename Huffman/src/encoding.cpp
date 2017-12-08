// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header
#include <vector>
#include <algorithm>

#include "encoding.h"
// TODO: include any other headers you need


//Creates a frequency table out of an input stream
map<int, int> buildFrequencyTable(istream& input) {
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
        if ( freqTable.find(256) != freqTable.end())
            freqTable[256] += 1;
        else
            freqTable[256] = 1;
    }
    else
    {
        std::cout << "Error reading file" << std::endl;
    }

    std::cout << input.get() << std::endl;
    return freqTable;
}



// Derefrences pointers to HuffmanNode's and compares them
bool huffmanNodePointerComparison (HuffmanNode* i, HuffmanNode* j)
{
    return ( *i < *j);
}

//
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable) {
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
        leafs.pop_back(); // Remove the two pointers that where placed in the new node
        leafs.push_back(combNode);
    }

    return leafs.front();
}

void gatherLeafNodes(const HuffmanNode*& huffNode, map<int, string>& encodingMap)
{
    if (huffNode->isLeaf())
    {
        encodingMap.insert(huffNode->character, huffNode->count);
    }
    else
    {
        gatherLeafNodes(huffNode->zero, encodingMap);
        gatherLeafNodes(huffNode->one, encodingMap);
    }
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    gatherLeafNodes(encodingTree, encodingMap);

    return encodingMap;
}

void encodeData(istream& input, const map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
