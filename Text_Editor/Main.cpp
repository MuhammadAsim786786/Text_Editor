#include <conio.h>
#include <iostream>
#include <string>
#include "TextEditor.h"
#include <windows.h>

using namespace std;

void gotoRowCol(int rpos, int cpos) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int xpos = cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void searchWord(Document* currentDoc, bool caseSensitive) {
    cout << "\nEnter the word to search (" << (caseSensitive ? "case-sensitive" : "case-insensitive") << "): ";
    string searchWord;
    cin >> searchWord;

    bool found = caseSensitive ? currentDoc->findWordSenstive(searchWord) : currentDoc->findWordNotSensitive(searchWord);

    if (found) {
        cout << "Word found!" << endl;
    }
    else {
        cout << "Word not found." << endl;
    }
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void searchSentence(Document* currentDoc) {
    cout << "\nEnter the sentence to search: ";
    string searchSentence;
    cin.ignore(); // Clear the input buffer
    getline(cin, searchSentence);

    bool found = currentDoc->findSentence(searchSentence);

    if (found) {
        cout << "Sentence found!" << endl;
    }
    else {
        cout << "Sentence not found." << endl;
    }
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void searchSubstring(Document* currentDoc) {
    cout << "\nEnter the substring to search: ";
    string searchSubstring;
    cin.ignore(); // Clear the input buffer
    getline(cin, searchSubstring);

    bool found = currentDoc->findSubStr(searchSubstring);

    if (found) {
        cout << "Substring found!" << endl;
    }
    else {
        cout << "Substring not found." << endl;
    }
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void findAvgWordLength(Document* currentDoc) {
    currentDoc->findAvgWordLength();
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void findLargestWordLength(Document* currentDoc) {
    currentDoc->largestWordLength();
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}
void findSmallestWordLength(Document* currentDoc) {
    currentDoc->findSmallestWordLength();
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void countSpecialCharacters(Document* currentDoc) {
    currentDoc->specialCharacterCount();
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}

void substringCount(Document* currentDoc) {
    cout << "\nEnter the substring to count: ";
    string searchSubstring;
    cin.ignore(); // Clear the input buffer
    getline(cin, searchSubstring);

    currentDoc->SubstringCount(searchSubstring);
    cout << "Press Enter to continue...";
    while (_getch() != 13) {}
}
void addPrefix(Document* currentDoc) {
    cout << "\nEnter the word to add prefix to: "; 
    string word; 
    
    getline(cin, word);
    cout << "Enter the prefix to add: "; 
    string prefix; getline(cin, prefix);
    currentDoc->AddPrefixToWord(word, prefix);
    cout << "Prefix added. Press Enter to continue...";
    
    while (_getch() != 13) {} }
void addPostfix(Document* currentDoc) {
    cout << "\nEnter the word to add prefix to: ";
    string word;

    getline(cin, word);
    cout << "Enter the prefix to add: ";
    string prefix; 
    getline(cin, prefix);
    currentDoc->AddPostfixToWord(word, prefix);
    cout << "Prefix added. Press Enter to continue...";

    while (_getch() != 13) {}
}
void findReplaceFromCursor(Document* currentDoc) {
    cout << "\nChoose an option for Find and Replace:" << endl;
    cout << "a. Replace Next" << endl;
    cout << "b. Replace All Next" << endl;
    cout << "c. Replace Previous" << endl;
    cout << "d. Replace All Previous" << endl;
    cout << "Enter your choice: ";
    char option;
    cin >> option;

    cout << "Enter the word to find: ";
    string findWord;
    cin.ignore(); // Clear input buffer
    getline(cin, findWord);

    cout << "Enter the replacement word: ";
    string replaceWord;
    getline(cin, replaceWord);

    currentDoc->FindReplaceFromCursor(findWord, replaceWord, option); // Call the Document method
    cout << "Find and Replace operation completed. Press Enter to continue...";
    while (_getch() != 13) {}
}


int main() {
    TextEditor editor;
    Document* doc = new Document();
    Line* line = new Line();
    doc->AddLine(line);
    editor.AddDocument(doc);

    int d;
    bool tabPressed = false;
    const int maxLineLength = 50;

    while (true) {
        if (_kbhit()) {
            d = _getch();

            Document* currentDoc = editor.GetCurrentDocument();

            if (d == 0 || d == 224) { // Special key
                d = _getch();
                if (d == 72) { // Arrow Up
                    currentDoc->currentRow = max(0, currentDoc->currentRow - 1);
                }
                else if (d == 80) { // Arrow Down
                    currentDoc->currentRow = min(currentDoc->numOfLines - 1, currentDoc->currentRow + 1);
                }
                else if (d == 77) { // Arrow Right
                    currentDoc->currentCol = min(static_cast<int>(currentDoc->lines[currentDoc->currentRow]->characters.size()), currentDoc->currentCol + 1);
                }
                else if (d == 75) { // Arrow Left
                    currentDoc->currentCol = max(0, currentDoc->currentCol - 1);
                }
                else if (d == 81) { // Page Down key (scan code 81)
                    if (currentDoc->currentRow < currentDoc->numOfLines && currentDoc->currentCol < currentDoc->lines[currentDoc->currentRow]->characters.size()) {
                        editor.ToUpper(); // Call the editor's ToUpper
                        gotoRowCol(currentDoc->currentRow, 0);
                        currentDoc->lines[currentDoc->currentRow]->PrintLine();
                    }
                }
                else if (d == 73) { // Page Up key (scan code 73)
                    if (currentDoc->currentRow < currentDoc->numOfLines && currentDoc->currentCol < currentDoc->lines[currentDoc->currentRow]->characters.size()) {
                        editor.ToLower();
                        gotoRowCol(currentDoc->currentRow, 0);
                        currentDoc->lines[currentDoc->currentRow]->PrintLine();
                    }
                }
            }
            else if (d == 9) { // Tab key (keycode 9)
                tabPressed = true;
            }
            else {
                if (tabPressed) {
                    if (d == 'S' || d == 's') { // Tab + S for case-sensitive search
                        searchWord(currentDoc, true);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'D' || d == 'd') { // Tab + D for case-insensitive search
                        searchWord(currentDoc, false);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'F' || d == 'f') { // Tab + F to load a file
                        // loadFile(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'C' || d == 'c') { // Tab + C to search a sentence
                        searchSentence(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'B' || d == 'b') { // Tab + B to search a substring
                        searchSubstring(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'A' || d == 'a') { // Tab + A to find average word length
                        findAvgWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'L' || d == 'l') { // Tab + L to find longest word length
                        findLargestWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'X' || d == 'x') { // Tab + X to count special characters
                        countSpecialCharacters(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'K' || d == 'k') { // Tab + K to count substring occurrences
                        substringCount(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'P' || d == 'p') { // Tab + P to add prefix to word
                        addPrefix(currentDoc); 
                        system("cls"); 
                        doc->PrintDocument(); 
                    }
                    else if (d == 'P' || d == 'P') { // Tab + P to add prefix to word
                        addPrefix(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'O' || d == 'o') { // Tab + P to add prefix to word
                        addPostfix(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'I' || d == 'i') { // Tab + P to add prefix to word
                        findSmallestWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'R' || d == 'r') { // Tab + R for Find and Replace from Cursor
                        findReplaceFromCursor(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }

                    tabPressed = false;
                }
                else {
                    if (d == 8) { // Backspace key (keycode 8)
                        currentDoc->removeCharacter();
                        system("cls"); // Clear screen to reflect changes
                        doc->PrintDocument();
                    }
                    else if (d == 13) { // Enter key
                        currentDoc->currentRow++;
                        currentDoc->currentCol = 0;
                        Line* newLine = new Line();
                        currentDoc->AddLine(newLine);
                    }
                    else {
                        char ch = char(d);
                        currentDoc->lines[currentDoc->currentRow]->AddCharacter(ch);
                        cout << ch;
                        currentDoc->currentCol++;
                        if (currentDoc->currentCol >= maxLineLength) {
                            currentDoc->currentRow++;
                            currentDoc->currentCol = 0;
                            Line* newLine = new Line();
                            currentDoc->AddLine(newLine);
                        }
                    }
                }
            }
            gotoRowCol(currentDoc->currentRow, currentDoc->currentCol);
        }
    }

    return 0;
}
