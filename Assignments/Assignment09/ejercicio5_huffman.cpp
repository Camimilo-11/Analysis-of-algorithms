#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

struct Node {
    char symbol;
    double freq;
    Node* left;
    Node* right;

    Node(char s, double f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
    Node(double f, Node* l, Node* r) : symbol('\0'), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, const string& code, map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->symbol] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

string encodeString(const string& text, const map<char, string>& huffmanCode) {
    string encoded = "";
    for (char c : text) {
        encoded += huffmanCode.at(c);
    }
    return encoded;
}

string decodeString(Node* root, const string& bitString) {
    string decoded = "";
    Node* curr = root;
    for (char bit : bitString) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            decoded += curr->symbol;
            curr = root;
        }
    }
    return decoded;
}

int main() {
    vector<pair<char, double>> frequencies = {
        {'A', 0.4},
        {'B', 0.1},
        {'C', 0.2},
        {'D', 0.15},
        {'_', 0.15}
    };

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node(left->freq + right->freq, left, right);
        pq.push(parent);
    }

    Node* root = pq.top();
    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "=== Huffman Code Table ===" << endl;
    for (auto p : huffmanCode) {
        cout << "Symbol: '" << p.first << "' -> Code: " << p.second << endl;
    }
    cout << endl;

    // 5.2 Encode ABACABAD
    string toEncode = "ABACABAD";
    string encoded = encodeString(toEncode, huffmanCode);
    cout << "Encoded '" << toEncode << "': " << encoded << endl;

    // 5.3 Decode 100010111001010
    string bitStr = "100010111001010";
    string decoded = decodeString(root, bitStr);
    cout << "Decoded '" << bitStr << "': " << decoded << endl;

    return 0;
}
