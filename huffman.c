
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 256

typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct PriorityQueue {
    Node *nodes[MAX_TREE_NODES];
    int size;
} PriorityQueue;

Node* createNode(char character, int frequency) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(PriorityQueue *pq, Node *node) {
    pq->nodes[pq->size++] = node;
    // Sift up to maintain heap property
    int i = pq->size - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->nodes[i]->frequency < pq->nodes[parent]->frequency) {
            Node *temp = pq->nodes[i];
            pq->nodes[i] = pq->nodes[parent];
            pq->nodes[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

Node* removeMin(PriorityQueue *pq) {
    if (pq->size == 0) return NULL;
    Node *minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    // Sift down to maintain heap property
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < pq->size && pq->nodes[left]->frequency < pq->nodes[smallest]->frequency) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right]->frequency < pq->nodes[smallest]->frequency) {
            smallest = right;
        }
        if (smallest == i) break;

        Node *temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[smallest];
        pq->nodes[smallest] = temp;
        i = smallest;
    }
    return minNode;
}

void buildHuffmanTree(PriorityQueue *pq) {
    while (pq->size > 1) {
        Node *left = removeMin(pq);
        Node *right = removeMin(pq);
        Node *combined = createNode('\0', left->frequency + right->frequency);
        combined->left = left;
        combined->right = right;
        insert(pq, combined);
    }
}

void generateCodes(Node *root, char *code, int depth, char codes[MAX_TREE_NODES][MAX_TREE_NODES]) {
    if (root->left) {
        code[depth] = '0';
        generateCodes(root->left, code, depth + 1, codes);
    }
    if (root->right) {
        code[depth] = '1';
        generateCodes(root->right, code, depth + 1, codes);
    }
    if (!root->left && !root->right) { // Leaf node
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->character], code);
    }
}

void compressFile(const char *inputFile, const char *outputFile) {
    int frequency[MAX_TREE_NODES] = {0};
    FILE *file = fopen(inputFile, "r");
    if (!file) {
        perror("Failed to open input file");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        frequency[ch]++;
    }
    fclose(file);

    PriorityQueue pq = { .size = 0 };
    for (int i = 0; i < MAX_TREE_NODES; i++) {
        if (frequency[i] > 0) {
            insert(&pq, createNode(i, frequency[i]));
        }
    }

    buildHuffmanTree(&pq);
    char codes[MAX_TREE_NODES][MAX_TREE_NODES] = {0};
    char code[MAX_TREE_NODES];
    generateCodes(pq.nodes[0], code, 0, codes);

    file = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "wb");
    if (!outFile) {
        perror("Failed to open output file");
        return;
    }

    // Write the compressed data to the output file
    while ((ch = fgetc(file)) != EOF) {
        fputs(codes[(unsigned char)ch], outFile);
    }
    
    fclose(file);
    fclose(outFile);
}

int main() {
    compressFile("input.txt", "output.bin");
    return 0;
}

