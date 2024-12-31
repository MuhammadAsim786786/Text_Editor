#include <iostream>
#include <list>
#include <vector>
#include <cctype> 
#include <algorithm>
#include <sstream> 
using namespace std;

struct Letter {
    char ch;           
    Letter* next;     
    Letter(char c) : ch(c) {}
    Letter() {
		ch = '\0';
		next = nullptr;
    }
};

class Line {
public:
    int size;                  
    list<Letter> characters;   

    
    void ToUpper(int cursorPos) {
        list<Letter>::iterator it = characters.begin();
        advance(it, cursorPos); 

      
        while (it != characters.begin() && (prev(it, 1)->ch)!=' ') {
            --it;
        }
        list<Letter>::iterator wordStart = it; 


        while (it != characters.end() && (it->ch)!=' ') {
            if (it->ch >= 'a' && it->ch <= 'z') {
                it->ch = it->ch - ('a' - 'A'); 
            }
            ++it;
        }
    }
    void ToLower(int cursorPos) {
        list<Letter>::iterator it = characters.begin();
        advance(it, cursorPos);

      
        while (it != characters.begin() && (prev(it, 1)->ch) != ' ') {
            --it;
        }
        list<Letter>::iterator wordStart = it;

        while (it != characters.end() && (it->ch) != ' ') {
            if (it->ch >= 'A' && it->ch <= 'Z') {
                it->ch = it->ch + ('a' - 'A'); 
            }
            ++it;
        }
    }
    void AddCharacter(char ch) {
        Letter l(ch); // Use the new constructor
        characters.push_back(l);
        size++;
    }
    


    void PrintLine() {
        for (list<Letter>::iterator it = characters.begin(); it != characters.end(); ++it) {
            cout << it->ch;
        }
        cout << endl;
    }
    void AddPrefixToWord(string& prefix, string& word) {
        // Convert the target word to lowercase
        string lowerWord = word;
        for (char& c : lowerWord) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        list<Letter>::iterator it = characters.begin();
        while (it != characters.end()) {
            // Find the start of the word
            list<Letter>::iterator wordStart = it;
            bool foundWord = true;

            for (int i = 0; i < lowerWord.size(); ++i) {
                if (it == characters.end() || tolower(it->ch) != lowerWord[i]) {
                    foundWord = false;
                    break;
                }
                ++it;
            }

            // If the word is found, replace it with prefix + word
            if (foundWord) {
                it = characters.erase(wordStart, it);              // Remove the word
                characters.insert(it, prefix.begin(), prefix.end()); // Insert the prefix
                characters.insert(it, lowerWord.begin(), lowerWord.end()); // Re-insert the original word
            }
            else {
                // Move to the next character if no match is found
                ++it;
            }
        }
    }

    void AddPostfixToWord(string& word, string& postfix) {
        // Convert the target word to lowercase for comparison
        string lowerWord = word;
        for (char& c : lowerWord) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        list<Letter>::iterator it = characters.begin();
        while (it != characters.end()) {
            // Find the start of the word
            list<Letter>::iterator wordStart = it;
            bool foundWord = true;

            for (int i = 0; i < lowerWord.size(); ++i) {
                if (it == characters.end() || tolower(it->ch) != lowerWord[i]) {
                    foundWord = false;
                    break;
                }
                ++it;
            }

            // If the word is found, append the postfix
            if (foundWord) {
                it = characters.erase(wordStart, it);               // Remove the word
                characters.insert(it, lowerWord.begin(), lowerWord.end()); // Re-insert the word
                characters.insert(it, postfix.begin(), postfix.end());     // Append the postfix
            }
            else {
                // Move to the next character if no match is found
                ++it;
            }
        }
    }
    void FromString(string& lineText) {
        characters.clear(); // Clear the existing list of characters
        for (size_t i = 0; i < lineText.size(); ++i) {
            char ch = lineText[i];
            Letter newLetter;
            newLetter.ch = ch; // Set the character
            characters.push_back(newLetter); // Add the Letter object to the list
        }
    }

    string ToString() { 
        string result; 
        for (list<Letter>::iterator it = characters.begin(); it != characters.end(); ++it) 
        { 
            result += it->ch; 
        }
        return result; 
    }
};

