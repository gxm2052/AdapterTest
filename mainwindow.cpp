#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("适配器在线检测");
    //setWindowState(Qt::WindowMaximized);
    if(! initDB())
    {
        qDebug("init db failed!");
    }

    this->createMenu();

    this->ui->startButton->hide();
    this->ui->stopButton->hide();
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

    // 设置参数
    QSqlQuery query;
    query.prepare("select * from adapter where name=:name");
    query.bindValue(":name", strText);
    query.exec();

    while (query.next())
    {
        QString voltageLower = query.value(2).toString();
        QString voltageUpper = query.value(3).toString();
        QString currentLower = query.value(4).toString();
        QString currentUpper = query.value(5).toString();

        this->ui->voltageLowerLabel->setText("下限值： "+voltageLower + " V");
        this->ui->voltageUpperLabel->setText("上限值： "+voltageUpper + " V");
        this->ui->currentLowerLabel->setText("下限值： "+currentLower + " A");
        this->ui->currentUpperLabel->setText("上限值： "+currentUpper + " A");

        this->ui->startButton->show();
        return ;
    }
}

bool MainWindow::insertData()
{
//    if(!query.exec("INSERT INTO student (name, age) VALUES (\"TOM\", 10)")){
//    qDebug() << "INSERT Failed!";
//    }
}

void MainWindow::createMenu()
{
    QMenu *adapterMenu = menuBar()->addMenu(tr("适配器"));

    QSqlQuery query;
    query.exec("SELECT * from adapter");
    QString string;
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        //qDebug("id:%s name:%s", id, name);
        qDebug("id:%s, name:%s", qPrintable(id), qPrintable(name));

        QAction* action;
        action = new QAction(name, this);
        adapterMenu->addAction(action);
    }


    /*
    QAction *action;

    action = new QAction(tr("CQ15-140100-AG"), this);
    adapterMenu->addAction(action);

    action = new QAction(tr("CQ15-140100-AC"), this);
    adapterMenu->addAction(action);

    action = new QAction(tr("ZD12D140100-BS"), this);
    adapterMenu->addAction(action);
    */

    connect(adapterMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_choose(QAction*)));

    QMenu *configMenu = this->ui->menuBar->addMenu(tr("工具"));
    QAction *configAction;
    configAction = new QAction(tr("选项"), this);
    configMenu->addAction(configAction);
}

bool MainWindow::addActionToAdapterMenu(int id, QString name)
{
    return true;
}

void MainWindow::start_test()
{
    qDebug("start_test");
    this->ui->stopButton->show();
    this->ui->startButton->hide();
}

void MainWindow::stop_test()
{
    qDebug("stop_test");
    this->ui->stopButton->hide();
    this->ui->startButton->show();
}







