

#include <iostream>
#include <cstring>
using namespace std;

/* ============================
   Simple TextBuffer
   ============================ */
class TextBuffer {
private:
    char* content;
    int length;
    int capacity;

    void ensureCapacity(int newLen) {
        if (newLen <= capacity) return;

        int newCap = capacity * 2;
        if (newCap < newLen) newCap = newLen;

        char* temp = new char[newCap + 1];
        strcpy(temp, content);

        delete[] content;
        content = temp;
        capacity = newCap;
    }

public:
    TextBuffer(int cap = 20) : length(0), capacity(cap) {
        content = new char[capacity + 1];
        content[0] = '\0';
    }

    // Copy constructor
    TextBuffer(const TextBuffer& other)
        : length(other.length), capacity(other.capacity) {
        content = new char[capacity + 1];
        strcpy(content, other.content);
    }

    // Assignment operator
    TextBuffer& operator=(const TextBuffer& other) {
        if (this == &other) return *this;

        delete[] content;

        length = other.length;
        capacity = other.capacity;
        content = new char[capacity + 1];
        strcpy(content, other.content);

        return *this;
    }

    // Destructor
    ~TextBuffer() {
        delete[] content;
    }

    void append(const char* text) {
        int add = strlen(text);
        ensureCapacity(length + add);
        strcat(content, text);
        length += add;
    }

    void remove(int start, int count) {
        if (start < 0 || start >= length) return;
        if (start + count > length) count = length - start;

        for (int i = start; i <= length - count; i++) {
            content[i] = content[i + count];
        }
        length -= count;
    }

    void display() const {
        cout << content << endl;
    }
};

/* ============================
   Simple TextEditor (Undo)
   ============================ */
class TextEditor {
private:
    TextBuffer current;
    TextBuffer* history;
    int historySize;
    int historyCapacity;

    void saveState() {
        if (historySize == historyCapacity) {
            for (int i = 1; i < historyCapacity; i++)
                history[i - 1] = history[i];

            history[historyCapacity - 1] = current;
        }
        else {
            history[historySize] = current;
            historySize++;
        }
    }

public:
    TextEditor(int cap = 10)
        : current(), historySize(0), historyCapacity(cap) {
        history = new TextBuffer[historyCapacity];
    }

    // Rule of Three
    TextEditor(const TextEditor& other)
        : current(other.current),
          historySize(other.historySize),
          historyCapacity(other.historyCapacity) {
        history = new TextBuffer[historyCapacity];
        for (int i = 0; i < historySize; i++)
            history[i] = other.history[i];
    }

    TextEditor& operator=(const TextEditor& other) {
        if (this == &other) return *this;

        delete[] history;

        current = other.current;
        historySize = other.historySize;
        historyCapacity = other.historyCapacity;

        history = new TextBuffer[historyCapacity];
        for (int i = 0; i < historySize; i++)
            history[i] = other.history[i];

        return *this;
    }

    ~TextEditor() {
        delete[] history;
    }

    void appendText(const char* text) {
        saveState();
        current.append(text);
    }

    void removeText(int start, int count) {
        saveState();
        current.remove(start, count);
    }

    void undo() {
        if (historySize == 0) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        historySize--;
        current = history[historySize];
    }

    void display() const {
        current.display();
    }
};

/* ============================
   MAIN
   ============================ */
int main() {
    TextEditor ed;

    ed.appendText("Hello");
    ed.appendText(" World");
    ed.display();     // Hello World

    ed.removeText(5,1);
    ed.display();     // HelloWorld

    ed.undo();
    ed.display();     // Hello World

    ed.undo();
    ed.display();     // Hello

    ed.undo();
    ed.display();     // (empty)

    return 0;
}