class Document {
public:
    int currentRow = 0;    
    int currentCol = 0;     
    int numOfLines = 0;    
    vector<Line*> lines;    

   
    void ToUpper() {
        if (currentRow >= 0 && currentRow < numOfLines) {
            lines[currentRow]->ToUpper(currentCol); 
        }
    }
	void ToLower() {
		if (currentRow >= 0 && currentRow < numOfLines) {
			lines[currentRow]->ToLower(currentCol);
		}
	}
    void AddLine(Line* line) {
        lines.push_back(line);
        numOfLines++;
    }

    bool findWordSenstive(string& str) {
        for (vector<Line*>::iterator iteratoring = lines.begin(); iteratoring != lines.end(); iteratoring++) {
            Line* temp = (*iteratoring);
            string tempstr = temp->ToString();
            string word = "";

            // Iterate through the line character by character
            for (int i = 0; i <= tempstr.size(); ++i) {
                if (i == tempstr.size() || tempstr[i] == ' ') {
                    // Word boundary detected
                    if (word == str) {
                        return true; // Match found for a complete word
                    }
                    word = ""; // Reset the word
                }
                else {
                    word += tempstr[i]; // Build the current word
                }
            }
        }
        return false; // No match found

    }
    bool findWordNotSensitive(string& str) {
        // Convert the target word to lowercase
        string lowerStr = str;
        for (int i = 0; i < lowerStr.size(); ++i) {
            if (lowerStr[i] >= 'A' && lowerStr[i] <= 'Z') {
                lowerStr[i] = lowerStr[i] - 'A' + 'a';
            }
        }

        // Iterate through all lines in the document
        for (vector<Line*>::iterator it = lines.begin(); it != lines.end(); ++it) {
            Line* temp = *it;
            string tempStr = temp->ToString();

            // Convert the line to lowercase
            string lowerTempStr = tempStr;
            for (int i = 0; i < lowerTempStr.size(); ++i) {
                if (lowerTempStr[i] >= 'A' && lowerTempStr[i] <= 'Z') {
                    lowerTempStr[i] = lowerTempStr[i] - 'A' + 'a';
                }
            }

            // Process the line word by word
            string word = "";
            for (size_t i = 0; i <= lowerTempStr.size(); ++i) {
                if (i == lowerTempStr.size() || lowerTempStr[i] == ' ') {
                    // Word boundary detected
                    if (word == lowerStr) {
                        return true; // Found a match
                    }
                    word = ""; // Reset the word
                }
                else {
                    word += lowerTempStr[i]; // Build the word
                }
            }
        }

        return false; // No match found
    }

    string getAllLines() {
        string returningString;
        for (vector<Line*>::iterator iteratring = lines.begin(); iteratring != lines.end(); iteratring++)
        {
            returningString += (*iteratring)->ToString() + '\n';
        }
        return returningString;
    }
    int getCursorOffset() {
        int offset = 0;
        for (int i = 0; i < currentRow; ++i) {
            offset += lines[i]->ToString().length() + 1; // Add 1 for newline
        }
        offset += currentCol; // Add the column offset
        return offset;
    }
    string getSpecificPart() {
        string returningString;
        int currentLineIndex = currentRow; // Start from the current row

        // Get the remaining part of the current line from the current cursor column
        if (currentLineIndex < lines.size()) {
            Line* currentLine = lines[currentLineIndex];
            list<Letter>::iterator it = currentLine->characters.begin();
            advance(it, currentCol); // Move to the current column in the line

            // Append the remaining part of the current line to the returning string
            while (it != currentLine->characters.end()) {
                returningString += it->ch;
                ++it;
            }

            // Append subsequent lines
            for (int i = currentLineIndex + 1; i < lines.size(); ++i) {
                returningString += '\n'; // Add a newline between lines
                returningString += lines[i]->ToString();
            }
        }

        return returningString;
    }

    bool findSentence(string str) {
		string wholeText = getAllLines();
        if (wholeText.find(str) != string::npos) {
            return true;
        }
        return false;
    }

