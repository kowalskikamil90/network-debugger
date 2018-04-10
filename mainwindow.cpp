#include "mainwindow.h"
#include "pingtab.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      tabs(new QTabWidget(this)),
      layout(new QVBoxLayout(this)),
      outputText(new QTextEdit(this)),
      runButton(new QPushButton(this)),
      commandRunner(new QProcess(this))
{
    tabs->addTab(new PingTab(tabs), "ping");
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

    // Execute command when the "RUN" button is clicked
    connect(runButton, SIGNAL (clicked()), this, SLOT (runCommand()));

    // Update output text filed when the command has finished
    connect(commandRunner, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT (updateOutput(int, QProcess::ExitStatus)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::runCommand()
{

    // Disactivate the button so it cannot be clicked once again
    runButton->setDisabled(true);

    // Check which TAB is active
    QWidget *currentTab = tabs->currentWidget();
    int currentTabIndex = tabs->currentIndex();

    PingTab *pingTab = nullptr;

    QString program;
    QStringList arguments;

    // Cast QWidget* to a correct tab class
    switch (currentTabIndex){

    case 0: // PING command tab, get count and IP address

        // Fetch data from the ping tab
        pingTab = reinterpret_cast<PingTab *>(currentTab);
        QString count = pingTab->getCount();
        QString ip = pingTab->getIp();

        program = "ping";
        arguments << ip;
        arguments << "-c" << count;

        commandRunner->start(program, arguments);

        break;
    }
}

void MainWindow::updateOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    (void)exitCode;
    (void)exitStatus;

    // Activate the button again
    runButton->setEnabled(true);

    outputText->setText(commandRunner->readAllStandardOutput());
}
