#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    unordered_map<char, unique_ptr<TrieNode>> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    unique_ptr<TrieNode> root;
    
public:
    Trie() {
        root = make_unique<TrieNode>();
    }
    
    // Insert a word into the trie
    void insert(const string& word) {
        TrieNode* current = root.get();
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        
        current->isEndOfWord = true;
    }
    
    // Search for a word in the trie
    bool search(const string& word) {
        TrieNode* current = root.get();
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c].get();
        }
        
        return current->isEndOfWord;
    }
    
    // Check if any word starts with the given prefix
    bool startsWith(const string& prefix) {
        TrieNode* current = root.get();
        
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c].get();
        }
        
        return true;
    }
};

// Example usage
int main() {
    Trie trie;
    
    // Insert words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("banana");
    
    // Test search
    cout << "Search 'apple': " << (trie.search("apple") ? "true" : "false") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "true" : "false") << endl;
    
    // Test startsWith
    cout << "StartsWith 'app': " << (trie.startsWith("app") ? "true" : "false") << endl;
    cout << "StartsWith 'appl': " << (trie.startsWith("appl") ? "true" : "false") << endl;
    cout << "StartsWith 'ban': " << (trie.startsWith("ban") ? "true" : "false") << endl;
    
    return 0;
}