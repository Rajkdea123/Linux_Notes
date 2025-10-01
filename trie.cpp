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
    
    // Helper method to recursively delete nodes
    void deleteNode(TrieNode* node) {
        if (!node) return;
        
        for (auto& pair : node->children) {
            deleteNode(pair.second.get());
        }
    }
    
public:
    Trie() {
        root = make_unique<TrieNode>();
    }
    
    // Destructor
    ~Trie() {
        // Smart pointers will handle cleanup automatically
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
    
    // Optional: Get all words with a given prefix
    vector<string> getWordsWithPrefix(const string& prefix) {
        vector<string> result;
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
    void collectWords(TrieNode* node, const string& currentWord, vector<string>& result) {
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
    
    cout << "=== Trie Data Structure Test ===" << endl;
    
    // Test insert and search
    cout << "\n1. Testing insert and search:" << endl;
    
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");
    trie.insert("band");
    
    cout << "Inserted words: apple, app, application, apply, banana, band" << endl;
    
    // Test search
    cout << "\n2. Testing search:" << endl;
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not found") << endl;
    cout << "Search 'banana': " << (trie.search("banana") ? "Found" : "Not found") << endl;
    cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not found") << endl;
    
    // Test startsWith
    cout << "\n3. Testing startsWith:" << endl;
    cout << "StartsWith 'app': " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    cout << "StartsWith 'appl': " << (trie.startsWith("appl") ? "Yes" : "No") << endl;
    cout << "StartsWith 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << endl;
    cout << "StartsWith 'ora': " << (trie.startsWith("ora") ? "Yes" : "No") << endl;
    cout << "StartsWith 'z': " << (trie.startsWith("z") ? "Yes" : "No") << endl;
    
    // Test getWordsWithPrefix (bonus functionality)
    cout << "\n4. Testing getWordsWithPrefix (bonus):" << endl;
    auto wordsWithApp = trie.getWordsWithPrefix("app");
    cout << "Words starting with 'app': ";
    for (const auto& word : wordsWithApp) {
        cout << word << " ";
    }
    cout << endl;
    
    auto wordsWithBan = trie.getWordsWithPrefix("ban");
    cout << "Words starting with 'ban': ";
    for (const auto& word : wordsWithBan) {
        cout << word << " ";
    }
    cout << endl;
}

int main() {
    testTrie();
    return 0;
}