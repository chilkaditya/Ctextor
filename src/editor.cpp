# include "editor.hpp"

Editor::Editor(){
    lines.push_back(" ");
    currentText = lines[cursor.getY()];
}

void Editor::handleTextInput(const std::string& input){
    std::string cText = getCurrText();
    cText.insert(cursor.getX(),input);
    lines[cursor.getY()] = cText;
    cursor.setX(cursor.getX() + input.size());
}

void Editor::handleBackspace(){
    if (cursor.getX() > 0) {
        lines[cursor.getY()].erase(cursor.getX() - 1, 1);
        cursor.setX(cursor.getX() - 1);
    } else if (cursor.getY() > 0) {
        cursor.setX(lines[cursor.getY() - 1].size());
        lines[cursor.getY() - 1] += lines[cursor.getY()];
        lines.erase(lines.begin() + cursor.getY());
        cursor.setY(cursor.getY() - 1);
    }
}

void Editor::handleEnter(){
    lines.push_back(" ");
    cursor.setX(0);
    cursor.setY(cursor.getY()+1);
    currentText = lines[cursor.getY()];
}

void Editor::handleLeftArrowKey(){
    if(cursor.getX() > 0){
        cursor.setX(cursor.getX()-1);
    }
    else if(cursor.getY() > 0){
        cursor.setY(cursor.getY()-1);
        cursor.setX(lines[cursor.getY()].size()-1);
        currentText = lines[cursor.getY()];
    }
}

void Editor::handleRightArrowKey(){
    if(cursor.getX() < (int)currentText.size()-1){
        cursor.setX(cursor.getX()+1);
    }
    else if(cursor.getY() < (int)lines.size()-1){
        cursor.setY(cursor.getY()+1);
        cursor.setX(0);
        currentText = lines[cursor.getY()];
    }
}

void Editor::handleUpArrowKey(){
    if(cursor.getY() > 0){
        cursor.setY(cursor.getY()-1);
        int mini = std::min(cursor.getX(),(int)lines[cursor.getY()].size()-1);
        cursor.setX(mini);
        currentText = lines[cursor.getY()];
    }
}

void Editor::handleDownArrowKey(){
    if(cursor.getY() < (int)lines.size()-1){
        cursor.setY(cursor.getY()+1);
        int mini = std::min(cursor.getX(),(int)lines[cursor.getY()].size()-1);
        cursor.setX(mini);
        currentText = lines[cursor.getY()];
    }
}

const std::vector<std::string>& Editor::getLines() const {
    return lines;
}

std::string& Editor:: getCurrText(){
    return lines[cursor.getY()];
}