#include "mainwindow.h"
#include "pingtab.h"
#include "tracerttab.h"
#include "generaltab.h"
#include <QStringList>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      _tabs(new QTabWidget(this)),
      _layout(new QVBoxLayout(this)),
      _btnsLayout(new QHBoxLayout(this)),
      _outputText(new QTextEdit(this)),
      _runButton(new QPushButton(this)),
      _clearButton(new QPushButton(this)),
      _terminateButton(new QPushButton(this)),
      _commandRunner(new QProcess(this))
{
    // Add TABs with commands
    _tabs->addTab(new PingTab(_tabs), "ping");
    _tabs->addTab(new TracertTab(_tabs), "traceroute");
    _tabs->addTab(new OneOptionTab("'Show all' option", _tabs), "arp");
    _tabs->addTab(new OneOptionTab( "'Show all' option", _tabs), "ifconfig");

    // Setup buttons and text field geometry
    _outputText->setBaseSize(150, 400);
    _runButton->setText("RUN");
    _runButton->setFixedWidth(140);
    _clearButton->setText("CLEAR");
    _clearButton->setFixedWidth(140);
    _terminateButton->setText("TERMINATE");
    _terminateButton->setFixedWidth(140);

    /* Horizontal layout for buttons*/
    _btnsLayout->addWidget(_runButton);
    _btnsLayout->addWidget(_terminateButton);
    _btnsLayout->addWidget(_clearButton);

    /* Main vertical layout */
    _layout->addWidget(_tabs);
    _layout->setAlignment(_tabs, Qt::AlignTop);
    _layout->addLayout(_btnsLayout);
    _layout->setAlignment(_runButton, Qt::AlignHCenter);
    _layout->addWidget(_outputText);
    setLayout(_layout);

    // Set the initial poistion and size of the main window
    this->setGeometry(300, 130, 500, 500);

    /* Mechanics of the  application */

    // Execute command when the "RUN" button is clicked
    connect(_runButton, SIGNAL (clicked()), this, SLOT (runCommand()));

    // Terminate the process when "TERMINATE" button is clicked
    connect(_terminateButton, SIGNAL (clicked()), _commandRunner, SLOT (terminate()));

    // Clear the output text field when "CLEAR" button is clicked
    connect(_clearButton, SIGNAL (clicked()), this, SLOT (clear()));

    // Update output text filed when the command has finished
    connect(_commandRunner, SIGNAL (readyReadStandardOutput()), this, SLOT (updateOutputRealTime()));

    // Add delimiter to the output text field when the command has been executed
    connect(_commandRunner, SIGNAL (finished(int, QProcess::ExitStatus)), this, SLOT (updateOutput(int, QProcess::ExitStatus)));

    // Handle QProcess error (e.g no such command in the system)
    connect(_commandRunner, SIGNAL (errorOccurred(QProcess::ProcessError)), this, SLOT (handleError(QProcess::ProcessError)));

}

MainWindow::~MainWindow()
{

}

void MainWindow::runCommand()
{

    // Disactivate the button so it cannot be clicked once again
    _runButton->setDisabled(true);

    // Check which TAB is active
    QWidget *currentTab = _tabs->currentWidget();
    int currentTabIndex = _tabs->currentIndex();

    PingTab *pingTab = nullptr;
    TracertTab *tracertTab = nullptr;
    OneOptionTab *arpTab = nullptr;
    OneOptionTab *ifconfigTab = nullptr;

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
        arpTab = reinterpret_cast<OneOptionTab *>(currentTab);

        if (arpTab->isOptionSet())
        {
            arguments << "-a";
        }

        program = "arp";

        break;

    case 3: // IFCONFIG command tab, check if 'all' option is set

        // Fetch data from the ifconfig tab
        ifconfigTab = reinterpret_cast<OneOptionTab *>(currentTab);

        if (ifconfigTab->isOptionSet())
        {
            arguments << "-a";
        }

        program = "ifconfig";

        break;

    }

    // Run the command
    _commandRunner->start(program, arguments);
}

void MainWindow::updateOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    (void)exitCode;
    (void)exitStatus;

    // Activate the button again
    _runButton->setEnabled(true);

    QString delimiter("\n------------------------------------------------------------------\n\n");
    _outputText->append(delimiter);

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = _outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::updateOutputRealTime()
{
    _outputText->setText(_outputText->toPlainText() + _commandRunner->readAllStandardOutput());

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = _outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::clear()
{
    _outputText->clear();
}

void MainWindow::handleError(QProcess::ProcessError error)
{

    switch (error) {
    case QProcess::FailedToStart:

        _outputText->append("ERROR. Failed to start the process\n");
        _outputText->append("\n------------------------------------------------------------------\n\n");

        // Activate the button again. Need to be done here since in this case
        // handler related to "process finished" event will not be triggered.
        _runButton->setEnabled(true);

        break;

    case QProcess::Crashed:

        _outputText->append("ERROR. Process terminated\n");
        break;

    case QProcess::Timedout:

        _outputText->append("ERROR. Timeout occured\n");
        break;

    case QProcess::WriteError:

        _outputText->append("ERROR. WriteError occured\n");
        break;

    case QProcess::ReadError:

        _outputText->append("ERROR. ReadError occured\n");
        break;

    case QProcess::UnknownError:

        _outputText->append("ERROR. UnknownError occured\n");
        break;
    }

    // Activate the button again
    _runButton->setEnabled(true);

    // Auto scroll down if the amount of text is greater than the text field
    QScrollBar *sb = _outputText->verticalScrollBar();
    sb->setValue(sb->maximum());
}


