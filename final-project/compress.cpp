#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <string>

using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left,*right;

    // This is a Constructor which will help me make creating a node
    Node(char data, int freq): data(data), freq(freq), left(nullptr), right(nullptr){}
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(priority_queue<Node*,vector<Node*>, Compare> &pq)
{
    while(pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *internal = new Node('\0', left->freq + right->freq);
        internal->left = left;
        internal->right = right;

        pq.push(internal);

    }
    Node *root = pq.top();

    return root;
}

void generateCodes(Node *node, string code, map<char, string>& codeMap)
{
    if(!node->left && !node->right)
    {
        codeMap[node->data] = code;
    }
    else
    {
        if(node->left)
        {
            generateCodes(node->left, code + "0", codeMap);
        }
        if(node->right)
        {
            generateCodes(node->right, code + "1", codeMap);
        }
    }
}

void writeTree(Node * node, ofstream &outfile)
{
    if(!node)
    {
        return;
    }
    if(!node->left && !node->right)
    {
        outfile.put('1');
        outfile.put(node->data);
    }
    else
    {
        outfile.put('0');
        writeTree(node->left, outfile);
        writeTree(node->right, outfile);
    }
}



int main(int argc, char *argv[])
{
    // define the accepted file types
    vector<string> file_type = {".txt",".log", ".csv", ".bmp", ".ppm", ".wav", ".aiff", ".c", ".cpp", ".py"};

    if(argc != 2)
    {
        cerr<<"Usage: "<<argv[0]<<" <filename>"<<endl;
        return 1;
    }

    string file_c = argv[1];
    string ftype = "";
    bool flag = false;


    // checking for valid file types
    for(string &ext: file_type)
    {
        if(file_c.find(ext) != string::npos){
            flag = true;
            ftype = ext;
            break;
        }
    }

    if(flag == false)
    {
        cout<<"Files permited: .txt, .jpeg, .wav"<<endl;
        return 1;
    }

    ifstream file(argv[1]);
    if(!file.is_open())
    {
        cerr<<"Error encountered while opening a file!"<<endl;
        return 1;
    }
    // helps with defining a Node
    unordered_map<char,int> freq;

    // loops over the contents of the file and adds them to the map for later use
    if(file.is_open())
    {
        char ch;
        while(file.get(ch))
        {
            freq[ch]++;
        }
        file.close();
    }
    // mini heap to add the two smallest nodes to the huffman tree
    priority_queue<Node*,vector<Node*>, Compare> pq;

    for(const auto& pair : freq)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    // root node of the huffman tree
    Node *huffmantree = buildHuffmanTree(pq);
    string code = "";
    map<char, string> codeMap;

    generateCodes(huffmantree, code, codeMap);

    // to name the compressed file based on the file type
    ofstream newFile("cp_" + file_c);

    ofstream tree("tree" + ftype);

    writeTree(huffmantree, tree);

    file.open(file_c);
    // check to see if file opens properly
    if(!file.is_open())
    {
        cerr<<"Error while opening a file!"<<endl;
        return 1;
    }
    // begin inputting the generated huffman codes into the new compressed file
    if(file.is_open())
    {
        unsigned char byte = 0;
        int bitCount = 0;
        char ch;
        while(file.get(ch))
        {
            string code = codeMap[ch];
            for(char bit: code)
            {
                byte = (byte << 1) | (bit - '0');
                bitCount++;
                if(bitCount == 8)
                {
                    newFile.put(byte);
                    byte = 0;
                    bitCount = 0;
                }
            }
        }

        if (bitCount > 0)
        {
            byte <<= (8 - bitCount);
            newFile.put(byte);
        }
        file.close();
        newFile.close();
    }
}
