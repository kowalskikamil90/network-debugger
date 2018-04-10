#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
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
    void updateOutput(int, QProcess::ExitStatus);

private:
    QTabWidget *tabs;
    QVBoxLayout *layout;
    QTextEdit *outputText;
    QPushButton *runButton;
    QProcess *commandRunner;
};

#endif // MAINWINDOW_H
