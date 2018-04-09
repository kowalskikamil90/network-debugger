#ifndef PINGTAB_H
#define PINGTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVector>

class PingTab : public QWidget
{
    Q_OBJECT
public:
    explicit PingTab(QWidget *parent = nullptr);
    int getTimes();
    QVector<int>& getIp(QVector<int>& ipOctets);

signals:

public slots:

private:
    QVBoxLayout *vLayout;
    QHBoxLayout *ipLayout;
    QHBoxLayout *timesLayout;
    QLabel *ipLabel;
    QLabel *dotLabel1;
    QLabel *dotLabel2;
    QLabel *dotLabel3;
    QLabel *timesLabel;
    QLineEdit *ipEdit1;
    QLineEdit *ipEdit2;
    QLineEdit *ipEdit3;
    QLineEdit *ipEdit4;
    QSpinBox *timesEdit;
};

#endif // PINGTAB_H
