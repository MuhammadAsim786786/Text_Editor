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
    cin.ignore(); 
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
    cin.ignore(); 
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
    cin.ignore(); 
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
    cin.ignore(); 
    getline(cin, findWord);

    cout << "Enter the replacement word: ";
    string replaceWord;
    getline(cin, replaceWord);

    currentDoc->FindReplaceFromCursor(findWord, replaceWord, option); 
    cout << "Find and Replace operation completed. Press Enter to continue...";
    while (_getch() != 13) {}
}
void findBestWord(Document* currentDoc) {
    currentDoc->wordGame();
   
    while (_getch() != 13) {} 
}


void displayMenu() {
    system("cls"); 
    cout << "Key Combinations and Functions:" << endl;
    cout << "Tab + S: Case-sensitive search" << endl;
    cout << "Tab + D: Case-insensitive search" << endl;
    cout << "Tab + F: Load a file" << endl;
    cout << "Tab + C: Search a sentence" << endl;
    cout << "Tab + B: Search a substring" << endl;
    cout << "Tab + A: Find average word length" << endl;
    cout << "Tab + L: Find longest word length" << endl;
    cout << "Tab + X: Count special characters" << endl;
    cout << "Tab + K: Count substring occurrences" << endl;
    cout << "Tab + P: Add prefix to word" << endl;
    cout << "Tab + O: Add postfix to word" << endl;
    cout << "Tab + I: Find smallest word length" << endl;
    cout << "Tab + R: Find and replace from cursor" << endl;
    cout << "Tab + M: Display this menu" << endl;
    cout << "Press Enter to continue...";

    while (_getch() != 13) {}
}


int main() {
	cout << "Enter the Passcode to enter the Application: " << endl;
	string passcode;
	cin >> passcode;
	if (passcode != "bscs23210") {
		cout << "Invalid Passcode! Application will exit." << endl;
		abort();
    }
    system("cls");

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

            if (d == 0 || d == 224) { 
                d = _getch();
                if (d == 72) { 
                    currentDoc->currentRow = max(0, currentDoc->currentRow - 1);
                }
                else if (d == 80) { 
                    currentDoc->currentRow = min(currentDoc->numOfLines - 1, currentDoc->currentRow + 1);
                }
                else if (d == 77) { 
                    currentDoc->currentCol = min(static_cast<int>(currentDoc->lines[currentDoc->currentRow]->characters.size()), currentDoc->currentCol + 1);
                }
                else if (d == 75) { 
                    currentDoc->currentCol = max(0, currentDoc->currentCol - 1);
                }
                else if (d == 81) { 
                    if (currentDoc->currentRow < currentDoc->numOfLines && currentDoc->currentCol < currentDoc->lines[currentDoc->currentRow]->characters.size()) {
                        editor.ToUpper();
                        gotoRowCol(currentDoc->currentRow, 0);
                        currentDoc->lines[currentDoc->currentRow]->PrintLine();
                    }
                }
                else if (d == 73) {
                    if (currentDoc->currentRow < currentDoc->numOfLines && currentDoc->currentCol < currentDoc->lines[currentDoc->currentRow]->characters.size()) {
                        editor.ToLower();
                        gotoRowCol(currentDoc->currentRow, 0);
                        currentDoc->lines[currentDoc->currentRow]->PrintLine();
                    }
                }
            }
            else if (d == 9) { 
                tabPressed = true;
            }
            else {
                if (tabPressed) {
                    if (d == 'S' || d == 's') { 
                        searchWord(currentDoc, true);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'D' || d == 'd') { 
                        searchWord(currentDoc, false);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'F' || d == 'f') { 
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'C' || d == 'c') { 
                        searchSentence(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'B' || d == 'b') { 
                        searchSubstring(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'A' || d == 'a') { 
                        findAvgWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'L' || d == 'l') { 
                        findLargestWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'X' || d == 'x') { 
                        countSpecialCharacters(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'K' || d == 'k') {
                        substringCount(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'P' || d == 'p') { 
                        addPrefix(currentDoc); 
                        system("cls"); 
                        doc->PrintDocument(); 
                    }
                    
                    else if (d == 'O' || d == 'o') { 
                        addPostfix(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'I' || d == 'i') { 
                        findSmallestWordLength(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'R' || d == 'r') { 
                        findReplaceFromCursor(currentDoc);
                        system("cls");
                        doc->PrintDocument();
                    }
                    else if (d == 'M' || d == 'm') { 
                        displayMenu();
                        system("cls");
                        
                    }
                    else if (d == 'W' || d == 'w') {
                        findBestWord(currentDoc);
                        system("cls"); 
                        doc->PrintDocument();

                    }

                    tabPressed = false;
                }
                else {
                    if (d == 8) { 
                        currentDoc->removeCharacter();
                        system("cls"); 
                        doc->PrintDocument();
                    }
                    else if (d == 13) { 
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
