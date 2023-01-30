#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<addnewtaskwindow.h>
#include<QSqlQuery>
#include<QDebug>
#include<QDate>
#include<QDateTime>
#include<taskdetailswindow.h>
#include"ui_taskdetailswindow.h"
#include"search_window.h"
#include<QFile>
#include<QTextStream>
#include<QMovie>
#include<QMessageBox>
#include <QDirIterator>
QString pwd;
int _current_year;
int _current_day;
int _current_month;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    QDir dir(".");


    pwd.append( dir.absolutePath() );


//    QFile f(":qdarkstyle/style.qss");
//    if (!f.exists())
//    {
//        printf("Unable to set stylesheet, file not found\n");
//    }
//    else
//    {
//        f.open(QFile::ReadOnly | QFile::Text);
//        QTextStream ts(&f);
//        qApp->setStyleSheet(ts.readAll());
//    }


    open_database();

    _current_day=ui->calendarWidget->selectedDate().day();
    _current_month=ui->calendarWidget->selectedDate().month();
    _current_year=ui->calendarWidget->selectedDate().year();
    qDebug()<<_current_day;
    load_alltasks();
    load_donetasks();
    load_today_tasks();
    load_overdue_task();
    qDebug()<<tasknumber;
    for(int i=0;i<num3;i++){
        if(st_tasks[i].today)
            qDebug()<<st_tasks[i].taskname;

    }
    ui->calendarWidget->hide();
    ui->search_by_name_area->hide();
    ui->search_priority_area->hide();
    ui->search_number_area->hide();
    ui->calendarWidget->showToday();
    //ui->label_2->hide();


    QDirIterator it(pwd.toLatin1() +"/Resource/themes/", QStringList() << "*.qss", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        //  QFileInfo fileInfo(f.fileName());
        ui->cmbTheme->addItem(it.next().toLatin1());
    }

    QString walltheme;
    QFile MyFile(pwd.toLatin1() +"/themes.txt");
    if (MyFile.exists()) {
        MyFile.open(QIODevice::ReadWrite);
        QTextStream in (&MyFile);
        QString line;
        QStringList list;
        //   QList<QString> nums;
        QStringList nums;
        QRegularExpression rx("[|]");
        line = in.readLine();
        QString stylesheet;

        if (line.contains("|")) {
            list = line.split(rx);
            qDebug() << "theme" <<  list.at(1).toLatin1();
            stylesheet =  list.at(1).toLatin1();
            loadStyleSheet( list.at(1).toLatin1());
            MyFile.close();
        }

        fileName=stylesheet;
        QFile file(stylesheet);

        file.open(QIODevice::Text | QIODevice::ReadOnly);
        QString content;

        while(!file.atEnd())
            content.append(file.readLine());
     }
    loaded=true;

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addtask(QString &taskname,QString taskdetails,int priority,int id,int day,int month,int year){



    if(is_date_pass(day,month,year)){
        qDebug()<<num4;
        box4[num4].first.setText(taskname);
        box4[num4].second=_check_box_id;
        st_tasks[num3].taskname=taskname;
        st_tasks[num3].id=id;
        st_tasks[num3].priority=priority;
        st_tasks[num3].taskdetails=taskdetails;
        st_tasks[num3].day=day;
        st_tasks[num3].month=month;
        st_tasks[num3].year=year;
        make_struct_status("overdue",st_tasks[num3].id);
        put_checkbox_on_overdue_tasks_ui(box4[num4].first);
        num4++;
        tasknumber++;
        st_tasks[num3].num_of_task=tasknumber;
    }else {
        if(_current_day==day&&_current_year==year&&_current_month==month){
            box5[num5].first.setText(taskname);
            box5[num5].second=_check_box_id;
            qDebug()<<box5[num5].second;
            st_tasks[num3].taskname=taskname;
            st_tasks[num3].id=id;
            st_tasks[num3].priority=priority;
            st_tasks[num3].taskdetails=taskdetails;
            st_tasks[num3].day=day;
            st_tasks[num3].month=month;
            st_tasks[num3].year=year;
            make_struct_status("today",st_tasks[num3].id);
            put_checkbox_on_today_tasks_ui(box5[num5].first);
            num5++;

            tasknumber++;
            st_tasks[num3].num_of_task=tasknumber;

        }else{
            box[num].first.setText(taskname);
            box[num].second=_check_box_id;
            qDebug()<<box[num].second;
            st_tasks[num3].taskname=taskname;
            st_tasks[num3].id=id;
            st_tasks[num3].priority=priority;
            st_tasks[num3].taskdetails=taskdetails;
            st_tasks[num3].day=day;
            st_tasks[num3].month=month;
            st_tasks[num3].year=year;
            put_checkbox_on_tasks_ui(box[num].first);
            num++;
            tasknumber++;
            st_tasks[num3].num_of_task=tasknumber;
        }
    }

    num3++;




}

void MainWindow::on_pushButton_clicked()
{
    addnewtaskwindow *taskwindow=new addnewtaskwindow(this,this);
    taskwindow->exec();

}

