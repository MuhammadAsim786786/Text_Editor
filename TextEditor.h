#include <iostream>
#include <list>
#include <vector>
#include <cctype> 
#include <algorithm>
#include <sstream> 
#include<unordered_map>
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

        while (it != characters.begin() && (prev(it, 1)->ch) != ' ') {
            --it;
        }
        list<Letter>::iterator wordStart = it;

        while (it != characters.end() && (it->ch) != ' ') {
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
        Letter l(ch);
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
        string lowerWord = word;
        for (char& c : lowerWord) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        list<Letter>::iterator it = characters.begin();
        while (it != characters.end()) {
            list<Letter>::iterator wordStart = it;
            bool foundWord = true;

            for (int i = 0; i < lowerWord.size(); ++i) {
                if (it == characters.end() || tolower(it->ch) != lowerWord[i]) {
                    foundWord = false;
                    break;
                }
                ++it;
            }

            if (foundWord) {
                it = characters.erase(wordStart, it);
                characters.insert(it, prefix.begin(), prefix.end());
                characters.insert(it, lowerWord.begin(), lowerWord.end());
            }
            else {
                ++it;
            }
        }
    }

    void AddPostfixToWord(string& word, string& postfix) {
        string lowerWord = word;
        for (char& c : lowerWord) {
            if (c >= 'A' && c <= 'Z') {
                c = tolower(c);
            }
        }

        list<Letter>::iterator it = characters.begin();
        while (it != characters.end()) {
            list<Letter>::iterator wordStart = it;
            bool foundWord = true;

            for (int i = 0; i < lowerWord.size(); ++i) {
                if (it == characters.end() || tolower(it->ch) != lowerWord[i]) {
                    foundWord = false;
                    break;
                }
                ++it;
            }

            if (foundWord) {
                it = characters.erase(wordStart, it);
                characters.insert(it, lowerWord.begin(), lowerWord.end());
                characters.insert(it, postfix.begin(), postfix.end());
            }
            else {
                ++it;
            }
        }
    }

    void FromString(string& lineText) {
        characters.clear();
        for (size_t i = 0; i < lineText.size(); ++i) {
            char ch = lineText[i];
            Letter newLetter;
            newLetter.ch = ch;
            characters.push_back(newLetter);
        }
    }

    string ToString() {
        string result;
        for (list<Letter>::iterator it = characters.begin(); it != characters.end(); ++it) {
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

            for (int i = 0; i <= tempstr.size(); ++i) {
                if (i == tempstr.size() || tempstr[i] == ' ') {
                    if (word == str) {
                        return true;
                    }
                    word = ""; 
                }
                else {
                    word += tempstr[i]; 
                }
            }
        }
        return false; 

    }
    bool findWordNotSensitive(string& str) {
        string lowerStr = str;
        for (int i = 0; i < lowerStr.size(); ++i) {
            if (lowerStr[i] >= 'A' && lowerStr[i] <= 'Z') {
                lowerStr[i] = lowerStr[i] - 'A' + 'a';
            }
        }

        for (vector<Line*>::iterator it = lines.begin(); it != lines.end(); ++it) {
            Line* temp = *it;
            string tempStr = temp->ToString();

            string lowerTempStr = tempStr;
            for (int i = 0; i < lowerTempStr.size(); ++i) {
                if (lowerTempStr[i] >= 'A' && lowerTempStr[i] <= 'Z') {
                    lowerTempStr[i] = lowerTempStr[i] - 'A' + 'a';
                }
            }

            string word = "";
            for (size_t i = 0; i <= lowerTempStr.size(); ++i) {
                if (i == lowerTempStr.size() || lowerTempStr[i] == ' ') {
                    if (word == lowerStr) {
                        return true; 
                    }
                    word = ""; 
                }
                else {
                    word += lowerTempStr[i]; 
                }
            }
        }

        return false; 
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
            offset += lines[i]->ToString().length() + 1; 
        }
        offset += currentCol; 
        return offset;
    }
    string getSpecificPart() {
        string returningString;
        int currentLineIndex = currentRow; 

        if (currentLineIndex < lines.size()) {
            Line* currentLine = lines[currentLineIndex];
            list<Letter>::iterator it = currentLine->characters.begin();
            advance(it, currentCol); 

            while (it != currentLine->characters.end()) {
                returningString += it->ch;
                ++it;
            }

            for (int i = currentLineIndex + 1; i < lines.size(); ++i) {
                returningString += '\n'; 
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

        for (int i = 0; i < str.length(); ++i) {
            if (isupper(str[i])) {
                str[i] = tolower(str[i]);
            }
        }

        while (findWordSenstive(originalWord)) {
            for (int i = 0; i < lines.size(); ++i) {
                lines[i]->AddPrefixToWord(prefix, originalWord);
            }
        }
    }
    void AddPostfixToWord(string str, string postfix) {
        string originalWord = str;

        for (int i = 0; i < str.length(); ++i) {
            if (isupper(str[i])) {
                str[i] = tolower(str[i]);
            }
        }

        while (findWordSenstive(originalWord)) {
            for (int i = 0; i < lines.size(); ++i) {
                lines[i]->AddPostfixToWord(originalWord, postfix);
            }
        }
    }
    void UpdateDocumentFromText( string& fullText) {
        lines.clear();
        string lineText;
        for (int i = 0; i < fullText.size(); ++i) {
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
    void UpdateDocumentFromCursor( string& updatedText) {
        int currentLineIndex = currentRow;

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
        case 'a': { 
            size_t pos = operatingStr.find(findWord);
            if (pos != string::npos) {
                operatingStr.replace(pos, findWord.length(), replaceWord);
            }
            break;
        }
        case 'b': { 
            size_t pos = 0;
            while ((pos = operatingStr.find(findWord, pos)) != string::npos) {
                operatingStr.replace(pos, findWord.length(), replaceWord);
                pos += replaceWord.length();
            }
            break;
        }
        case 'c': {
            string fullText = getAllLines();
            size_t cursorOffset = getCursorOffset(); 
            size_t lastPos = fullText.rfind(findWord, cursorOffset);
            if (lastPos != string::npos) {
                fullText.replace(lastPos, findWord.length(), replaceWord);
                UpdateDocumentFromText(fullText);
            }
            return;
        }
        case 'd': { 
            string fullText = getAllLines();
            size_t cursorOffset = getCursorOffset(); 
            size_t pos = 0;
            while ((pos = fullText.find(findWord, pos)) != string::npos && pos < cursorOffset) {
                fullText.replace(pos, findWord.length(), replaceWord);
                pos += replaceWord.length(); 
            }
            UpdateDocumentFromText(fullText); 
            return;
        }
        }

        UpdateDocumentFromCursor(operatingStr);
    }





  

    unordered_map<char, int> getLetterFrequency( string& word) {
        unordered_map<char, int> frequency;
        for (int i = 0; i < word.size(); ++i) {
            frequency[word[i]]++;
        }
        return frequency;
    }

    bool canFormWord( string& baseWord,  string& targetWord) {
        unordered_map<char, int> baseFreq, targetFreq;

        for (int i = 0; i < baseWord.size(); ++i) {
            baseFreq[baseWord[i]]++;
        }
        for (int i = 0; i < targetWord.size(); ++i) {
            targetFreq[targetWord[i]]++;
        }

        for (unordered_map<char, int>::iterator it = targetFreq.begin(); it != targetFreq.end(); ++it) {
            char letter = it->first;
            int count = it->second;
            if (baseFreq[letter] < count) {
                cout << "Cannot form " << targetWord << " from " << baseWord << endl;
                return false;
            }
        }
        return true;
    }

    vector<string> splitString(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    void wordGame() {
        string document = getAllLines();
        vector<string> words;
        string word = "";

        for (int i = 0; i < document.size(); ++i) {
            if (isspace(document[i])) {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            }
            else {
                word += document[i];
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }

        string bestWord = "";
        int maxSubwords = 0;

        cout << "Extracted words:\n";
        for (int i = 0; i < words.size(); ++i) {
            cout << words[i] << endl;
        }

        for (int i = 0; i < words.size(); ++i) {
            string baseWord = words[i];
            int subwordCount = 0;
            for (int j = 0; j < words.size(); ++j) {
                string targetWord = words[j];
                if (baseWord != targetWord && canFormWord(baseWord, targetWord)) {
                    subwordCount++;
                }
            }


            if (subwordCount > maxSubwords) {
                maxSubwords = subwordCount;
                bestWord = baseWord;
            }
        }

        cout << "Best word: " << bestWord << "\n";
        cout << "Number of subwords: " << maxSubwords << "\n";
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

