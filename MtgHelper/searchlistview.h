#ifndef SEARCHLISTVIEW_H
#define SEARCHLISTVIEW_H

#include <QObject>

class SearchListView: public QObject
{
    Q_OBJECT

public:
    explicit SearchListView(QObject* parent = nullptr);
};

#endif // SEARCHLISTVIEW_H
