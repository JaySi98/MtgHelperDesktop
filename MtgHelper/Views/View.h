#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>

class View : public QObject
{
    Q_OBJECT
public:
    explicit View(QObject *parent = nullptr);
//    virtual ~View() = 0;

    QWidget* get_widget();

signals:
    void signal(void);

protected:
    QWidget* main_widget;

};
#endif // VIEW_H
