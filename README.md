## Documentation

### HuffmanAlgorithm

This C code implements a simple Huffman compression algorithm. Huffman coding is a widely used method for lossless data compression. The code creates a Huffman tree based on character frequencies in a given input file, generates binary codes for each character, and writes the compressed data to an output file. Below is a detailed explanation of the different sections and functions in the code.

### Includes and Definitions

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 256
#define MAX_CODE_LENGTH 256
```

- The code includes standard libraries for input/output (`stdio.h`), memory management (`stdlib.h`), and string manipulation (`string.h`).
- It defines constants for the maximum number of tree nodes (256, corresponding to the number of possible ASCII characters) and the maximum length of a code (256 bits).

### Data Structures

```c
typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;
```

- `Node` represents each node in the Huffman tree. Each node contains:
  - `character`: the character it represents.
  - `frequency`: how often that character appears in the input data.
  - `left` and `right`: pointers to the left and right children in the tree.

```c
typedef struct PriorityQueue {
    Node *nodes[MAX_TREE_NODES];
    int size;
} PriorityQueue;
```

- `PriorityQueue` is a simple array-based priority queue to manage the nodes based on their frequencies. It holds an array of `Node` pointers and the current size of the queue.

### Functions

1. **Creating Nodes**

```c
Node* createNode(char character, int frequency) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}
```

- Allocates and initializes a new node with a given character and frequency.

2. **Inserting Nodes into Priority Queue**

```c
void insert(PriorityQueue *pq, Node *node) {
    pq->nodes[pq->size++] = node;
    // Sift up to maintain heap property
    ...
}
```

- Inserts a node into the priority queue and maintains the heap property (min-heap) by sifting up.

3. **Removing the Minimum Node**

```c
Node* removeMin(PriorityQueue *pq) {
    ...
}
```

- Removes and returns the node with the smallest frequency from the priority queue while maintaining the heap property by sifting down.

4. **Building the Huffman Tree**

```c
void buildHuffmanTree(PriorityQueue *pq) {
    while (pq->size > 1) {
        Node *left = removeMin(pq);
        Node *right = removeMin(pq);
        Node *combined = createNode('\0', left->frequency + right->frequency);
        ...
    }
}
```

- Combines the two nodes with the smallest frequencies to create a new internal node until only one node remains, which becomes the root of the Huffman tree.

5. **Generating Huffman Codes**

```c
void generateCodes(Node *root, char *code, int depth, char codes[MAX_TREE_NODES][MAX_CODE_LENGTH]) {
    ...
}
```

- Recursively traverses the Huffman tree to generate binary codes for each character, storing them in the `codes` array.

6. **Compressing the File**

```c
void compressFile(const char *inputFile, const char *outputFile) {
    ...
}
```

- Reads the input file, calculates character frequencies, builds the Huffman tree, generates codes, and writes the compressed binary data to the output file. It handles bit-level operations to pack bits into bytes.

### Main Function

```c
int main() {
    compressFile("input.txt", "output.bin");
    return 0;
}
```

- The `main` function calls `compressFile`, specifying `input.txt` as the input file and `output.bin` as the output file where the compressed data will be stored.

### Summary

- The code efficiently compresses a text file using Huffman coding by creating a tree based on character frequencies, generating unique binary codes for each character, and writing the compressed data as a binary file.


![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