    string toLowerCase(const string& str) {
        string lowerStr = str;
        for (size_t i = 0; i < lowerStr.size(); ++i) {
            if (lowerStr[i] >= 'A' && lowerStr[i] <= 'Z') {
                lowerStr[i] = lowerStr[i] + ('a' - 'A');
            }
        }
        return lowerStr;
    }

    bool findSubStr(string substring) {
        substring = toLowerCase(substring); 

        for (vector<Line*>::iterator iterating = lines.begin(); iterating != lines.end(); iterating++) {
            string findingString = toLowerCase((*iterating)->ToString()); 
            string word = "";
            for (int i = 0; i <= findingString.size(); ++i) { 
                if (i == findingString.size() || findingString[i]==' ') {
                    if (word == substring) {
                        return true; 
                    }
                    word = ""; 
                }
                else {
                    word += findingString[i];
                }
            }
        }

        return false;
    }
    void findAvgWordLength() {
        string wholeDocument = getAllLines();
		int totalChar = 0;
		int totalWords = 0;
        for (int i = 0; i < wholeDocument.length(); i++)
        {
            if (wholeDocument[i] == ' ') {
                totalWords++;
            }
            totalChar++;
        }
      
        if (!wholeDocument.empty()) {
            totalWords++;
        }

        if (totalWords == 0) {
            cout << "No words found in the document." << endl;
            return;
        }

        double avgWordLength = static_cast<double>(totalChar) / totalWords;
        cout << "Average Word Length: " << avgWordLength << endl;
    }
    void largestWordLength() {
        string wholeDocument = getAllLines();
        int maxWordLength = 0;
        int currentLength = 0;

        for (int i = 0; i <= wholeDocument.length(); ++i) {
            if (i == wholeDocument.length() || wholeDocument[i] == ' ') {
                
                maxWordLength = max(maxWordLength, currentLength);
                currentLength = 0; 
            }
            else {
                currentLength++; 
            }
        }

        cout << "Longest Word Length: " << maxWordLength << endl;
    }
    void findSmallestWordLength() {
        string wholeDocument = getAllLines();
        int maxWordLength = INT_MAX;
        int currentLength = 0;

        for (int i = 0; i <= wholeDocument.length(); ++i) {
            if (i == wholeDocument.length() || wholeDocument[i] == ' ') {

                maxWordLength = min(maxWordLength, currentLength);
                currentLength = 0;
            }
            else {
                currentLength++;
            }
        }

        cout << "Smallest Word Length: " << maxWordLength << endl;
    }
    void specialCharacterCount() {
        int count = 0;
        string wholeDocument = getAllLines();
        for (int i = 0; i < wholeDocument.length(); ++i) {
            if (!isalnum(wholeDocument[i]) && wholeDocument[i] != ' '&&wholeDocument[i]!='\n') {
                count++;
            }

        }
        cout << "Number of Special Characters: " << count << endl;
    }
    void SubstringCount(string substring) {
        int count = 0;
        for (vector<Line*>::iterator it = lines.begin(); it != lines.end(); ++it) {
            string lineStr = (*it)->ToString();
            int temp = lineStr.find(substring, 0);
            while (temp != string::npos) {
                count++;
                temp = lineStr.find(substring, temp + 1);
            }
        }
		cout << "SubStringCount: " << count << endl;
    }
    void removeCharacter() {
        if (currentRow < 0 || currentRow >= numOfLines) return;

        Line* line = lines[currentRow];
        if (currentCol > 0 && currentCol <= line->size) {
            list<Letter>::iterator it = line->characters.begin();
            advance(it, currentCol - 1);
            line->characters.erase(it);
            line->size--;
            currentCol--;
        }
        else if (currentCol == 0 && currentRow > 0) {
            currentCol = lines[currentRow - 1]->size;
            lines[currentRow - 1]->characters.splice(lines[currentRow - 1]->characters.end(), line->characters);
            lines.erase(lines.begin() + currentRow);
            numOfLines--;
            currentRow--;
        }
    }
    void AddPrefixToWord(string str, string prefix) {
        string originalWord = str;

        // Convert the target word to lowercase for case-sensitive matching
        for (char& c : str) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        // Keep adding the prefix until the word is no longer found
        while (findWordSenstive(originalWord)) {
            for (Line* line : lines) {
                line->AddPrefixToWord(prefix, originalWord);
            }
        }
    }
    void AddPostfixToWord(string str, string postfix) {
        string originalWord = str;

        // Convert the target word to lowercase for case-sensitive matching
        for (char& c : str) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        // Keep adding the postfix until the word is no longer found
        while (findWordSenstive(originalWord)) {
            for (Line* line : lines) {
                line->AddPostfixToWord(originalWord, postfix);
            }
        }
    }
    void UpdateDocumentFromText( string& fullText) {
        lines.clear();
        string lineText;
        for (size_t i = 0; i < fullText.size(); ++i) {
            char ch = fullText[i];
            if (ch == '\n') {
                Line* newLine = new Line();
                newLine->FromString(lineText);
                lines.push_back(newLine);
                lineText.clear();
            }
            else {
                lineText += ch;
            }
        }
        if (!lineText.empty()) {
            Line* newLine = new Line();
            newLine->FromString(lineText);
            lines.push_back(newLine);
        }
    }
    void UpdateDocumentFromCursor(const string& updatedText) {
        size_t currentLineIndex = currentRow;

        stringstream ss(updatedText);
        string lineText;
        while (getline(ss, lineText)) {
            if (currentLineIndex < lines.size()) {
                lines[currentLineIndex]->FromString(lineText);
            }
            else {
                Line* newLine = new Line();
                newLine->FromString(lineText);
                lines.push_back(newLine);
            }
            ++currentLineIndex;
        }
    }

    
    void FindReplaceFromCursor(string findWord, string replaceWord, char option) {
        string operatingStr = getSpecificPart();

        switch (option) {
        case 'a': { // Replace Next Occurrence
            size_t pos = operatingStr.find(findWord);
            if (pos != string::npos) {
                operatingStr.replace(pos, findWord.length(), replaceWord);
            }
            break;
        }
        case 'b': { // Replace All Next Occurrences
            size_t pos = 0;
            while ((pos = operatingStr.find(findWord, pos)) != string::npos) {
                operatingStr.replace(pos, findWord.length(), replaceWord);
                pos += replaceWord.length(); // Move past the replaced word
            }
            break;
        }
        case 'c': { // Replace Previous Occurrence
            string fullText = getAllLines();
            size_t cursorOffset = getCursorOffset(); // Get cursor's position in the full text
            size_t lastPos = fullText.rfind(findWord, cursorOffset);
            if (lastPos != string::npos) {
                fullText.replace(lastPos, findWord.length(), replaceWord);
                UpdateDocumentFromText(fullText); // Rebuild document
            }
            return;
        }
        case 'd': { // Replace All Previous Occurrences
            string fullText = getAllLines();
            size_t cursorOffset = getCursorOffset(); // Get cursor's position in the full text
            size_t pos = 0;
            while ((pos = fullText.find(findWord, pos)) != string::npos && pos < cursorOffset) {
                fullText.replace(pos, findWord.length(), replaceWord);
                pos += replaceWord.length(); // Move past the replaced word
            }
            UpdateDocumentFromText(fullText); // Rebuild document
            return;
        }
        }

        // Update the document with the modified text
        UpdateDocumentFromCursor(operatingStr);
    }


    void PrintDocument() {
        for (int i = 0; i < numOfLines; i++) {
            lines[i]->PrintLine();
        }
    }
};


class TextEditor {
public:
    vector<Document*> documents; 
    int currentDocIndex = 0;     

    void ToUpper() {
        if (currentDocIndex >= 0 && currentDocIndex < documents.size()) {
            documents[currentDocIndex]->ToUpper(); 
        }
    }
	void ToLower() {
        if (currentDocIndex >= 0 && currentDocIndex < documents.size()) {
            documents[currentDocIndex]->ToLower();
        }
    }

    void AddDocument(Document* doc) {
        documents.push_back(doc);
    }

    void PrintCurrentDocument() {
        if (currentDocIndex >= 0 && currentDocIndex < documents.size()) {
            documents[currentDocIndex]->PrintDocument();
        }
    }

    Document* GetCurrentDocument() {
        if (currentDocIndex >= 0 && currentDocIndex < documents.size()) {
            return documents[currentDocIndex];
        }
        return nullptr;
    }
};

