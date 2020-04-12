#include "selectactorwidget.h"
#include "ui_selectactorwidget.h"

SelectActorWidget::SelectActorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectActorWidget)
{
    ui->setupUi(this);
}

SelectActorWidget::~SelectActorWidget()
{
    delete ui;
}
