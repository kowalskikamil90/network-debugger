#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QProcess>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void runCommand();
    void clear();
    void updateOutput(int, QProcess::ExitStatus);
    void updateOutputRealTime();
    void handleError(QProcess::ProcessError);

private:
    QTabWidget *_tabs;
    QVBoxLayout *_layout;
    QHBoxLayout *_btnsLayout;
    QTextEdit *_outputText;
    QPushButton *_runButton;
    QPushButton *_clearButton;
    QPushButton *_terminateButton;
    QProcess *_commandRunner;
};

#endif // MAINWINDOW_H
