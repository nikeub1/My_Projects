#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

struct Node
{
    char data;

    Node *left;
    Node *right;

    // constructor if data provided
    Node(char data):data(data),left(nullptr),right(nullptr){}
    // default constructor
    Node() : data('\0'), left(nullptr), right(nullptr) {}
};

Node *deserilizeTree(ifstream &infile)
{
    char marker = infile.get();
    if(marker == '1') // finds leaf node
    {
        char dataChar = infile.get();
        return new Node(dataChar);
    }
    else if(marker == '0')
    {
        Node *node = new Node(); // build a new node and start bulding left and right recurssively
        node->left = deserilizeTree(infile);
        node->right = deserilizeTree(infile);
        return node;
    }

    if (marker != '1' && marker != '0') {
        cerr << "Error: Invalid tree structure in file." << endl;
        return nullptr;
    }

    return nullptr;
}

void decode(ifstream &infile, ofstream &outfile, Node *root)
{
    Node *current = root;
    char byte;

    while(infile.get(byte))
    {
        for(int i = 7; i >= 0; i-- )
        {
            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left; // traverse the huffman tree on left if 0 and right if 1


            if(!current->left && !current->right) // when reach leaf node put in the data and reset node.
            {
                outfile.put(current->data);
                current = root;
            }
        }
    }
}

void deleteTree(Node* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        cerr<<"Usage: ./decompress <CompressedFile> <compressed_files tree>"<<endl;
        return 1;
    }

    ifstream infile(argv[1], ios::binary);
    if(!infile.is_open())
    {
        cerr<<"Error while opening the infile!"<<endl;
        return 1;
    }
    ifstream trfile(argv[2], ios::binary);
    if(!trfile.is_open())
    {
        cerr<<"Error while opening the infile!"<<endl;
        return 1;
    }

    Node* huffmanTree = deserilizeTree(trfile);

    string outfilename = "decompressed_" + string(argv[1]);
    ofstream outfile(outfilename, ios::binary);

    if(!outfile.is_open())
    {
        cerr<<"Error while opening the outfile"<<endl;
        return 1;
    }

    decode(infile, outfile, huffmanTree);

    infile.close();
    outfile.close();

    deleteTree(huffmanTree);

    cout<<"File decompressed successfully to "<<outfilename<<endl;
    return 0;
}
