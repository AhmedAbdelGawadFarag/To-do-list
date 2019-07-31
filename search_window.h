#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include <QDialog>

namespace Ui {
class search_window;
}

class search_window : public QDialog
{
    Q_OBJECT

public:
    explicit search_window(int year,int month,int day,int id,int priority,QString taskname,QString taskdetails,int tasknumber,QWidget *parent = nullptr);
    ~search_window();
    QString _convert_to_string(int num);

private:
    Ui::search_window *ui;
};

#endif // SEARCH_WINDOW_H
