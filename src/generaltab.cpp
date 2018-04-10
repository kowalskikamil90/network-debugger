#include "generaltab.h"

OneOptionTab::OneOptionTab(QString optionName, QWidget *parent) :
    QWidget(parent),
    _option(new QCheckBox),
    _mainLayout(new QVBoxLayout),
    _hLayout(new QHBoxLayout )
{
    _option->setText(optionName);
    _hLayout->addWidget(_option);
    _hLayout->addStretch(1);

    _mainLayout->addLayout(_hLayout);
    _mainLayout->addStretch(1);

    setLayout(_mainLayout);
}

bool OneOptionTab::isOptionSet()
{
    return _option->isChecked();
}
