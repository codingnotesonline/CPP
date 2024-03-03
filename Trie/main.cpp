#include "Trie.cpp"
#include <iostream>
using namespace std;

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