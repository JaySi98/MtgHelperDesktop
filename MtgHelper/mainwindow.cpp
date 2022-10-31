#include <QSharedPointer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_connector()
{
    db_connector.connect_database();
    view_list = QList<QSharedPointer<View>>
    {
        QSharedPointer<ViewCardSearch>(new ViewCardSearch(this)),
    };

    ui->setupUi(this);

    connect(ui->action_search_cards,  &QAction::triggered, this, &MainWindow::set_card_serch_view);
    set_card_serch_view();
}

MainWindow::~MainWindow()
{
    db_connector.disconnect_database();
    delete ui;
}

void MainWindow::set_card_serch_view()
{
    setCentralWidget(view_list.at(0)->get_widget());
}

// 3. flipowanie obrazka
