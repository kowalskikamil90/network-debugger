#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void runCommand();

private:
    QTabWidget *tabs;
    QVBoxLayout *layout;
    QTextEdit *outputText;
    QPushButton *runButton;
};

#endif // MAINWINDOW_H
