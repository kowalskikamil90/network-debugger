#include "generaltab.h"

OneOptionTab::OneOptionTab(QString optionName, QWidget *parent) :
    QWidget(parent),
    option(new QCheckBox),
    mainLayout(new QVBoxLayout),
    hLayout(new QHBoxLayout )
{
    option->setText(optionName);
    hLayout->addWidget(option);
    hLayout->addStretch(1);

    mainLayout->addLayout(hLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

bool OneOptionTab::isOptionSet()
{
    return option->isChecked();
}
