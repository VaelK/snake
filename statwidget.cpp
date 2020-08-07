#include "statwidget.h"
#include "ui_statwidget.h"
#include "QStackedWidget"
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QGroupBox>
using namespace QtCharts;

StatWidget::StatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->leaveStatButt,
                     SIGNAL(pressed()),
                     this, SIGNAL(toGameWidget()));
    this->parent = parent;
    QObject::connect(ui->changeView,
                     SIGNAL(pressed()),
                     this, SLOT(switchWidget()));
//    this->switchWidget();
}

StatWidget::~StatWidget()
{
    delete ui;
}

void StatWidget::refreshPlot(){

    this->requestActorList();
}

void StatWidget::getActorList(QList<Actor*> actorList){
    //Creating the layout
    QHBoxLayout *layout = new QHBoxLayout;
    // First diagram: Best score
    QBarSeries *serieBestScore = new QBarSeries();
    QBarSet *set0 = new QBarSet("Score");
    QBarSet *set1 = new QBarSet("Actions joués");
    QStringList xlabels;
    int bestScore = 0;
    int maxTrain = 0;
    for (int i=0; i<actorList.length(); i++){
        Actor *actor = actorList[i];
        *set0 << actor->getBestScore();
        *set1 << actor->getTotalNumAction();
        xlabels << actor->getName();
        if (actor->getBestScore() > bestScore)
            bestScore = actor->getBestScore();
        if (actor->getTotalNumAction() > maxTrain)
            maxTrain = actor->getTotalNumAction();
    }
    serieBestScore->append(set0);
    QChart *chartScore = new QChart();
    chartScore->addSeries(serieBestScore);
    chartScore->setTitle("Satitiques des scores");
    chartScore->setAnimationOptions(QChart::SeriesAnimations);

    //xAxis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(xlabels);
    chartScore->addAxis(axisX, Qt::AlignBottom);
    serieBestScore->attachAxis(axisX);

    //yaxis
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,bestScore);
    chartScore->addAxis(axisY, Qt::AlignLeft);
    serieBestScore->attachAxis(axisY);

    chartScore->legend()->setVisible(true);
    chartScore->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartViewScore = new QChartView(chartScore);
    chartViewScore->setRenderHint(QPainter::Antialiasing);
    //Adding the graph to the horizontal layout
    layout->addWidget(chartViewScore);

    // Second diagram: Training time
    QBarSeries *serieTrainTime = new QBarSeries();
    serieTrainTime->append(set1);
    QChart *chartTrain = new QChart();
    chartTrain->addSeries(serieTrainTime);
    chartTrain->setTitle("Satitiques des temps d'entrainement");
    chartTrain->setAnimationOptions(QChart::SeriesAnimations);

    //xaxis
    QBarCategoryAxis *axisXTrain = new QBarCategoryAxis();
    axisXTrain->append(xlabels);
    chartTrain->addAxis(axisXTrain, Qt::AlignBottom);
    serieTrainTime->attachAxis(axisXTrain);
    //yaxis
    QValueAxis *axisYTrain = new QValueAxis();
    axisYTrain->setRange(0,maxTrain);
    chartTrain->addAxis(axisYTrain, Qt::AlignLeft);
    serieTrainTime->attachAxis(axisYTrain);

    chartTrain->legend()->setVisible(true);
    chartTrain->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartViewTrain = new QChartView(chartTrain);
    chartViewTrain->setRenderHint(QPainter::Antialiasing);
    //Adding the graph to the horizontal layout
    layout->addWidget(chartViewTrain);

    this->ui->stackedWidget->removeWidget(this->ui->stackedWidget->widget(1));
    QGroupBox *horizontalGroupBox = new QGroupBox();
    horizontalGroupBox->setLayout(layout);
    this->ui->stackedWidget->addWidget(horizontalGroupBox);
}

void StatWidget::switchWidget(){
    if (this->ui->stackedWidget->currentIndex()==0){
        ui->stackedWidget->setCurrentIndex(1);
        ui->changeView->setText("Table");
    }else{
        ui->stackedWidget->setCurrentIndex(0);
        ui->changeView->setText("Graphique");
    }
}

void StatWidget::toStatsWidget(){
    this->refreshPlot();
}