void MainWindow::on_deletebutton_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to permanently delete the selected item(s)?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num-1;i++){
        if(box[i].first.isChecked()){

            box[i].first.hide();
            box[i].first.setChecked(false);
            delete_data_from_st_tasks(box[i].second);
            delete_data_from_tasks(box[i].second);

        }
    }
     }
}void MainWindow::on_delete_today_button_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to permanently delete the selected item(s)?"),QMessageBox::Ok,QMessageBox::Cancel);
    if(ret==QMessageBox::Ok){
        for(int i=0;i<=num5-1;i++){
            if(box5[i].first.isChecked()){

                box5[i].first.hide();
                box5[i].first.setChecked(false);
                delete_data_from_st_today_tasks(box5[i].second);
                delete_data_from_today_tasks(box5[i].second);

            }
        }

    }
}
void MainWindow::on_donebutton_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to mark the selected item(s) as done ?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num-1;i++){
        if(box[i].first.isChecked()){
            qDebug()<<box[i].second;
            QString str=box[i].first.text();
            box2[num2].first.setText(str);
            int id=box[i].second;
            box2[num2].second=id;

            put_checkbox_on_done_tasks_ui(box2[num2].first);
            box[i].first.hide();
            box[i].first.setChecked(false);
            move_data_form_st_tasks_to_st_donetasks(box[i].second);
            num2++;


            move_data_from_tasks_to_donetasks(box[i].second);
            delete_data_from_tasks(box[i].second);


        }
    }
     }
}
void MainWindow::on_done_today_button_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to mark the selected item(s) as done ?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num5-1;i++){
        if(box5[i].first.isChecked()){

            QString str=box5[i].first.text();
            box2[num2].first.setText(str);
            int id=box5[i].second;
            box2[num2].second=id;

            put_checkbox_on_done_tasks_ui(box2[num2].first);
            box5[i].first.hide();
            box5[i].first.setChecked(false);
            move_data_form_st_today_tasks_to_st_donetasks(box5[i].second);
            num2++;


            move_data_from_today_tasks_to_donetasks(box5[i].second);
            delete_data_from_today_tasks(box5[i].second);


        }
    }
}
}
void MainWindow::on_donebutton_overdue_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to mark the selected item(s) as done ?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num4-1;i++){
        if(box4[i].first.isChecked()){
            QString str=box4[i].first.text();
            box2[num2].first.setText(str);
            int id=box4[i].second;
            box2[num2].second=id;
            put_checkbox_on_done_tasks_ui(box2[num2].first);
            box4[i].first.hide();
            box4[i].first.setChecked(false);
            num2++;
            move_data_from_overdue_tasks_to_donetasks(box4[i].second);
            move_data_form_st_overdue_tasks_to_st_donetasks(box4[i].second);
            delete_data_from_overdue_tasks(box4[i].second);



        }
    }
}
}





int MainWindow::_return_last_id_from_tasks(){
    QSqlQuery query;
    query.exec("SELECT id FROM task_data_table");

    query.last();
    int id=query.value(0).toInt();
    return  id;

}
int MainWindow::_return_last_id_from_donetasks(){

    QSqlQuery query;
    query.exec("SELECT id FROM done_tasks");

    query.last();
    int id=query.value(0).toInt();
    return  id;
}
int MainWindow::_return_last_id_from_overdue_tasks(){

    QSqlQuery query;
    query.exec("SELECT id FROM overdue_tasks");

    query.last();
    int id=query.value(0).toInt();
    return  id;

}int MainWindow::_return_last_id_from_today_tasks(){

    QSqlQuery query;
    query.exec("SELECT id FROM today_tasks");

    query.last();
    int id=query.value(0).toInt();
    return  id;


}

