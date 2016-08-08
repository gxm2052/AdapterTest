#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_close();
    void on_choose(QAction* action);
    void start_test();
    void stop_test();
    void openSerialPort();
    void closeSerialPort();

    void writeData(const QByteArray &data);
    void readData();

private:
    void createMenu();
    bool initDB();
    bool insertData();
    bool addActionToAdapterMenu(int id, QString& name);

private:
    void initActionsConnections();
    void showStatusMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    SettingsDialog *settings;
    QLabel *status;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
