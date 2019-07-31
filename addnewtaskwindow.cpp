#include "addnewtaskwindow.h"
#include "ui_addnewtaskwindow.h"
#include<mainwindow.h>
#include<QSqlQuery>
#include<QChar>
#include<QDebug>
#include<QMovie>
#include"form.h"
addnewtaskwindow::addnewtaskwindow(QWidget *parent,MainWindow *window) :
    QDialog(parent),
    ui(new Ui::addnewtaskwindow)
{

    ui->setupUi(this);
    this->window = window;




}

addnewtaskwindow::~addnewtaskwindow()
{
    delete ui;
}

void addnewtaskwindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Do you want to save your changes?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    QString _taskname=ui->_tasktitlearea->toPlainText()
            ,_taskdetails=ui->_taskdetailsarea->toPlainText();

    QString _taskpriority=ui->_taskpriorityarea->toPlainText();
    int day,month,year;

    take_time(day,month,year);

    QSqlQuery query;
    bool today_tasks=false,overdue_tasks=false,task_data_table=false;
    if(!window->is_date_pass(day,month,year)){
        if(_current_day==day&&_current_month==month&&_current_year==year){
            query.prepare("INSERT INTO today_tasks (taskname, taskdetails, priority,id,day,month,year) "
                          "VALUES (:taskname, :taskdetails, :priority,:id,:day,:month,:year)");
            today_tasks=true;

        }else{




        query.prepare("INSERT INTO task_data_table (taskname, taskdetails, priority,id,day,month,year) "
                      "VALUES (:taskname, :taskdetails, :priority,:id,:day,:month,:year)");
        task_data_table=true;
        }
    }else{
        query.prepare("INSERT INTO overdue_tasks (taskname, taskdetails, priority,id,day,month,year) "
                      "VALUES (:taskname, :taskdetails, :priority,:id,:day,:month,:year)");
    overdue_tasks=true;
    }
    int priority;
    if(_string_or_not(_taskpriority)&&window->is_string_valid(_taskname)){
        qDebug()<<"is in";
        priority=_convert_to_int(_taskpriority);
        query.bindValue(":priority",priority);
        //window->giveid(id);
        int max=window->_giveid();

        query.bindValue(":taskname",_taskname);
        query.bindValue(":taskdetails",_taskdetails);
        query.bindValue(":id",max);
        query.bindValue(":day",day);
        query.bindValue(":month",month);
        query.bindValue(":year",year);
        query.exec();
        window->_assign_checkbox_id(max);
        window->addtask(_taskname,_taskdetails,priority,max,day,month,year);


    }else{
        if(!_string_or_not(_taskpriority)){
        QMessageBox *mb=new QMessageBox;
        mb->warning(this,tr("warning"),tr("Invalid priority please enter valid number"),QMessageBox::Ok);
        }else if(!window->is_string_valid(_taskname)){
            QMessageBox *mb=new QMessageBox;
            mb->warning(this,tr("warning"),tr("Invalid taskname please enter valid string"),QMessageBox::Ok);

        }

}
     }
}
bool addnewtaskwindow::_string_or_not(QString str){

    for(int i=0;i<str.size();i++){
        QChar m=str.at(i);
        if(m.toLatin1()!=48&&m.toLatin1()!=49&&m.toLatin1()!=50&&m.toLatin1()!=51&&m.toLatin1()!=52&&m.toLatin1()!=53&&m.toLatin1()!=54&&m.toLatin1()!=55&&m.toLatin1()!=56&&m.toLatin1()!=57){
            return false;
        }
    }
    return true;
}
int addnewtaskwindow::_convert_to_int(QString str){
    return str.toInt();
}
void addnewtaskwindow::take_time(int &day,int &month,int &year){
    day=ui->calendarWidget->selectedDate().day();
    month=ui->calendarWidget->selectedDate().month();
    year=ui->calendarWidget->selectedDate().year();
    qDebug()<<day<<" "<<month<<" "<<year;


}

