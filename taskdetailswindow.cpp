#include "taskdetailswindow.h"
#include "ui_taskdetailswindow.h"
#include<QSqlQuery>
#include<QString>
#include<QDebug>
#include<mainwindow.h>
#include"mainwindow.h"
taskdetailswindow::taskdetailswindow(int task_id,QString str,QWidget *parent,MainWindow *window ) :
    QDialog(parent),
    ui(new Ui::taskdetailswindow)
{
    ui->setupUi(this);
    this->window = window;

    // MainWindow s;
    id=task_id;
    view=str;
    //ui->day_area->setReadOnly(true);
    //ui->month_area->setReadOnly(true);
    //ui->yaer_area->setReadOnly(true);
    //ui->task_name_area->setReadOnly(true);
    //ui->task_details_area->setReadOnly(true);
    //ui->task_priority->setReadOnly(true);
    ui->task_number_area->setReadOnly(true);
    if(str=="view_from_done_tasks"){
        _view_from_done_tasks(task_id);
    }else if(str=="view_from_tasks"){
        _view_from_tasks(task_id);

    }else if(str=="view_from_overdue_tasks"){

        _view_from_overdue_tasks(task_id);
    }else if(str=="view_from_today_tasks"){
        _view_from_today_tasks(task_id);

    }






}

taskdetailswindow::~taskdetailswindow()
{
    delete ui;
}
QString taskdetailswindow::_convert_to_string(int num){
    return QString::number(num);
}

