#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSharedPointer>

#include <Api/apiconnector.h>
#include <Views/ViewCardSearch.h>
#include <Api/Card.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void set_card_serch_view();

private:
    Ui::MainWindow *ui;
    QList<QSharedPointer<View>> view_list;
};
#endif // MAINWINDOW_H
