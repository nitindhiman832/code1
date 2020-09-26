#include <iostream>
#include <fstream>
using std:: string;
using std:: cin;
using std:: cout;
using std:: endl;

class TrieNode{
public:
    int frequency;
    TrieNode* data[26]{};
    TrieNode() {
        frequency = 0;
        for(auto &i : data) {
            i = nullptr;
        }
    }
};

void insert(TrieNode* root, const string& key, int freq) {
    auto* new_node = new TrieNode;
    for(char i : key) {
        int index = i - 'a';
        if(!root->data[index]) {
            root->data[index] = new_node;
        }
        root = root->data[index];
    }
    root->frequency = freq;
}

void search(TrieNode* root, const string& key) {
    for(char i : key) {
        int index = i - 'a';
        if(!root->data[index]) {
            cout << "Word does not exist in the dictionary\n";
            return;
        }
        root = root->data[index];
    }
    if(root != nullptr && root->frequency) {
        cout << key << " " << root->frequency;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: ./a.out word_to_be_searched <path_to_dictionary>"
             << endl;
        return 1;
    }

    auto *root = new TrieNode;

    std::fstream words(argv[2], std::ios_base::in);
    string line;
    while (std::getline(words, line)) {
        string current, freq;
        int i = 0;
        while(line[i] != ',') {
            current += line[i];
            ++i;
        }
        ++i;
        while(line[i]) {
            freq += line[i];
            ++i;
        }
        insert(root, current, stoi(freq));
        line.clear();
    }

    search(root, argv[1]);
    return 0;
}