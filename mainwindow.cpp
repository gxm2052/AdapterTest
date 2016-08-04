#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(! initDB())
    {
        qDebug("init db failed!");
    }

    this->createMenu();
}

bool MainWindow::initDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("adapters.sqlite"); // 数据库名与路径, 此时是放在同目录下,调试时路径不一样
    if (!db.open())
    {
        qDebug("datebase not opened!");
        return false;
    }

    // 创建数据表
    QSqlQuery query;
    bool ok = false;
    ok = query.exec("CREATE TABLE IF NOT EXISTS adapter (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "name VARCHAR(30) NOT NULL,"
                         "voltage_lower float,"
                         "voltage_upper float,"
                         "current_lower float,"
                         "current_upper float"
                         ")");
    if(!ok)
    {
        qDebug("create table adapter failed!");
        return false;
    }

    ok = query.exec("CREATE TABLE IF NOT EXISTS sample (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "type INTEGER, "
                         "voltage float, "
                         "current float, "
                         "result boolean, "
                         "test_time date"
                         ")");
    if(!ok)
    {
        qDebug("create table sample failed! ");
    }

    return true;
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
    // todo
}







