#include "mainwindow.h"
#include "pingtab.h"
#include <QStringList>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      tabs(new QTabWidget(this)),
      layout(new QVBoxLayout(this)),
      btnsLayout(new QHBoxLayout(this)),
      outputText(new QTextEdit(this)),
      runButton(new QPushButton(this)),
      clearButton(new QPushButton(this)),
      terminateButton(new QPushButton(this)),
      commandRunner(new QProcess(this))
{
    tabs->addTab(new PingTab(tabs), "ping");
    outputText->setBaseSize(150, 400);
    runButton->setText("RUN");
    runButton->setFixedWidth(140);
    clearButton->setText("CLEAR");
    clearButton->setFixedWidth(140);
    terminateButton->setText("TERMINATE");
    terminateButton->setFixedWidth(140);

    /* Horizontal layout for buttons*/
    btnsLayout->addWidget(runButton);
    btnsLayout->addWidget(terminateButton);
    btnsLayout->addWidget(clearButton);

    /* Main vertical layout */
    layout->addWidget(tabs);
    layout->setAlignment(tabs, Qt::AlignTop);
    layout->addLayout(btnsLayout);
    layout->setAlignment(runButton, Qt::AlignHCenter);
    layout->addWidget(outputText);
    setLayout(layout);

    // Set the initial poistion and size of the main window
    this->setGeometry(300, 130, 400, 500);

    /* Mechanics of the  application */

    // Execute command when the "RUN" button is clicked
    connect(runButton, SIGNAL (clicked()), this, SLOT (runCommand()));

    // Terminate the process when "TERMINATE" button is clicked
    connect(terminateButton, SIGNAL (clicked()), commandRunner, SLOT (terminate()));

    // Clear the output text field when "CLEAR" button is clicked
    connect(clearButton, SIGNAL (clicked()), this, SLOT (clear()));

    // Update output text filed when the command has finished
    connect(commandRunner, SIGNAL (readyReadStandardOutput()), this, SLOT (updateOutputRealTime()));

    // Add delimiter to the output text field when the command has been executed
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

    QString delimiter("\n------------------------------------------------------------------\n\n");

    outputText->setText(outputText->toPlainText() + delimiter);

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::updateOutputRealTime()
{
    // Activate the button again
    runButton->setEnabled(true);

    outputText->setText(outputText->toPlainText() + commandRunner->readAllStandardOutput());

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::clear()
{
    outputText->clear();
}


