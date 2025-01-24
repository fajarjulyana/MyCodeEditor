#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextCharFormat>
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class CodeEditor : public QMainWindow {
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor();

private slots:
    void findText();
    void replaceText();
    void openFile();
    void saveFile();
    void saveFileAs();
    void toggleDarkMode();

private:
    QPlainTextEdit *editor;
    QString currentFilePath;
    bool darkModeEnabled;

    class SyntaxHighlighter : public QSyntaxHighlighter {
    public:
        SyntaxHighlighter(QTextDocument *parent = nullptr);

    protected:
        void highlightBlock(const QString &text) override;

    private:
        struct HighlightRule {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QVector<HighlightRule> rules;
    };
};

#endif // CODEEDITOR_H

