#include "search_window.h"
#include "ui_search_window.h"
#include<QString>
search_window::search_window(int year,int month,int day,int id,int priority,QString taskname,QString taskdetails,int tasknumber,QWidget *parent):
    QDialog(parent),
    ui(new Ui::search_window)
{
    ui->setupUi(this);
    ui->day_area->setReadOnly(true);
    ui->month_area->setReadOnly(true);
    ui->year_area->setReadOnly(true);
    ui->task_name_area->setReadOnly(true);
    ui->task_details_area->setReadOnly(true);
    ui->priority_area->setReadOnly(true);
    ui->task_number_area->setReadOnly(true);
    ui->task_name_area->setText(taskname);
    ui->task_details_area->setText(taskdetails);
    ui->priority_area->setText(_convert_to_string(priority));
    ui->day_area->setText(_convert_to_string(day));
    ui->month_area->setText(_convert_to_string(month));
    ui->year_area->setText(_convert_to_string(year));
    ui->task_number_area->setText(_convert_to_string(id));
}

search_window::~search_window()
{
    delete ui;
}
QString search_window::_convert_to_string(int num){
return QString::number(num);
}
