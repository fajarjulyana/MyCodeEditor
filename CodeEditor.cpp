#include "CodeEditor.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QInputDialog>
#include <QLineEdit>
#include <QKeySequence>

// Constructor
CodeEditor::CodeEditor(QWidget *parent)
    : QMainWindow(parent), editor(new QPlainTextEdit(this)), currentFilePath(""), darkModeEnabled(false) {
    setCentralWidget(editor);

    // Add toolbar actions
    QToolBar *toolbar = addToolBar("Toolbar");
    QAction *openAction = toolbar->addAction("Open");
    QAction *saveAction = toolbar->addAction("Save");
    QAction *saveAsAction = toolbar->addAction("Save As");
    QAction *findAction = toolbar->addAction("Find");
    QAction *replaceAction = toolbar->addAction("Replace");
    QAction *darkModeAction = toolbar->addAction("Toggle Dark Mode");

    // Connect actions
    connect(openAction, &QAction::triggered, this, &CodeEditor::openFile);
    connect(saveAction, &QAction::triggered, this, &CodeEditor::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &CodeEditor::saveFileAs);
    connect(findAction, &QAction::triggered, this, &CodeEditor::findText);
    connect(replaceAction, &QAction::triggered, this, &CodeEditor::replaceText);
    connect(darkModeAction, &QAction::triggered, this, &CodeEditor::toggleDarkMode);

    // Keyboard shortcuts
    openAction->setShortcut(QKeySequence::Open);
    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    findAction->setShortcut(QKeySequence::Find);
    replaceAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));

    // Syntax highlighter
    new SyntaxHighlighter(editor->document());
}

// Destructor
CodeEditor::~CodeEditor() {}

// Open File
void CodeEditor::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    QTextStream in(&file);
    editor->setPlainText(in.readAll());
    file.close();
    currentFilePath = fileName;
    setWindowTitle(fileName);
}

// Save File
void CodeEditor::saveFile() {
    if (currentFilePath.isEmpty()) {
        saveFileAs();
    } else {
        QFile file(currentFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot save file");
            return;
        }

        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();
    }
}

// Save File As
void CodeEditor::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File As");
    if (fileName.isEmpty()) return;

    currentFilePath = fileName;
    saveFile();
    setWindowTitle(fileName);
}

// Find Text
void CodeEditor::findText() {
    bool ok;
    QString text = QInputDialog::getText(this, "Find", "Enter text to find:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        if (!editor->find(text)) {
            QMessageBox::information(this, "Find", "Text not found");
        }
    }
}

// Replace Text
void CodeEditor::replaceText() {
    bool ok;
    QString findText = QInputDialog::getText(this, "Find", "Enter text to find:", QLineEdit::Normal, "", &ok);
    if (ok && !findText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, "Replace", "Enter replacement text:", QLineEdit::Normal, "", &ok);
        if (ok) {
            QString content = editor->toPlainText();
            content.replace(findText, replaceText);
            editor->setPlainText(content);
        }
    }
}

// Toggle Dark Mode
void CodeEditor::toggleDarkMode() {
    darkModeEnabled = !darkModeEnabled;

    QPalette palette = editor->palette();
    if (darkModeEnabled) {
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::Text, Qt::white);
        editor->setPalette(palette);
    } else {
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        editor->setPalette(palette);
    }
}

// Syntax Highlighter Constructor
CodeEditor::SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywords = {"int", "float", "if", "else", "while", "return", "class", "public", "private"};
    for (const QString &keyword : keywords) {
        rules.append({QRegularExpression("\\b" + keyword + "\\b"), keywordFormat});
    }

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGreen);
    commentFormat.setFontItalic(true);
    rules.append({QRegularExpression("//[^\n]*"), commentFormat});
}

// Highlight Block
void CodeEditor::SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const auto &rule : rules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

