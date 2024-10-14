# SDL2 Text Editor Application : CTextor

## Introduction

This is a simple text editor built using SDL2 and SDL_ttf libraries, designed to demonstrate basic text editing capabilities with cursor management and text rendering. The application allows users to:
- Enter text.
- Move the cursor around using the arrow keys.
- Insert new lines with the "Enter" key.
- Delete characters with the "Backspace" key.

The text editor can be extended to include more advanced features like syntax highlighting, file handling (open, save), copy-paste functionality, and more.

## Features
- **Basic Text Editing**: Enter, edit, and delete text.
- **Cursor Movement**: Use the arrow keys to navigate through the text.
- **Multi-line Support**: Supports writing across multiple lines.
- **Cross-Platform**: Can run on Windows, macOS, and Linux with proper SDL2 setup.

## Setup and Build on Your Local Machine

### Prerequisites

Before building the project, ensure that the following are installed on your machine:

1. **SDL2**: The Simple DirectMedia Layer library for handling graphics and input.
2. **SDL2_ttf**: The SDL extension for rendering TrueType fonts.
3. **CMake**: Used as the build system to compile the project(you can ignore).
4. **A C++ Compiler**: Such as GCC or MinGW (for Windows).
5. Make sure that you can access the **SDL2** and **SDL2_ttf** libraries.

### Installation Steps

#### 1. Fork the repository
A 'fork' is a remote (online) copy of a repository. After a fork is made, it can be edited freely without affecting the original repository.
Tip: Only create a fork if you want to edit the code. If you just want to compile then you can skip creating the fork and move straight to Clone the repository.

#### 2. Clone the Repository
First create a new project folder
then, clone the repository to your local machine:

```bash
mkdir your_project_folder
cd your_project_folder
#If you fork before then do this
git clone https://github.com/chilkaditya/your_username/Ctextor.git
#else you just simple clone it from oficial repo
git clone https://github.com/chilkaditya/Ctextor.git
#go to working directory
cd Ctextor
```
#### 3.Set the remote
```bash
# If you cloned your fork earlier:
git remote add upstream https://github.com/chilkaditya/Ctextor.git
git remote set-url upstream --push disabled  # Prevent accidental push to official repo (team members only)
git pull upstream master                     # Get latest code from official repo.
git branch -u upstream/master                # Track the official master branch instead of your fork's master branch
# If you cloned the official repo:
git remote set-url origin --push disabled    # Prevent accidental push to official repo (team members only)
```

### Build & Run
```bash
cd Ctextor
# if you using make for building then use below command
make
./prog1.exe
# otherwise
g++ editor.cpp -o prog1 -lmingw32 -lSDL2main -lSDL2 -lSDL2_tt 
./prog1.exe
```