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

private:
    QTabWidget *tabs;
    QVBoxLayout *layout;
    QHBoxLayout *btnsLayout;
    QTextEdit *outputText;
    QPushButton *runButton;
    QPushButton *clearButton;
    QProcess *commandRunner;
};

#endif // MAINWINDOW_H
