#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class OneOptionTab : public QWidget
{
    Q_OBJECT
public:
    explicit OneOptionTab(QString optionName, QWidget *parent = nullptr);
    bool isOptionSet();

signals:

public slots:

private:
    QCheckBox *_option;
    QVBoxLayout *_mainLayout;
    QHBoxLayout *_hLayout;
};

#endif // GENERALTAB_H