void MainWindow::load_alltasks(){
    QSqlQuery query;
    query.exec("SELECT taskname,id,priority,taskdetails,day,month,year FROM task_data_table");
    while(query.next()){
        int day=query.value(4).toInt()
                ,month=query.value(5).toInt(),
                year=query.value(6).toInt();
        qDebug()<<_current_day<<" "<<day;

        if(is_date_pass(day,month,year)){
            QString taskname=query.value(0).toString();

            int id=query.value(1).toInt();

            box4[num4].first.setText(taskname);
            box4[num4].second=id;
            move_data_from_tasks_to_overdue_tasks(box4[num4].second);
            delete_data_from_tasks(box4[num4].second);
            num4++;

        }else {

            if(_current_day==day&&_current_month==month&&_current_year==year){
                QString taskname=query.value(0).toString();
                int id=query.value(1).toInt();
                //st_tasks[num3].priority=query.value(2).toInt();
                //st_tasks[num3].taskdetails=query.value(3).toString();
                //st_tasks[num3].day=query.value(4).toInt();
                //st_tasks[num3].month=query.value(5).toInt();
                //st_tasks[num3].year=query.value(6).toInt();

                box5[num5].first.setText(taskname);
                box5[num5].second=id;
                //put_checkbox_on_today_tasks_ui(box5[num5].first);
                move_data_from_tasks_to_today_tasks(box5[num5].second);
                num5++;


            }else{

                st_tasks[num3].taskname=query.value(0).toString();
                st_tasks[num3].id=query.value(1).toInt();
                st_tasks[num3].priority=query.value(2).toInt();
                st_tasks[num3].taskdetails=query.value(3).toString();
                st_tasks[num3].day=query.value(4).toInt();
                st_tasks[num3].month=query.value(5).toInt();
                st_tasks[num3].year=query.value(6).toInt();
                make_struct_status("alltasks",st_tasks[num3].id);
                box[num].first.setText(st_tasks[num3].taskname);
                box[num].second=st_tasks[num3].id;
                put_checkbox_on_tasks_ui(box[num].first);
                tasknumber++;
                st_tasks[num3].num_of_task=tasknumber;
                num++;
                num3++;
            }
        }


    }

}
void MainWindow::load_donetasks(){
    QSqlQuery query;
    query.exec("SELECT taskname,id,priority,taskdetails,day,month,year FROM done_tasks");
    while (query.next()) {
        st_tasks[num3].taskname=query.value(0).toString();
        st_tasks[num3].id=query.value(1).toInt();
        st_tasks[num3].priority=query.value(2).toInt();
        st_tasks[num3].taskdetails=query.value(3).toString();
        st_tasks[num3].day=query.value(4).toInt();
        st_tasks[num3].month=query.value(5).toInt();
        st_tasks[num3].year=query.value(6).toInt();
        make_struct_status("done",st_tasks[num3].id);
        //qDebug()<<st_done_tasks[num2].taskname<<" "<<st_done_tasks[num2].id;
        box2[num2].first.setText(st_tasks[num3].taskname);
        box2[num2].second=st_tasks[num3].id;
        put_checkbox_on_done_tasks_ui(box2[num2].first);
        ui->scrollArea_2->setWidget(gbox2);
        tasknumber++;
        st_tasks[num3].num_of_task=tasknumber;
        num2++;
        num3++;
    }

}
void MainWindow::load_overdue_task(){
    QSqlQuery query;
    query.exec("SELECT taskname,id,priority,taskdetails,day,month,year FROM overdue_tasks");
    while (query.next()) {
        st_tasks[num3].taskname=query.value(0).toString();
        //qDebug()<<st_tasks[num3].taskname;
        st_tasks[num3].id=query.value(1).toInt();
        st_tasks[num3].priority=query.value(2).toInt();
        st_tasks[num3].taskdetails=query.value(3).toString();
        st_tasks[num3].day=query.value(4).toInt();
        st_tasks[num3].month=query.value(5).toInt();
        st_tasks[num3].year=query.value(6).toInt();
        make_struct_status("overdue",st_tasks[num3].id);
        //qDebug()<<st_done_tasks[num2].taskname<<" "<<st_done_tasks[num2].id;
        box4[num4].first.setText(st_tasks[num3].taskname);
        box4[num4].second=st_tasks[num3].id;
        put_checkbox_on_overdue_tasks_ui(box4[num4].first);
        ui->scrollArea_3->setWidget(gbox4);
        // qDebug()<<num4;
        tasknumber++;
        st_tasks[num3].num_of_task=tasknumber;
        num4++;
        num3++;

    }
}
void MainWindow::load_today_tasks(){
    QSqlQuery query;
    query.exec("SELECT taskname,id,priority,taskdetails,day,month,year FROM today_tasks");
    while (query.next()) {
        int day=query.value(4).toInt();
        int month=query.value(5).toInt();
        int year=query.value(6).toInt();
        if(is_date_pass(day,month,year)){
            st_tasks[num3].taskname=query.value(0).toString();
            //qDebug()<<st_tasks[num3].taskname;
            st_tasks[num3].id=query.value(1).toInt();
            st_tasks[num3].priority=query.value(2).toInt();
            st_tasks[num3].taskdetails=query.value(3).toString();
            st_tasks[num3].day=query.value(4).toInt();
            st_tasks[num3].month=query.value(5).toInt();
            st_tasks[num3].year=query.value(6).toInt();
            make_struct_status("overdue",st_tasks[num3].id);
            //qDebug()<<st_done_tasks[num2].taskname<<" "<<st_done_tasks[num2].id;
            box4[num4].first.setText(st_tasks[num3].taskname);
            box4[num4].second=st_tasks[num3].id;
            // put_checkbox_on_overdue_tasks_ui(box4[num4].first);
            move_data_from_today_tasks_to_overdue_tasks(box4[num4].second);
            delete_data_from_today_tasks(box4[num4].second);
            qDebug()<<box4[num4].second;
            ui->scrollArea_3->setWidget(gbox4);
            tasknumber++;
            st_tasks[num3].num_of_task=tasknumber;
            num4++;
            num3++;
        }else{
            st_tasks[num3].taskname=query.value(0).toString();
            //qDebug()<<st_tasks[num3].taskname;
            st_tasks[num3].id=query.value(1).toInt();
            st_tasks[num3].priority=query.value(2).toInt();
            st_tasks[num3].taskdetails=query.value(3).toString();
            st_tasks[num3].day=query.value(4).toInt();
            st_tasks[num3].month=query.value(5).toInt();
            st_tasks[num3].year=query.value(6).toInt();
            make_struct_status("today",st_tasks[num3].id);

            //qDebug()<<st_done_tasks[num2].taskname<<" "<<st_done_tasks[num2].id;

            box5[num5].first.setText(st_tasks[num3].taskname);
            box5[num5].second=st_tasks[num3].id;
            put_checkbox_on_today_tasks_ui(box5[num5].first);

            tasknumber++;
            st_tasks[num3].num_of_task=tasknumber;
            num5++;
            num3++;
        }
    }
}
void MainWindow::move_data_from_today_tasks_to_donetasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO done_tasks SELECT * FROM today_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}void MainWindow::move_data_from_today_tasks_to_overdue_tasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO overdue_tasks SELECT * FROM today_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}

