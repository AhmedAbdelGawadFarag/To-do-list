#include "form.h"
#include "ui_form.h"
#include<QMovie>
#include<QLabel>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QMovie *movie=new QMovie("C:/Users/ahmed/Desktop/ajax-loader.gif");
    ui->label->setMovie(movie);

    movie->start();
    //label1->show();
    //movie->deleteLater();
}

Form::~Form()
{
    delete ui;
}