void taskdetailswindow:: _view_from_tasks(int id){
    QSqlQuery query;
    query.prepare("SELECT taskname,taskdetails,priority,day,month,year FROM task_data_table WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();

    query.first();
    QString task_name=query.value(0).toString();
    QString task_details=query.value(1).toString();
    int task_priority=query.value(2).toInt();
    int day=query.value(3).toInt();
    int month=query.value(4).toInt();
    int year=query.value(5).toInt();
    ui->task_name_area->setPlainText(task_name);
    ui->task_details_area->setPlainText(task_details);
    ui->task_priority->setText(_convert_to_string(task_priority));


    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->yaer_area->setText(_convert_to_string(year));
    ui->task_number_area->setText(_convert_to_string(id));

}
void taskdetailswindow::_view_from_done_tasks(int id){
    QSqlQuery query;
    query.prepare("SELECT taskname,taskdetails,priority,day,month,year FROM done_tasks WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();

    query.first();
    QString task_name=query.value(0).toString();
    QString task_details=query.value(1).toString();
    int task_priority=query.value(2).toInt();
    int day=query.value(3).toInt();
    int month=query.value(4).toInt();
    int year=query.value(5).toInt();
    ui->task_name_area->setPlainText(task_name);
    ui->task_details_area->setPlainText(task_details);
    ui->task_priority->setText(_convert_to_string(task_priority));


    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->yaer_area->setText(_convert_to_string(year));
    ui->task_number_area->setText(_convert_to_string(id));


}
void taskdetailswindow::_view_from_overdue_tasks(int id){
    QSqlQuery query;
    query.prepare("SELECT taskname,taskdetails,priority,day,month,year FROM overdue_tasks WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();

    query.first();
    QString task_name=query.value(0).toString();
    QString task_details=query.value(1).toString();
    int task_priority=query.value(2).toInt();
    int day=query.value(3).toInt();
    int month=query.value(4).toInt();
    int year=query.value(5).toInt();
    ui->task_name_area->setPlainText(task_name);
    ui->task_details_area->setPlainText(task_details);
    ui->task_priority->setText(_convert_to_string(task_priority));


    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->yaer_area->setText(_convert_to_string(year));
    ui->task_number_area->setText(_convert_to_string(id));


}void taskdetailswindow::_view_from_today_tasks(int id){
    QSqlQuery query;
    query.prepare("SELECT taskname,taskdetails,priority,day,month,year FROM today_tasks WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();

    query.first();
    QString task_name=query.value(0).toString();
    QString task_details=query.value(1).toString();
    int task_priority=query.value(2).toInt();
    int day=query.value(3).toInt();
    int month=query.value(4).toInt();
    int year=query.value(5).toInt();
    ui->task_name_area->setPlainText(task_name);
    ui->task_details_area->setPlainText(task_details);
    ui->task_priority->setText(_convert_to_string(task_priority));


    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->yaer_area->setText(_convert_to_string(year));
    ui->task_number_area->setText(_convert_to_string(id));


}

void taskdetailswindow::search_by_name(int id){
    QSqlQuery query;
    query.prepare("SELECT taskname,taskdetails,priority,day,month,year FROM task_data_table WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();

    query.first();
    QString task_name=query.value(0).toString();
    QString task_details=query.value(1).toString();
    int task_priority=query.value(2).toInt();
    int day=query.value(3).toInt();
    int month=query.value(4).toInt();
    int year=query.value(5).toInt();
    ui->task_name_area->setPlainText(task_name);
    ui->task_details_area->setPlainText(task_details);
    ui->task_priority->setText(_convert_to_string(task_priority));


    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->yaer_area->setText(_convert_to_string(year));
}

void taskdetailswindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Do you want to save your changes?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    qDebug()<<id;
    int day=ui->day_area->toPlainText().toInt();
    int month=ui->month_area->toPlainText().toInt();
    int year=ui->yaer_area->toPlainText().toInt();
    QString taskname=ui->task_name_area->toPlainText();
    QString taskdetails=ui->task_details_area->toPlainText();
    int priority=ui->task_priority->text().toInt();
    if(view=="view_from_tasks"){
        edit_tasks(id,day,month,year,priority,taskdetails,taskname);

        window->modify_checkbox_from_tasktable(id,taskname);
        window->modify_checkbox_from_tasktable_st(id,taskname,taskdetails,day,year,month,priority);

    }else if(view=="view_from_done_tasks"){
        edit_done_tasks(id,day,month,year,priority,taskdetails,taskname);
        window->modify_checkbox_from_done_tasks(id,taskname);
        window->modify_checkbox_from_tasktable_st(id,taskname,taskdetails,day,year,month,priority);

    }else if(view=="view_from_overdue_tasks"){
        edit_overdue_tasks(id,day,month,year,priority,taskdetails,taskname);
        window->modify_checkbox_from_overdue_tasks(id,taskname);
        window->modify_checkbox_from_tasktable_st(id,taskname,taskdetails,day,year,month,priority);

    }else if(view=="view_from_today_tasks"){
    edit_today_tasks(id,day,month,year,priority,taskdetails,taskname);
    window->modify_checkbox_from_today_tasks(id,taskname);
    window->modify_checkbox_from_tasktable_st(id,taskname,taskdetails,day,year,month,priority);



}
}
}
void  taskdetailswindow::edit_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname){
    QSqlQuery query;
    query.prepare("UPDATE task_data_table SET  taskname=(:taskname),priority=(:priority),day=(:day),month=(:month),year=(:year),taskdetails=(:taskdetails) WHERE id=(:id)");
    query.bindValue(":id",id);
    query.bindValue(":taskdetails",taskdetails);
    query.bindValue(":taskname",taskname);
    query.bindValue(":day",day);
    query.bindValue(":month",month);
    query.bindValue(":year",year);
    query.bindValue(":priority",priority);
    query.exec();
}
void taskdetailswindow:: edit_done_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname){
    QSqlQuery query;
    query.prepare("UPDATE done_tasks SET  taskname=(:taskname),priority=(:priority),day=(:day),month=(:month),year=(:year),taskdetails=(:taskdetails) WHERE id=(:id)");
    query.bindValue(":id",id);
    query.bindValue(":taskdetails",taskdetails);
    query.bindValue(":taskname",taskname);
    query.bindValue(":day",day);
    query.bindValue(":month",month);
    query.bindValue(":year",year);
    query.bindValue(":priority",priority);
    query.exec();
}
void taskdetailswindow:: edit_overdue_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname){
    QSqlQuery query;
    query.prepare("UPDATE overdue_tasks SET  taskname=(:taskname),priority=(:priority),day=(:day),month=(:month),year=(:year),taskdetails=(:taskdetails) WHERE id=(:id)");
    query.bindValue(":id",id);
    query.bindValue(":taskdetails",taskdetails);
    query.bindValue(":taskname",taskname);
    query.bindValue(":day",day);
    query.bindValue(":month",month);
    query.bindValue(":year",year);
    query.bindValue(":priority",priority);
    query.exec();


}
void taskdetailswindow:: edit_today_tasks(int id,int day,int month,int year,int priority,QString taskdetails,QString taskname){
    QSqlQuery query;
    query.prepare("UPDATE today_tasks SET  taskname=(:taskname),priority=(:priority),day=(:day),month=(:month),year=(:year),taskdetails=(:taskdetails) WHERE id=(:id)");
    query.bindValue(":id",id);
    query.bindValue(":taskdetails",taskdetails);
    query.bindValue(":taskname",taskname);
    query.bindValue(":day",day);
    query.bindValue(":month",month);
    query.bindValue(":year",year);
    query.bindValue(":priority",priority);
    query.exec();


}


