#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_close()
{
    this->close();
}

void MainWindow::on_choose(QAction* action)
{
    QString strText = action->text();    //根据text来判断具体的action操作
    this->ui->adapter_name->setText(strText);
}

void MainWindow::createMenu()
{
    QMenu *adapterMenu = menuBar()->addMenu(tr("适配器"));
    QAction *action;

    action = new QAction(tr("CQ15-140100-AG"), this);
    adapterMenu->addAction(action);

    action = new QAction(tr("CQ15-140100-AC"), this);
    adapterMenu->addAction(action);

    action = new QAction(tr("ZD12D140100-BS"), this);
    adapterMenu->addAction(action);

    connect(adapterMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_choose(QAction*)));

    QMenu *configMenu = this->ui->menuBar->addMenu(tr("配置"));

}







