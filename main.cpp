#include "CodeEditor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CodeEditor editor;
    editor.setWindowTitle("Code Editor");
    editor.resize(800, 600);
    editor.show();

    return app.exec();
}

