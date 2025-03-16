#include "ladder.h"

using namespace std;

int main() {
    string start_word, end_word;

    cout << "Enter the start word: ";
    cin >> start_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

    if (start_word == end_word) {
        cout << "The start and end words cannot be the same!" << endl;
        return 1;
    }

    set<string> word_list;
    load_words(word_list, "words.txt");

    if (word_list.find(end_word) == word_list.end()) {
        cout << "The end word is not in the dictionary!" << endl;
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    if (ladder.empty()) {
        cout << "No word ladder found!" << endl;
    } else {
        cout << "Word Ladder: ";
        print_word_ladder(ladder);
    }

    return 0;
}