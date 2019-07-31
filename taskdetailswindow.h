#ifndef TASKDETAILSWINDOW_H
#define TASKDETAILSWINDOW_H

#include <QDialog>
#include<addnewtaskwindow.h>
#include<mainwindow.h>
#include<QString>
namespace Ui {
class taskdetailswindow;
}

class taskdetailswindow : public QDialog
{
    Q_OBJECT

public:
    explicit taskdetailswindow(int task_id,QString str,QWidget *parent = nullptr,MainWindow *window = nullptr);
    ~taskdetailswindow();
    QString _convert_to_string(int num);
    void _view_from_tasks(int id);
    void _view_from_done_tasks(int id);
    void search_by_name(int id);
    void _view_from_overdue_tasks(int id);
    void edit_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname);
   int id=0;
   void edit_done_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname);
   void edit_overdue_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname);
void _view_from_today_tasks(int id);
void edit_today_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname);

    MainWindow *window2;
    QString view;

private slots:
    void on_pushButton_clicked();

private:
    Ui::taskdetailswindow *ui;
    MainWindow *window;


};

#endif // TASKDETAILSWINDOW_H
