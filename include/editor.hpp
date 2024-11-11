#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <string>
#include "cursor.hpp"

class Editor {
public:
    Cursor cursor;
    Editor();
    void handleTextInput(const std::string& input);
    void handleBackspace();
    void handleEnter();
    void handleLeftArrowKey();
    void handleRightArrowKey();
    void handleUpArrowKey();
    void handleDownArrowKey();
    const std::vector<std::string>& getLines() const;
    std::string& getCurrText();

private:
    std::vector<std::string> lines;
    std::string currentText;
    
};

#endif //EDIOR_H