void MainWindow::move_data_from_tasks_to_donetasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO done_tasks SELECT * FROM task_data_table WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}void MainWindow::move_data_from_overdue_tasks_to_donetasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO done_tasks SELECT * FROM overdue_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();
}
void MainWindow::move_data_from_tasks_to_overdue_tasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO overdue_tasks SELECT * FROM task_data_table WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}void MainWindow::move_data_from_tasks_to_today_tasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO today_tasks SELECT * FROM task_data_table WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}
void MainWindow::move_data_form_st_tasks_to_st_donetasks(int id){
    make_struct_status("done",id);

}void MainWindow::move_data_form_st_today_tasks_to_st_donetasks(int id){
    make_struct_status("done",id);

}

void MainWindow::move_data_form_st_overdue_tasks_to_st_donetasks(int id){
    make_struct_status("done",id);

}
void MainWindow::move_data_from_donetasks_to_tasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO task_data_table SELECT * FROM done_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();
}
void MainWindow::move_data_from_donetasks_to_overdue_tasks(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO overdue_tasks SELECT * FROM done_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();


}

void MainWindow::move_data_from_st_donetasks_to_st_tasks(int id){

    make_struct_status("alltasks",id);

}
void MainWindow::move_data_from_st_donetasks_to_st_overdue_tasks(int id){
    make_struct_status("overdue",id);

}
void MainWindow::move_data_from_st_overduetasks_to_st_tasks(int id){
    for(int i=0;i<num3;i++){
        if(st_tasks[i].overdue&&st_tasks[i].id==id){
            st_tasks[i].overdue=false;
        }
    }
}


void MainWindow::delete_data_from_tasks(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM task_data_table WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}void MainWindow::delete_data_from_today_tasks(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM today_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();

}

int MainWindow::_giveid(){
    int id1=_return_last_id_from_tasks();
    int id2=_return_last_id_from_donetasks();
    int id3=_return_last_id_from_overdue_tasks();
    int id4=_return_last_id_from_today_tasks();
    vector<int> v;
    v.push_back(id1);
    v.push_back(id2);
    v.push_back(id3);
    v.push_back(id4);
    sort(v.begin(),v.end(),greater<int>());
    int max=v[0];


    max++;

    return max;
}
void MainWindow::_assign_checkbox_id(int id){

    _check_box_id= id;

}
void MainWindow::open_database(){
    sqldb=QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("E:/qt/todolist31/14/todolist5/database.db");
    sqldb.open();
}

void MainWindow::on_details_button_clicked()
{
    for(int i=0;i<=num-1;i++){
        if(box[i].first.isChecked()){
            int taskid=box[i].second;

            taskdetailswindow m(taskid,"view_from_tasks",this,this);
            m.exec();
        }

    }
}

void MainWindow::on_delete_from_done_button_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to permanently delete the selected item(s)?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num2-1;i++){
        if(box2[i].first.isChecked()){
            box2[i].first.hide();
            box2[i].first.setChecked(false);
            delete_data_from_st_done_tasks(box2[i].second);
            delete_data_from_done_tasks(box2[i].second);

        }


    }
     }
    qDebug()<<num2;
}

void MainWindow::delete_data_from_done_tasks(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM done_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();


}
void MainWindow::delete_data_from_overdue_tasks(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM overdue_tasks WHERE id =(:id)");
    query.bindValue(":id",id);
    query.exec();


}

void MainWindow::on_details_from_done_tasks_button_clicked()
{
    for(int i=0;i<=num2-1;i++){
        if(box2[i].first.isChecked()){
            int taskid=box2[i].second;
            taskdetailswindow m(taskid,"view_from_done_tasks",this,this);
            m.exec();
        }

    }
}

