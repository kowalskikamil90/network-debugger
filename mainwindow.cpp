#include "mainwindow.h"
#include "pingtab.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      tabs(new QTabWidget(this)),
      layout(new QVBoxLayout(this)),
      outputText(new QTextEdit(this)),
      run(new QPushButton(this))
{
    tabs->addTab(new PingTab(), "ping");
    outputText->setText("<HARDCODED OUTPUT>");
    outputText->setBaseSize(150, 400);
    run->setText("RUN");
    run->setFixedWidth(100);

    layout->addWidget(tabs);
    layout->setAlignment(tabs, Qt::AlignTop);
    layout->addWidget(run);
    layout->setAlignment(run, Qt::AlignHCenter);
    layout->addWidget(outputText);
    setLayout(layout);

    this->setGeometry(300, 300, 400, 500);
}

MainWindow::~MainWindow()
{

}
