#ifndef VIEWWATCHLIST_H
#define VIEWWATCHLIST_H

#include <QObject>
#include <Views/View.h>
#include <Api/Card.h>

class ViewWatchlist : public View
{
public:
    explicit ViewWatchlist(QObject *parent = nullptr);
};

#endif // VIEWWATCHLIST_H
