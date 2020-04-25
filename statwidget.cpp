#include "statwidget.h"
#include "ui_statwidget.h"
#include "QStackedWidget"

StatWidget::StatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->leaveStatButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toGameWidget()));
    this->parent = parent;
}

StatWidget::~StatWidget()
{
    delete ui;
}
