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
        QSharedPointer<ViewWatchlist>(new ViewWatchlist(this)),
    };

    ui->setupUi(this);

    connect(ui->action_search_cards,  &QAction::triggered, this, &MainWindow::set_card_serch_view);
    connect(ui->action_watchlist,     &QAction::triggered, this, &MainWindow::set_watchlist_view);
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

void MainWindow::set_watchlist_view()
{
    setCentralWidget(view_list.at(1)->get_widget());
}
