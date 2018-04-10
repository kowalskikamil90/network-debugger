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
    explicit OneOptionTab(QString option, QWidget *parent = nullptr);
    bool isOptionSet();

signals:

public slots:

private:
    QCheckBox *option;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hLayout;
};

#endif // GENERALTAB_H
