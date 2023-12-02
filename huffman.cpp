#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    char data;
    unsigned frequency;
    Node* left;
    Node* right;

    Node(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

Node* buildHuffmanTree(const string& characters, const vector<unsigned>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (size_t i = 0; i < characters.length(); ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* internalNode = new Node('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

void printHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
        cout << "  " << root->data << " : " << code << endl;
    }

    printHuffmanCodes(root->left, code + "0", huffmanCodes);
    printHuffmanCodes(root->right, code + "1", huffmanCodes);
}

void huffmanCoding() {
    string S;
    cout << "Enter characters (no spaces): ";
    cin >> S;

    vector<unsigned> f;
    cout << "Enter frequencies for each character: ";
    for (char c : S) {
        unsigned frequency;
        cin >> frequency;
        f.push_back(frequency);
    }

    Node* root = buildHuffmanTree(S, f);

    cout << "Huffman codes will be:" << endl;

    unordered_map<char, string> huffmanCodes;
    printHuffmanCodes(root, "", huffmanCodes);
}

int main() {
    huffmanCoding();

    return 0;
}
