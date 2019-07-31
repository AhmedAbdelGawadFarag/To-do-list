#ifndef ADDNEWTASKWINDOW_H
#define ADDNEWTASKWINDOW_H

#include <QDialog>
#include<mainwindow.h>
#include<QtSql/QSqlDatabase>
#include<QString>
#include<string>
using namespace std;
namespace Ui {
class addnewtaskwindow;
}

class addnewtaskwindow : public QDialog
{
    Q_OBJECT

public:
    explicit addnewtaskwindow(QWidget *parent = nullptr,MainWindow *window = nullptr);
    ~addnewtaskwindow();
    QSqlDatabase sqldb;
    bool _string_or_not(QString str);
    int _convert_to_int(QString str);
    void take_time(int &day,int &month,int &year);
   // int id=0;
private slots:
    void on_pushButton_clicked();

private:
    Ui::addnewtaskwindow *ui;

    MainWindow *window;
};

#endif // ADDNEWTASKWINDOW_H
