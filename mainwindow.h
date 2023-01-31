#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QGroupBox>
#include<QVBoxLayout>
#include<QCheckBox>
#include<QtSql/QSqlDatabase>
#include<QSqlQuery>
#include<QPair>
#include<QString>
#include<QVector>
#include<QSystemTrayIcon>
extern QString m[];
extern int _current_year;
extern int _current_day;
extern int _current_month;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int tasknumber=0;
    bool closing;
        bool loaded=false;
        QString fileName;
            void loadStyleSheet(QString sheet_name);

    struct tasks{
        QString taskname;
        int id;
        int priority;
        int day;
        int month;
        int year;
        int num_of_task=0;
        QString taskdetails;
        bool done=false;
        bool is_deleted=false;
        bool overdue=false;
        bool today=false;
    }st_tasks[300];

    int num=0;
    int num2=0;
    int num3=0;
    int num4=0;
    int num5=0;
    //int _current_year;
    //int _current_day;
    //int _current_month;
    //نامبر 3 دا الحاجات الى محطوطه فى الاستراكت عشان انا خليت ستراكت واحد بس
    QPair<QCheckBox,int> box[500];
    QPair<QCheckBox,int> box2[500];
    QPair<QCheckBox,int> box4[500];
    QPair<QCheckBox,int> box5[500];

    QGroupBox *gbox=new QGroupBox;
    QGroupBox *gbox2=new QGroupBox;
    QGroupBox *gbox4=new QGroupBox;
    QGroupBox *gbox5=new QGroupBox;


    QVBoxLayout *vlayout=new QVBoxLayout;
    QVBoxLayout *vlayout2=new QVBoxLayout;
    QVBoxLayout *vlayout4=new QVBoxLayout;
    QVBoxLayout *vlayout5=new QVBoxLayout;

     void check_tasks_struct();
    void addtask(QString &taskname,QString taskdetails,int priority,int id,int day,int month,int year);
    int _giveid();
    void load_alltasks();
    void load_donetasks();
    int _return_last_id_from_tasks();
    int _return_last_id_from_donetasks();
    void _assign_checkbox_id(int id);
    void open_database();
    void delete_data_from_done_tasks(int id);
    void move_data_from_donetasks_to_tasks(int id);
    void put_checkbox_on_tasks_ui(QCheckBox &checkbox);
    void put_checkbox_on_done_tasks_ui(QCheckBox &checkbox);
    void move_data_form_st_tasks_to_st_donetasks(int id);
    void check_done_struct();
    void delete_data_from_st_tasks(int id);
    void delete_data_from_st_done_tasks(int id);
    void move_data_from_st_donetasks_to_st_tasks(int id);
    bool is_date_pass(int day,int month,int year);
    void put_checkbox_on_overdue_tasks_ui(QCheckBox &checkbox);
    int _return_last_id_from_overdue_tasks();
    void load_overdue_task();
    void check_overdue_struct();
    void delete_data_from_overdue_tasks(int id);
    void delete_data_from_st_overdue_tasks(int id);
   void move_data_form_st_overdue_tasks_to_st_donetasks(int id);
   void move_data_from_overdue_tasks_to_donetasks(int id);
   void move_data_from_st_overduetasks_to_st_tasks(int id);
   void delayed_tasks();
   void move_data_from_tasks_to_overdue_tasks(int id);
   void modify_checkbox_from_tasktable(int id,QString name);
void modify_checkbox_from_tasktable_st(int id,QString taskname,QString taskdetails,int day,int year,int month,int prioirty);
void modify_checkbox_from_done_tasks(int id,QString name);
void modify_checkbox_from_overdue_tasks(int id,QString name);
void put_checkbox_on_today_tasks_ui(QCheckBox &checkbox);
void move_data_from_tasks_to_today_tasks(int id);

void load_today_tasks();
int _return_last_id_from_today_tasks();
void modify_checkbox_from_today_tasks(int id,QString name);
void move_data_form_st_today_tasks_to_st_donetasks(int id);
void move_data_from_today_tasks_to_donetasks(int id);
void delete_data_from_today_tasks(int id);
void delete_data_from_st_today_tasks(int id);
void move_data_from_today_tasks_to_overdue_tasks(int id);
void increment_num_of_today_tasks();
void increment_num_of_all_tasks();
void increment_num_of_overdue_tasks();
void check_today_tasks_struct();
void make_struct_status(QString str,int id);

bool is_string_valid(QString &taskname);
void take_date_from_done_tasks(int id,int &day,int &month,int &year);
void move_data_from_donetasks_to_overdue_tasks(int id);
void move_data_from_st_donetasks_to_st_overdue_tasks(int id);

    QSqlDatabase sqldb;
int _check_box_id;
void modify_checkbox_from_tasktable_st(int id);
private slots:
    void on_pushButton_clicked();
    void on_deletebutton_clicked();
    void on_donebutton_clicked();
    void move_data_from_tasks_to_donetasks(int id);
    void delete_data_from_tasks(int id);
    void on_details_button_clicked();

    void on_delete_from_done_button_clicked();

    void on_details_from_done_tasks_button_clicked();

    void on_undone_button_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_search_by_name_button_clicked();

    void on_search_by_date_button_clicked();

    void on_search_by_priority_button_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_details_from_overdue_tasks_button_clicked();

    void on_delete_from_overdue_button_clicked();

    void on_donebutton_overdue_clicked();

    void on_view_today_button_clicked();

    void on_done_today_button_clicked();

    void on_delete_today_button_clicked();

    void on_refresh_button_clicked();

    void on_check_all_structs_button_clicked();

    void on_search_by_number_button_clicked();
    void on_cmbTheme_currentIndexChanged(const QString &arg1);

    void on_actionExit_triggered();
    void on_exit();
    void on_show();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // MAINWINDOW_H
