# CodeEditor

CodeEditor is a simple text editor built using C++ and Qt5. It includes syntax highlighting, a dark mode toggle, and common text editing functionalities like Find, Replace, Save, and Save As. The editor is designed for basic code editing and showcases how to implement a GUI application with Qt.

---

## Features

- **Syntax Highlighting**:
  - Supports highlighting for common C++ keywords and comments.
- **Dark Mode**:
  - Toggle between light and dark themes.
- **File Operations**:
  - Open, Save, and Save As functionality for text files.
- **Find and Replace**:
  - Simple find and replace dialog for editing text.
- **Keyboard Shortcuts**:
  - **Open**: `Ctrl + O`
  - **Save**: `Ctrl + S`
  - **Save As**: `Ctrl + Shift + S`
  - **Find**: `Ctrl + F`
  - **Replace**: `Ctrl + R`

---

## Prerequisites

To build and run CodeEditor, you need:

1. **Qt5 Development Tools**:
   - Install using your package manager:
     ```bash
     sudo apt update
     sudo apt install qt5-default qttools5-dev-tools
     ```
2. **G++ Compiler**:
   - Install with:
     ```bash
     sudo apt install build-essential
     ```

---

## Build Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/fajarjulyana/MyCodeEditor.git
   cd CodeEditor
   ```

2. **Generate the MOC File**:
   Use `moc` to process the header file:
   ```bash
   moc -o moc_CodeEditor.cpp CodeEditor.h
   ```

3. **Compile the Code**:
   ```bash
   g++ -fPIC main.cpp CodeEditor.cpp moc_CodeEditor.cpp -o CodeEditor `pkg-config --cflags --libs Qt5Widgets`
   ```

4. **Run the Program**:
   ```bash
   ./CodeEditor
   ```

---

## Usage

1. Launch the application using the command above.
2. Use the toolbar or keyboard shortcuts to perform operations:
   - Open a file: `Ctrl + O`
   - Save the current file: `Ctrl + S`
   - Save the file as: `Ctrl + Shift + S`
   - Find text: `Ctrl + F`
   - Replace text: `Ctrl + R`
   - Toggle dark mode from the toolbar.

---

## Dark Mode

The editor includes a toggleable dark mode. Click the "Toggle Dark Mode" button in the toolbar to switch between light and dark themes.

---

## License

This project is licensed under the MIT License.


## Contributing

Feel free to fork this repository, submit issues, or create pull requests to improve the project.

