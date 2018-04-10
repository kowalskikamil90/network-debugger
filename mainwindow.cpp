#include "mainwindow.h"
#include "pingtab.h"
#include "tracerttab.h"
#include "generaltab.h"
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
    // Add TABs with commands
    tabs->addTab(new PingTab(tabs), "ping");
    tabs->addTab(new TracertTab(tabs), "traceroute");
    tabs->addTab(new GeneralTab("'Show all' option", tabs), "arp");
    tabs->addTab(new GeneralTab( "'Show all' option", tabs), "ifconfig");

    // Setup buttons and text field geometry
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
    this->setGeometry(300, 130, 500, 500);

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

    // Handle QProcess error (e.g no such command in the system)
    connect(commandRunner, SIGNAL (errorOccurred(QProcess::ProcessError)), this, SLOT (handleError(QProcess::ProcessError)));

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
    TracertTab *tracertTab = nullptr;
    GeneralTab *arpTab = nullptr;
    GeneralTab *ifconfigTab = nullptr;

    QString program;
    QStringList arguments;
    QString ip;
    QString count;

    // Cast QWidget* to a correct tab class
    switch (currentTabIndex){

    case 0: // PING command tab, get count and IP address

        // Fetch data from the ping tab
        pingTab = reinterpret_cast<PingTab *>(currentTab);
        count = pingTab->getCount();
        ip = pingTab->getIp();

        program = "ping";
        arguments << ip;
        arguments << "-c" << count;

        break;

    case 1: // TRACEROUTE command tab, get IP address

        // Fetch data from the ping tab
        tracertTab = reinterpret_cast<TracertTab *>(currentTab);
        ip = tracertTab->getIp();

        program = "traceroute";
        arguments << ip;

        break;

    case 2: // ARP command tab, check if 'all' option is set

        // Fetch data from the arp tab
        arpTab = reinterpret_cast<GeneralTab *>(currentTab);

        if (arpTab->isOptionSet())
        {
            arguments << "-a";
        }

        program = "arp";

        break;

    case 3: // IFCONFIG command tab, check if 'all' option is set

        // Fetch data from the ifconfig tab
        ifconfigTab = reinterpret_cast<GeneralTab *>(currentTab);

        if (ifconfigTab->isOptionSet())
        {
            arguments << "-a";
        }

        program = "ifconfig";

        break;

    }

    // Run the command
    commandRunner->start(program, arguments);
}

void MainWindow::updateOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    (void)exitCode;
    (void)exitStatus;

    // Activate the button again
    runButton->setEnabled(true);

    QString delimiter("\n------------------------------------------------------------------\n\n");
    outputText->append(delimiter);

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::updateOutputRealTime()
{
    outputText->setText(outputText->toPlainText() + commandRunner->readAllStandardOutput());

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::clear()
{
    outputText->clear();
}

void MainWindow::handleError(QProcess::ProcessError error)
{

    switch (error) {
    case QProcess::FailedToStart:

        outputText->append("ERROR. Failed to start the process\n");
        outputText->append("\n------------------------------------------------------------------\n\n");

        // Activate the button again. Need to be done here since in this case
        // handler related to "process finished" event will not be triggered.
        runButton->setEnabled(true);

        break;

    case QProcess::Crashed:

        outputText->append("ERROR. Process terminated\n");
        break;

    case QProcess::Timedout:

        outputText->append("ERROR. Timeout occured\n");
        break;

    case QProcess::WriteError:

        outputText->append("ERROR. WriteError occured\n");
        break;

    case QProcess::ReadError:

        outputText->append("ERROR. ReadError occured\n");
        break;

    case QProcess::UnknownError:

        outputText->append("ERROR. UnknownError occured\n");
        break;
    }

    // Activate the button again
    runButton->setEnabled(true);

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}


