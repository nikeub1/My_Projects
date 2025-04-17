# Compression and Decompression program using Huffman Coding in C++
#### Video Demo:  <[URL HERE](https://youtu.be/b0GQYBpoRp0)>
#### Description:

### compress.cpp:
This file contains the neccessary functions and algorithms to compress the file. As you see in the code, the node structure contains the char, its frequency, right and left pointers that will help us create the huffman tree.

The compare bool function helps us create a priority queue, in which we find the two most less frequent characters that appear in the file so we can add them and their sum to the huffmantree.

The buildHuffmanTree function constructs the Huffman tree. It repeatedly selects the two least frequent characters, creates a new internal node combining them, and restructures the priority queue until only one node remains, which becomes the root of the tree.

GenerateCodes gives the shortened bit values to each character, instead of the 8bit ASCII value it shortens it by traversing the huffman tree, on the left its 0 and on the right its 1 and when shortening it, it saves the values in the codeMap.

writeTree writes the serialized information of the huffman tree to a seperate file called tree.(the inputed file type). The internal nodes are marked as '0's and leaf nodes as '1's followed by character data.

### decompress.cpp:
The node structure is altered so it contains the character, the and right node that will be useful to navigate the reconstructed huffman tree.

deserilizeTree is a function which takes the original huffman tree that we created as a seperate file in order to provide context while decoding the file. Markers are used to identify leaf nodes and internal nodes, where if marker is of value 1, that means its a leaf node and extracts the character and returns the newly created node, if the marker equal 0 then its an internal node which has left and right nodes added from the original tree binary file.

decode is a functuon which now takes the compressed file along with the newly reconstructed tree and starts to decode the compressed data. it reads each byte, examines its bits and traverses left to right. When leaf node is reached the corresponding character then is written into the new file that supposed to output the compressed data. This continues till the entire file is decoded.

deleTree is used to delete the original tree, in order to free the allocated memory after the decompression process is succesfully finished. It recursively deletes each node in the tree to ensure no memory leaks appear. Used for safety.

### Process of the project:
My main reason why I chose this project is because I understood the difficulty and the time it would take to learn the required concpets and methods. Since I'm a Computer Science student in Ilia State University, I thought it would be useful to put my knowledge to the test, independently create a project of my choosing. Also, the time it took for me to complete this project is almost a month, having to juggle between university assignments, labs, midterms and allocating 3-4 hours of free time to not lose motvation completely.

Its not the first time i had to code a project on my own, during my freshmen year my Intro to Programming professor gave us a group assignment, where we hade to construct a mock bank program in c++, unfortunately, due to some complications I had to work on my own and go through sleepless nights to meet the deadlines. This taught me a very valuable lesson, that no matter how difficult it may seem to do something big on your own, the first step is the biggest step to success.

Initially, I started with understanding how the Huffman Coding compresses data mathmatically, after I chose my programming language I decided to look into the libraries that exist and how they might help me. For some time I thought I should include a user interface to make it easier and aesthetically pleasant, but after contemplating about it I realized that it would take more time which I, unfortunately, don't have, than expected.

The materials I used were from week 4 to understand pointer usage, week 5 for datastructures, geeksforgeeks to understand queues, vectors and maps and duck50 (harvards AI) to ask for guidence, step by step general instructions to build the compression and decompression program.
The reason I used C++ is because it has more libraries to ease the process instead of defining the datastructures manually in C. Its also very versitile and memory handiling is easier.
One can ask the question of why did I decide to use C++ instead of python, the answer is because its more challenging and requires you to use all of the concepts learned in the CS50 course.




