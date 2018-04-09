#include "mainwindow.h"
#include "pingtab.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      tabs(new QTabWidget(this)),
      layout(new QVBoxLayout(this)),
      outputText(new QTextEdit(this)),
      runButton(new QPushButton(this))
{
    tabs->addTab(new PingTab(tabs), "ping");
    outputText->setText("<HARDCODED OUTPUT>");
    outputText->setBaseSize(150, 400);
    runButton->setText("RUN");
    runButton->setFixedWidth(100);

    layout->addWidget(tabs);
    layout->setAlignment(tabs, Qt::AlignTop);
    layout->addWidget(runButton);
    layout->setAlignment(runButton, Qt::AlignHCenter);
    layout->addWidget(outputText);
    setLayout(layout);

    this->setGeometry(300, 130, 400, 500);

    connect(runButton, SIGNAL (clicked()), this, SLOT (runCommand()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::runCommand()
{
    // Check which TAB is active
    QWidget *currentTab = tabs->currentWidget();
    int currentTabIndex = tabs->currentIndex();

    PingTab *pingTab = nullptr;

    // Cast QWidget* to a correct tab class
    switch (currentTabIndex){

    case 0: // PING command tab, get count and IP address
        pingTab = reinterpret_cast<PingTab *>(currentTab);
        int times = pingTab->getTimes();
        QVector<int> ipOctets(4);
        pingTab->getIp(ipOctets);

        qDebug() << "0" << ipOctets[0];
        qDebug() << "1" << ipOctets[1];
        qDebug() << "2" << ipOctets[2];
        qDebug() << "3" << ipOctets[3];

        break;
    }
}