void MainWindow::on_undone_button_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to mark the selected item(s) as undone ?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){
    for(int i=0;i<=num2-1;i++){
        if(box2[i].first.isChecked()){
            int day,month,year;
            take_date_from_done_tasks(box2[i].second,day,month,year);
            QString str=box2[i].first.text();
            int id=box2[i].second;


            if(is_date_pass(day,month,year)){
                box4[num4].first.setText(str);
                box4[num4].second=id;

                put_checkbox_on_overdue_tasks_ui(box4[num4].first);
                box2[i].first.hide();
                box2[i].first.setChecked(false);
                move_data_from_st_donetasks_to_st_overdue_tasks(id);

                num4++;
                move_data_from_donetasks_to_overdue_tasks(id);
                delete_data_from_done_tasks(id);


            }else {
                if(_current_day==day&&_current_month==month&&_current_year==year){
                    box5[num5].first.setText(str);
                    box5[num5].second=id;
                    put_checkbox_on_today_tasks_ui(box5[num5].first);

                    box2[i].first.hide();
                    box2[i].first.setChecked(false);
                    make_struct_status("today",id);
                    num5++;


                    move_data_from_tasks_to_today_tasks(box5[num5].second);
                    delete_data_from_done_tasks(id);

                }else{


                    qDebug()<<box2[i].second<<" "<<day<<" "<<month<<" "<<year<<" ";
                    box[num].first.setText(str);
                    box[num].second=id;
                    put_checkbox_on_tasks_ui(box[num].first);
                    box2[i].first.hide();
                    box2[i].first.setChecked(false);
                    move_data_from_st_donetasks_to_st_tasks(id);
                    //move_data_from_st_overduetasks_to_st_tasks(id);
                    num++;
                    move_data_from_donetasks_to_tasks(id);
                    delete_data_from_done_tasks(id);



                    qDebug()<<num;
                }
            }
        }
    }
}
}
void MainWindow::put_checkbox_on_tasks_ui(QCheckBox &checkbox){
    vlayout->addWidget(&checkbox);
    gbox->setLayout(vlayout);
    ui->scrollArea->setWidget(gbox);
}
void MainWindow::put_checkbox_on_today_tasks_ui(QCheckBox &checkbox){
    vlayout5->addWidget(&checkbox);
    gbox5->setLayout(vlayout5);
    ui->scrollArea_4->setWidget(gbox5);


}
void MainWindow::put_checkbox_on_done_tasks_ui(QCheckBox &checkbox){
    vlayout2->addWidget(&checkbox);
    gbox2->setLayout(vlayout2);
    ui->scrollArea_2->setWidget(gbox2);
}
void MainWindow::put_checkbox_on_overdue_tasks_ui(QCheckBox &checkbox){
    vlayout4->addWidget(&checkbox);
    gbox4->setLayout(vlayout4);
    ui->scrollArea_3->setWidget(gbox4);

}

void MainWindow::check_tasks_struct(){
    for(int i=0;i<num3;i++){
        if(!st_tasks[i].done&&!st_tasks[i].is_deleted&&!st_tasks[i].today&&!st_tasks[i].overdue){
            qDebug()<<st_tasks[i].taskname<<" "
                   <<st_tasks[i].id<<" "
                  <<st_tasks[i].priority<<" "
                 <<st_tasks[i].taskdetails<<" "
                <<st_tasks[i].day<<" "
               <<st_tasks[i].month<<" "
              <<st_tasks[i].year<<" "<<st_tasks[i].num_of_task;
        }
    }

}void MainWindow::check_today_tasks_struct(){
    for(int i=0;i<num3;i++){
        if(!st_tasks[i].overdue&&!st_tasks[i].done&&!st_tasks[i].is_deleted&&st_tasks[i].today){
            qDebug()<<st_tasks[i].taskname<<" "
                   <<st_tasks[i].id<<" "
                  <<st_tasks[i].priority<<" "
                 <<st_tasks[i].taskdetails<<" "
                <<st_tasks[i].day<<" "
               <<st_tasks[i].month<<" "
              <<st_tasks[i].year<<" "<<st_tasks[i].num_of_task;
        }
    }

}

