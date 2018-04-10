#ifndef TRACERTTAB_H
#define TRACERTTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>

class TracertTab : public QWidget
{
    Q_OBJECT
public:
    explicit TracertTab(QWidget *parent = nullptr);
    QString getIp();

signals:

public slots:

private:
    QVBoxLayout *_vLayout;
    QHBoxLayout *_ipLayout;
    QLabel *_ipLabel;
    QLabel *_dotLabel1;
    QLabel *_dotLabel2;
    QLabel *_dotLabel3;
    QLineEdit *_ipEdit1;
    QLineEdit *_ipEdit2;
    QLineEdit *_ipEdit3;
    QLineEdit *_ipEdit4;
};

#endif // TRACERTTAB_H
