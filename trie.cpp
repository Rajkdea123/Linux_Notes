#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class TrieNode {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
    
    // Helper method to recursively delete nodes
    void deleteNode(TrieNode* node) {
        if (!node) return;
        
        for (auto& pair : node->children) {
            deleteNode(pair.second.get());
        }
    }
    
public:
    Trie() {
        root = std::make_unique<TrieNode>();
    }
    
    // Destructor
    ~Trie() {
        // Smart pointers will handle cleanup automatically
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
    
    // Optional: Get all words with a given prefix
    std::vector<std::string> getWordsWithPrefix(const std::string& prefix) {
        std::vector<std::string> result;
        TrieNode* current = root.get();
        
        // Navigate to the prefix node
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return result; // No words with this prefix
            }
            current = current->children[c].get();
        }
        
        // Collect all words from this node
        collectWords(current, prefix, result);
        return result;
    }
    
private:
    // Helper method to collect all words from a node
    void collectWords(TrieNode* node, const std::string& currentWord, std::vector<std::string>& result) {
        if (node->isEndOfWord) {
            result.push_back(currentWord);
        }
        
        for (const auto& pair : node->children) {
            collectWords(pair.second.get(), currentWord + pair.first, result);
        }
    }
};

// Test function to demonstrate the Trie functionality
void testTrie() {
    Trie trie;
    
    std::cout << "=== Trie Data Structure Test ===" << std::endl;
    
    // Test insert and search
    std::cout << "\n1. Testing insert and search:" << std::endl;
    
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");
    trie.insert("band");
    
    std::cout << "Inserted words: apple, app, application, apply, banana, band" << std::endl;
    
    // Test search
    std::cout << "\n2. Testing search:" << std::endl;
    std::cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'banana': " << (trie.search("banana") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not found") << std::endl;
    
    // Test startsWith
    std::cout << "\n3. Testing startsWith:" << std::endl;
    std::cout << "StartsWith 'app': " << (trie.startsWith("app") ? "Yes" : "No") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie.startsWith("appl") ? "Yes" : "No") << std::endl;
    std::cout << "StartsWith 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << std::endl;
    std::cout << "StartsWith 'ora': " << (trie.startsWith("ora") ? "Yes" : "No") << std::endl;
    std::cout << "StartsWith 'z': " << (trie.startsWith("z") ? "Yes" : "No") << std::endl;
    
    // Test getWordsWithPrefix (bonus functionality)
    std::cout << "\n4. Testing getWordsWithPrefix (bonus):" << std::endl;
    auto wordsWithApp = trie.getWordsWithPrefix("app");
    std::cout << "Words starting with 'app': ";
    for (const auto& word : wordsWithApp) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    auto wordsWithBan = trie.getWordsWithPrefix("ban");
    std::cout << "Words starting with 'ban': ";
    for (const auto& word : wordsWithBan) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

int main() {
    testTrie();
    return 0;
}