void MainWindow::check_done_struct(){
    for(int i=0;i<num3;i++){
        if(!st_tasks[i].today&&!st_tasks[i].overdue&&st_tasks[i].done&&!st_tasks[i].is_deleted){

            qDebug()<<num3<<" "<<i<<" "<<st_tasks[i].taskname<<" "
                   <<st_tasks[i].id<<" "
                  <<st_tasks[i].priority<<" "
                 <<st_tasks[i].taskdetails<<" "
                <<st_tasks[i].day<<" "
               <<st_tasks[i].month<<" "
              <<st_tasks[i].year<<" "<<st_tasks[i].num_of_task;
        }
    }
}
void MainWindow::check_overdue_struct(){
    for(int i=0;i<num3;i++){
        if(!st_tasks[i].today&&!st_tasks[i].done&&!st_tasks[i].is_deleted&&st_tasks[i].overdue){

            qDebug()<<num3<<" "<<i<<" "<<st_tasks[i].taskname<<" "
                   <<st_tasks[i].id<<" "
                  <<st_tasks[i].priority<<" "
                 <<st_tasks[i].taskdetails<<" "
                <<st_tasks[i].day<<" "
               <<st_tasks[i].month<<" "
              <<st_tasks[i].year<<" "<<st_tasks[i].num_of_task;
        }
    }

}
void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<num3;i++){
        if(st_tasks[i].today){
            qDebug()<<st_tasks[i].taskname;
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    check_done_struct();
}
void MainWindow::delete_data_from_st_tasks(int id){
    make_struct_status("delete",id);

}
void MainWindow::delete_data_from_st_done_tasks(int id){
    make_struct_status("delete",id);

}void MainWindow::delete_data_from_st_today_tasks(int id){
    make_struct_status("delete",id);

}
void MainWindow::delete_data_from_st_overdue_tasks(int id){

    make_struct_status("delete",id);
}


void MainWindow::on_pushButton_4_clicked()
{
bool isfound=false;
    QString name=ui->search_by_name_area->toPlainText();
    if(ui->search_in_tasks_radioButton->isChecked()&&ui->search_by_name_button->isChecked()){
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].done&&!st_tasks[i].overdue&&st_tasks[i].taskname==name&&!st_tasks[i].is_deleted&&!st_tasks[i].today){
                isfound=true;
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                // s.setFixedSize(800,500);
                s.exec();
            }
        }
    }else if(ui->search_in_done_tasks_radioButton->isChecked()&&ui->search_by_name_button->isChecked()){
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].overdue&&st_tasks[i].done&&st_tasks[i].taskname==name&&!st_tasks[i].is_deleted&&!st_tasks[i].today){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }
        }


    }
    else if(ui->search_in_overdue_tasks_radioButton->isChecked()&&ui->search_by_name_button->isChecked()){
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].today&&st_tasks[i].overdue&&!st_tasks[i].done&&st_tasks[i].taskname==name&&!st_tasks[i].is_deleted){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }
        }


    }
    else if(ui->search_in_tasks_radioButton->isChecked()&&ui->search_by_date_button->isChecked()){
        int day=ui->calendarWidget->selectedDate().day(),
                month=ui->calendarWidget->selectedDate().month(),
                year=ui->calendarWidget->selectedDate().year();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].today&&!st_tasks[i].overdue&&!st_tasks[i].done&&!st_tasks[i].is_deleted&&st_tasks[i].day==day&&st_tasks[i].month==month&&st_tasks[i].year==year){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }

        }
    }
    else if(ui->search_in_overdue_tasks_radioButton->isChecked()&&ui->search_by_date_button->isChecked()){
        int day=ui->calendarWidget->selectedDate().day(),
                month=ui->calendarWidget->selectedDate().month(),
                year=ui->calendarWidget->selectedDate().year();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].done&&!st_tasks[i].today&&st_tasks[i].overdue&&!st_tasks[i].is_deleted&&st_tasks[i].day==day&&st_tasks[i].month==month&&st_tasks[i].year==year){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }

        }
    }
    else if(ui->search_in_done_tasks_radioButton->isChecked()&&ui->search_by_date_button->isChecked()){
        int day=ui->calendarWidget->selectedDate().day(),
                month=ui->calendarWidget->selectedDate().month(),
                year=ui->calendarWidget->selectedDate().year();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].today&&!st_tasks[i].overdue&&st_tasks[i].done&&!st_tasks[i].is_deleted&&st_tasks[i].day==day&&st_tasks[i].month==month&&st_tasks[i].year==year){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }


        }
    }


    else if(ui->search_in_tasks_radioButton->isChecked()&&ui->search_by_priority_button->isChecked()){

        QString priority=ui->search_priority_area->toPlainText();
        int _priority=priority.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].today&&!st_tasks[i].overdue&&!st_tasks[i].done&&st_tasks[i].priority==_priority&&!st_tasks[i].is_deleted){
                qDebug()<<priority;
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;



            }
        }
    }
    else if(ui->search_in_done_tasks_radioButton->isChecked()&&ui->search_by_priority_button->isChecked()){
        QString priority=ui->search_priority_area->toPlainText();
        int _priority=priority.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].today&&!st_tasks[i].overdue&&st_tasks[i].done&&st_tasks[i].priority==_priority&&!st_tasks[i].is_deleted){
                qDebug()<<priority;
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }
        }

    }
    else if(ui->search_in_overdue_tasks_radioButton->isChecked()&&ui->search_by_priority_button->isChecked()){
        QString priority=ui->search_priority_area->toPlainText();
        int _priority=priority.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].done&&!st_tasks[i].today&&st_tasks[i].overdue&&st_tasks[i].priority==_priority&&!st_tasks[i].is_deleted){
                qDebug()<<priority;
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].num_of_task);
                s.exec();
                isfound=true;

            }
        }

    }else if(ui->search_in_tasks_radioButton->isChecked()&&ui->search_by_number_button->isChecked()){
        QString number=ui->search_number_area->toPlainText();
        int _number=number.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].done&&!st_tasks[i].overdue&&st_tasks[i].id==_number&&!st_tasks[i].is_deleted&&!st_tasks[i].today){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].id);
                s.exec();
                isfound=true;


            }


        }


    }else if(ui->search_in_done_tasks_radioButton->isChecked()&&ui->search_by_number_button->isChecked()){
        QString number=ui->search_number_area->toPlainText();
        int _number=number.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].overdue&&st_tasks[i].done&&st_tasks[i].id==_number&&!st_tasks[i].is_deleted&&!st_tasks[i].today){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].id);
                s.exec();
                isfound=true;


            }

        }

    }
    else if(ui->search_in_overdue_tasks_radioButton->isChecked()&&ui->search_by_number_button->isChecked()){
        QString number=ui->search_number_area->toPlainText();
        int _number=number.toInt();
        for(int i=0;i<num3;i++){
            if(!st_tasks[i].done&&!st_tasks[i].today&&st_tasks[i].overdue&&st_tasks[i].id==_number&&!st_tasks[i].is_deleted){
                search_window s(st_tasks[i].year,st_tasks[i].month,st_tasks[i].day,st_tasks[i].id,
                                st_tasks[i].priority,st_tasks[i].taskname,st_tasks[i].taskdetails,st_tasks[i].id);
                s.exec();
                isfound=true;

            }
        }

    }
    if(isfound==false){
        QMessageBox msgBox;
        int ret=msgBox.information(this,tr("warning"),tr("No results found"),QMessageBox::Ok);


    }
}


