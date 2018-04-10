#ifndef PINGTAB_H
#define PINGTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>

class PingTab : public QWidget
{
    Q_OBJECT
public:
    explicit PingTab(QWidget *parent = nullptr);
    QString getCount();
    QString getIp();

signals:

public slots:

private:
    QVBoxLayout *_vLayout;
    QHBoxLayout *_ipLayout;
    QHBoxLayout *_timesLayout;
    QLabel *_ipLabel;
    QLabel *_dotLabel1;
    QLabel *_dotLabel2;
    QLabel *_dotLabel3;
    QLabel *_timesLabel;
    QLineEdit *_ipEdit1;
    QLineEdit *_ipEdit2;
    QLineEdit *_ipEdit3;
    QLineEdit *_ipEdit4;
    QSpinBox *_timesEdit;
};

#endif // PINGTAB_H
