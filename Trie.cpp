#include <iostream>
#include <string>
using namespace std;

class TrieNode {
private:
  void ChildrenInitializer() {
    for (int i = 0; i < 26; i++) {
      this->ChildrenPresent[i] = false;
      this->Children[i] = NULL;
    }
  }

public:
  char Value;
  TrieNode **Children;
  bool *ChildrenPresent;
  bool TerminalNode;

  TrieNode() {
    this->Children = new TrieNode *[26];
    this->ChildrenPresent = new bool[26];
    this->ChildrenInitializer();
    this->TerminalNode = false;
  }

  TrieNode(char value) {
    this->Value = value;
    this->Children = new TrieNode *[26];
    this->ChildrenPresent = new bool[26];
    this->ChildrenInitializer();
    this->TerminalNode = false;
  }

  ~TrieNode() {
    delete[] this->Children;
    delete[] this->ChildrenPresent;
    this->TerminalNode = false;
  }
};

class Trie {
private:
  TrieNode *trie;
  int count;

  void DeleteTrie(TrieNode *trie) {
    for (int i = 0; i < 26; i++) {
      if (trie->ChildrenPresent[i]) {
        this->DeleteTrie(trie->Children[i]);
      }
    }

    delete trie;
  }

  void InsertWord(TrieNode *trie, string word, int index = 0) {
    if (index == word.length()) {
      return;
    }

    char letter = word[index];
    int position = letter - 'A';
    if (!(trie->ChildrenPresent[position])) {
      trie->Children[position] = new TrieNode();
      trie->Children[position]->Value = letter;
      trie->ChildrenPresent[position] = true;

      if (index == (word.length() - 1)) {
        trie->Children[position]->TerminalNode = true;
      }
    }

    this->InsertWord(trie->Children[position], word, index + 1);
  }

  bool SearchWord(TrieNode *trie, string word, int index = 0) {
    char letter = word[index];
    int position = letter - 'A';

    if (trie->ChildrenPresent[position]) {
      if (index == (word.length() - 1)) {
        if (trie->Children[position]->TerminalNode) {
          return true;
        } else {
          return false;
        }
      } else {
        return SearchWord(trie->Children[position], word, index + 1);
      }
    } else {
      return false;
    }
  }

  bool DeleteWord(TrieNode *trie, string word, int index = 0) {
    char letter = word[index];
    int position = letter - 'A';

    if (trie->ChildrenPresent[position]) {
      if (index == (word.length() - 1)) {
        if (trie->Children[position]->TerminalNode) {
          trie->Children[position]->TerminalNode = false;
          return true;
        } else {
          return false;
        }
      } else {
        return DeleteWord(trie->Children[position], word, index + 1);
      }
    } else {
      return false;
    }
  }

  void PrintTrie(TrieNode *trie, string word = "") {
    if (trie->TerminalNode) {
      cout << word << endl;
    }

    for (int i = 0; i < 26; i++) {
      if (trie->ChildrenPresent[i]) {
        word.push_back(trie->Children[i]->Value);
        this->PrintTrie(trie->Children[i], word);
        word.pop_back();
      }
    }
  }

public:
  Trie() {
    this->trie = new TrieNode('\0');
    this->count = 0;
  }

  ~Trie() { this->DeleteTrie(this->trie); }

  void Insert(string word) {
    if (word.empty()) {
      return;
    }

    if (!(this->Search(word))) {
      this->count++;
      this->InsertWord(this->trie, word);
    } else {
      return;
    }
  }

  bool Search(string word) {
    if (word.empty()) {
      return false;
    }

    return this->SearchWord(this->trie, word);
  }

  bool Delete(string word) {
    if (word.empty()) {
      return false;
    }

    if (this->Search(word)) {
      this->count--;
      return this->DeleteWord(this->trie, word);
    } else {
      return false;
    }
  }

  inline int size() { return this->count; }

  void Print() { this->PrintTrie(this->trie); }
};

int main() {
  Trie *dictionary = new Trie();
  dictionary->Insert("KEY");
  dictionary->Insert("KEYPASS");
  dictionary->Insert("KEYWORD");
  dictionary->Insert("KEYBOARD");

  cout << "Is KEY Present: " << dictionary->Search("KEY") << endl;
  cout << "Is KEYUP Present: " << dictionary->Search("KEYUP") << endl;
  cout << "Is KEYPASS Present: " << dictionary->Search("KEYPASS") << endl;
  cout << "Is KEYWORD Present: " << dictionary->Search("KEYWORD") << endl;
  cout << "Is KEYBOARD Present: " << dictionary->Search("KEYBOARD") << endl;
  // cout << "Deleting KEYWORD...: " << dictionary->Delete("KEYWORD") << endl;
  cout << "Is KEYWORD Present: " << dictionary->Search("KEYWORD") << endl;
  cout << endl;

  cout << "Printing Trie: " << endl;
  dictionary->Print();

  delete dictionary;
  return 0;
}