void MainWindow::on_search_by_name_button_clicked()
{
    ui->search_by_name_area->show();
    ui->calendarWidget->hide();
    ui->search_priority_area->hide();
    ui->search_number_area->hide();
    // ui->label_2->hide();

}

void MainWindow::on_search_by_date_button_clicked()
{
    ui->calendarWidget->show();
    ui->search_by_name_area->hide();
    ui->search_priority_area->hide();
    ui->search_number_area->hide();
    //ui->label_2->hide();

}
void MainWindow::on_search_by_number_button_clicked()
{
    ui->search_number_area->show();
    ui->calendarWidget->hide();
    ui->search_by_name_area->hide();
    ui->search_priority_area->hide();

}

void MainWindow::on_search_by_priority_button_clicked()
{
    ui->search_priority_area->show();
    ui->calendarWidget->hide();
    ui->search_by_name_area->hide();
    ui->search_number_area->hide();
    //ui->label_2->show();

}
bool MainWindow::is_date_pass(int day,int month,int year){
    //22 4 2019 c
    //25 4 2019
    if(_current_year>year){
        qDebug()<<"pass";
        return  true;
    }else if(_current_year==year&&_current_month>month){
        qDebug()<<"pass";
        return  true;
    }

    else if(_current_day>day&&_current_month>=month&&_current_year>=year){
        qDebug()<<"pass";
        return true;
    }else if(_current_day>day&&_current_year>year){
        qDebug()<<"pass";
        return  true;
    }else{
        qDebug()<<"didnt pass";
        return false;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int day,month,year;
    day=ui->calendarWidget->selectedDate().day();
    month=ui->calendarWidget->selectedDate().month();
    year=ui->calendarWidget->selectedDate().year();
    is_date_pass(day,month,year);
    qDebug()<<day<<" "<<_current_day<<month<<" "
           <<_current_month<<" "<<year<<_current_year<<" ";
}


void MainWindow::on_pushButton_6_clicked()
{
    check_overdue_struct();

}

void MainWindow::on_details_from_overdue_tasks_button_clicked()
{
    for(int i=0;i<=num4-1;i++){
        if(box4[i].first.isChecked()){
            int taskid=box4[i].second;
            taskdetailswindow m(taskid,"view_from_overdue_tasks",this,this);
            m.exec();
        }

    }
}

void MainWindow::on_delete_from_overdue_button_clicked()
{
    QMessageBox msgBox;
    int ret=msgBox.warning(this,tr("warning"),tr("Are you sure that you want to permanently delete the selected item(s)?"),QMessageBox::Ok,QMessageBox::Cancel);
     if(ret==QMessageBox::Ok){

    for(int i=0;i<=num4-1;i++){
        if(box4[i].first.isChecked()){
            box4[i].first.hide();
            box4[i].first.setChecked(false);
            delete_data_from_overdue_tasks(box4[i].second);
            delete_data_from_st_overdue_tasks(box4[i].second);

        }
    }
     }
}
void MainWindow::modify_checkbox_from_tasktable(int id,QString name){
    for(int i=0;i<num;i++){
        if(box[i].second==id){
            box[i].first.setText(name);
        }
    }
}
void MainWindow::modify_checkbox_from_done_tasks(int id,QString name){
    for(int i=0;i<num2;i++){
        if(box2[i].second==id){
            box2[i].first.setText(name);
        }
    }


}
void MainWindow::modify_checkbox_from_overdue_tasks(int id,QString name){
    for(int i=0;i<num4;i++){
        if(box4[i].second==id){
            box4[i].first.setText(name);
        }
    }
}
void MainWindow::modify_checkbox_from_today_tasks(int id,QString name){
    for(int i=0;i<num5;i++){
        if(box5[i].second==id){
            box5[i].first.setText(name);
        }
    }
}


void MainWindow::modify_checkbox_from_tasktable_st(int id,QString taskname,QString taskdetails,int day,int year,int month,int prioirty){
    for(int i=0;i<num3;i++){
        if(st_tasks[i].id==id){
            st_tasks[i].taskname=taskname;
            st_tasks[i].day=day;
            st_tasks[i].month=month;
            st_tasks[i].year=year;
            st_tasks[i].taskdetails=taskdetails;
            st_tasks[i].priority=prioirty;
        }
    }

}

void MainWindow::on_view_today_button_clicked()
{
    for(int i=0;i<=num5-1;i++){
        if(box5[i].first.isChecked()){
            int taskid=box5[i].second;
            taskdetailswindow m(taskid,"view_from_today_tasks",this,this);
            m.exec();
        }

    }

}
bool MainWindow::is_string_valid(QString &taskname){
    for(int i=0;i<taskname.size();i++){
        if(taskname[i]!=" "){

            taskname.remove(0,i);
            return true;
        }
    }
    return false;

}




void MainWindow::on_refresh_button_clicked()
{

}
void MainWindow::increment_num_of_today_tasks(){
    //num_of_tasks.today_num++;
}
void MainWindow::increment_num_of_all_tasks(){
    //num_of_tasks.alltasks_num++;
}

void MainWindow::increment_num_of_overdue_tasks(){
    //num_of_tasks.overdue_num++;
}

void MainWindow::on_check_all_structs_button_clicked()
{
    qDebug()<<"done struct"<<endl;

    check_done_struct();
    qDebug()<<endl<<"tasks struct"<<endl;
    check_tasks_struct();
    qDebug()<<endl<<"over due struct"<<endl;
    check_overdue_struct();
    qDebug()<<endl<<"today task  struct"<<endl;
    check_today_tasks_struct();



}void MainWindow::make_struct_status(QString str,int id){
    if(str=="done"){
        for(int i=0;i<=num3;i++){
            if(st_tasks[i].id==id){
                st_tasks[i].done=true;
                st_tasks[i].overdue=false;
                st_tasks[i].is_deleted=false;
                st_tasks[i].today=false;
            }

        }

    }else if(str=="overdue"){
        for(int i=0;i<=num3;i++){
            if(st_tasks[i].id==id){
                st_tasks[i].done=false;
                st_tasks[i].overdue=true;
                st_tasks[i].is_deleted=false;
                st_tasks[i].today=false;
            }
        }

    }else if(str=="today"){
        for(int i=0;i<=num3;i++){
            if(st_tasks[i].id==id){
                st_tasks[i].done=false;
                st_tasks[i].overdue=false;
                st_tasks[i].is_deleted=false;
                st_tasks[i].today=true;
            }
        }
    }else if(str=="delete"){
        for(int i=0;i<=num3;i++){
            if(st_tasks[i].id==id){
                st_tasks[i].done=false;
                st_tasks[i].overdue=false;
                st_tasks[i].is_deleted=true;
                st_tasks[i].today=false;
            }

        }


    }else if(str=="alltasks"){
        for(int i=0;i<=num3;i++){
            if(st_tasks[i].id==id){
                st_tasks[i].done=false;
                st_tasks[i].overdue=false;
                st_tasks[i].is_deleted=false;
                st_tasks[i].today=false;
            }

        }


    }
}
void MainWindow::take_date_from_done_tasks(int id,int &day,int &month,int &year){
    QSqlQuery query;
    query.prepare("SELECT day,month,year FROM done_tasks WHERE id=(:id)");
    query.bindValue(":id",id);
    query.exec();
    query.first();
    day=query.value(0).toInt();
    month=query.value(1).toInt();
    year=query.value(2).toInt();

}

void MainWindow::loadStyleSheet( QString sheet_name)
{
    QFile file(sheet_name);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(styleSheet);
}

void MainWindow::on_cmbTheme_currentIndexChanged(const QString &arg1)
{
    if (loaded==true)
    {
        fileName=ui->cmbTheme->currentText();
        QFile file(fileName);

        file.open(QIODevice::Text | QIODevice::ReadOnly);
        QString content;
        while(!file.atEnd())
            content.append(file.readLine());
        file.close();

        loadStyleSheet(ui->cmbTheme->currentText());

        QFile file2(pwd.toLatin1() +"/themes.txt");
        if(file2.open(QIODevice::ReadWrite | QIODevice::Text))// QIODevice::Append |
        {
            QTextStream stream(&file2);
            file2.seek(0);
            stream << "theme|" << ui->cmbTheme->currentText().toLatin1()<< endl;
            for (int i = 0; i < ui->cmbTheme->count(); i++) {
                stream << "theme|" << ui->cmbTheme->itemText(i) << endl;
            }
            file2.close();
        }

        if (ui->cmbTheme->currentText().toLatin1() != ""){
          //   ui->cmbTheme->currentText().toLatin1();
        }
    }
}



void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

