#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Trie {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        bool isEndOfWord;
        
        TrieNode() : isEndOfWord(false) {}
    };
    
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* current = root;
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        
        current->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* current = root;
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        
        return current->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* current = root;
        
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        
        return true;
    }
    
    // Destructor to clean up memory
    ~Trie() {
        deleteTrie(root);
    }
    
private:
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        
        delete node;
    }
};

// Example usage and test cases
int main() {
    Trie trie;
    
    // Test insert and search
    trie.insert("apple");
    cout << "Search 'apple': " << (trie.search("apple") ? "true" : "false") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << endl;
    
    // Test startsWith
    cout << "StartsWith 'app': " << (trie.startsWith("app") ? "true" : "false") << endl;
    
    // Insert more words
    trie.insert("app");
    trie.insert("application");
    
    cout << "Search 'app' after insert: " << (trie.search("app") ? "true" : "false") << endl;
    cout << "StartsWith 'appl': " << (trie.startsWith("appl") ? "true" : "false") << endl;
    
    return 0;
}