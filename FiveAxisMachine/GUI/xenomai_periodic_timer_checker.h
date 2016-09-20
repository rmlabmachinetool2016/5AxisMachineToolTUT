#ifndef XENOMAI_PERIODIC_TIMER_CHECKER_H
#define XENOMAI_PERIODIC_TIMER_CHECKER_H

#include <QMainWindow>
#include <stdio.h>
#include <signal.h>
#include <boost/shared_ptr.hpp>
#if basesystem == 0
#include <unistd.h>
#endif
namespace Ui {
class Xenomai_periodic_timer_checker;
}

class Xenomai_periodic_timer_checker : public QMainWindow
{
    Q_OBJECT

public:
    explicit Xenomai_periodic_timer_checker(QWidget *parent = 0);
    ~Xenomai_periodic_timer_checker();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_stop2_clicked();

private:
    boost::shared_ptr<Ui::Xenomai_periodic_timer_checker> ui;
};

#endif // XENOMAI_PERIODIC_TIMER_CHECKER_H
