#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * Trie (Prefix Tree) Implementation
 * 
 * A Trie is a tree-like data structure that stores strings in a way that
 * allows for efficient prefix-based operations. Each node represents a character,
 * and paths from root to leaf nodes represent complete words.
 * 
 * Key Components:
 * 1. TrieNode: Represents each node in the trie
 * 2. Trie: Main class containing the trie operations
 * 
 * Time Complexities:
 * - Insert: O(m) where m is the length of the word
 * - Search: O(m) where m is the length of the word
 * - startsWith: O(m) where m is the length of the prefix
 * 
 * Space Complexity: O(ALPHABET_SIZE * N * M) where N is number of words and M is average length
 */

class TrieNode {
public:
    TrieNode* children[26];  // Array to store child nodes for each letter (a-z)
    bool isEndOfWord;       // Flag to mark if this node represents end of a word
    
    // Constructor
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
    
    // Destructor to prevent memory leaks
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
    }
};

class Trie {
private:
    TrieNode* root;
    
    // Helper function to convert character to index (0-25)
    int charToIndex(char c) {
        return c - 'a';
    }
    
public:
    // Constructor
    Trie() {
        root = new TrieNode();
    }
    
    // Destructor
    ~Trie() {
        delete root;
    }
    
    /**
     * Insert a word into the trie
     * 
     * Algorithm:
     * 1. Start from the root node
     * 2. For each character in the word:
     *    - Calculate the index for the character
     *    - If the child node doesn't exist, create it
     *    - Move to the child node
     * 3. Mark the last node as end of word
     * 
     * Time Complexity: O(m) where m is the length of the word
     * Space Complexity: O(m) for the path nodes
     */
    void insert(string word) {
        TrieNode* current = root;
        
        for (char c : word) {
            int index = charToIndex(c);
            
            // If child node doesn't exist, create it
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            
            // Move to the child node
            current = current->children[index];
        }
        
        // Mark the last node as end of word
        current->isEndOfWord = true;
    }
    
    /**
     * Search for a complete word in the trie
     * 
     * Algorithm:
     * 1. Start from the root node
     * 2. For each character in the word:
     *    - Calculate the index for the character
     *    - If the child node doesn't exist, return false
     *    - Move to the child node
     * 3. Check if the last node is marked as end of word
     * 
     * Time Complexity: O(m) where m is the length of the word
     * Space Complexity: O(1)
     */
    bool search(string word) {
        TrieNode* current = root;
        
        for (char c : word) {
            int index = charToIndex(c);
            
            // If child node doesn't exist, word is not in trie
            if (current->children[index] == nullptr) {
                return false;
            }
            
            // Move to the child node
            current = current->children[index];
        }
        
        // Return true only if this node is marked as end of word
        return current->isEndOfWord;
    }
    
    /**
     * Check if any word in the trie starts with the given prefix
     * 
     * Algorithm:
     * 1. Start from the root node
     * 2. For each character in the prefix:
     *    - Calculate the index for the character
     *    - If the child node doesn't exist, return false
     *    - Move to the child node
     * 3. If we can traverse the entire prefix, return true
     * 
     * Time Complexity: O(m) where m is the length of the prefix
     * Space Complexity: O(1)
     */
    bool startsWith(string prefix) {
        TrieNode* current = root;
        
        for (char c : prefix) {
            int index = charToIndex(c);
            
            // If child node doesn't exist, no word starts with this prefix
            if (current->children[index] == nullptr) {
                return false;
            }
            
            // Move to the child node
            current = current->children[index];
        }
        
        // If we can traverse the entire prefix, return true
        return true;
    }
    
    /**
     * Utility function to print all words in the trie
     * This is helpful for debugging and understanding the trie structure
     */
    void printAllWords() {
        cout << "All words in the trie: ";
        printWordsFromNode(root, "");
        cout << endl;
    }
    
private:
    void printWordsFromNode(TrieNode* node, string currentWord) {
        if (node == nullptr) return;
        
        // If this node marks the end of a word, print it
        if (node->isEndOfWord) {
            cout << currentWord << " ";
        }
        
        // Recursively traverse all children
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                printWordsFromNode(node->children[i], currentWord + c);
            }
        }
    }
};

// Test driver program
int main() {
    cout << "=== Trie (Prefix Tree) Implementation Demo ===" << endl << endl;
    
    Trie trie;
    
    // Test insert operation
    cout << "1. Inserting words into the trie..." << endl;
    vector<string> words = {"apple", "app", "application", "apply", "banana", "band", "bandana"};
    
    for (const string& word : words) {
        trie.insert(word);
        cout << "   Inserted: " << word << endl;
    }
    cout << endl;
    
    // Test search operation
    cout << "2. Testing search operation..." << endl;
    vector<string> searchWords = {"app", "apple", "application", "banana", "band", "ban", "xyz"};
    
    for (const string& word : searchWords) {
        bool found = trie.search(word);
        cout << "   Search '" << word << "': " << (found ? "Found" : "Not found") << endl;
    }
    cout << endl;
    
    // Test startsWith operation
    cout << "3. Testing startsWith operation..." << endl;
    vector<string> prefixes = {"app", "ban", "band", "xyz", "a", "b"};
    
    for (const string& prefix : prefixes) {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "   startsWith '" << prefix << "': " << (hasPrefix ? "Yes" : "No") << endl;
    }
    cout << endl;
    
    // Print all words in the trie
    cout << "4. All words currently in the trie:" << endl;
    trie.printAllWords();
    cout << endl;
    
    // Demonstrate the trie structure concept
    cout << "=== Trie Structure Explanation ===" << endl;
    cout << "The trie stores words as follows:" << endl;
    cout << "- Each node represents a character" << endl;
    cout << "- Paths from root to marked nodes represent complete words" << endl;
    cout << "- Common prefixes share the same path" << endl;
    cout << "- Example: 'app', 'apple', 'application' all share the 'app' prefix" << endl;
    
    return 0;
}