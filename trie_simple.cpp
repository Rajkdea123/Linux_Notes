#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

class TrieNode {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
    
public:
    Trie() {
        root = std::make_unique<TrieNode>();
    }
    
    // Insert a word into the trie
    void insert(const std::string& word) {
        TrieNode* current = root.get();
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        
        current->isEndOfWord = true;
    }
    
    // Search for a word in the trie
    bool search(const std::string& word) {
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
    bool startsWith(const std::string& prefix) {
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
    std::cout << "Search 'apple': " << (trie.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'appl': " << (trie.search("appl") ? "true" : "false") << std::endl;
    
    // Test startsWith
    std::cout << "StartsWith 'app': " << (trie.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie.startsWith("appl") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'ban': " << (trie.startsWith("ban") ? "true" : "false") << std::endl;
    
    return 0;
}