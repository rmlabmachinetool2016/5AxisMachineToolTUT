#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QMainWindow>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
namespace Ui{
class openglwindow;
}

class openglwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit openglwindow(QWidget *parent = 0);
    ~openglwindow();
    static boost::numeric::ublas::matrix<double> *GLdatalog;
    void ready(boost::numeric::ublas::matrix<double> *datalogptr);
private slots:
    void on_pushButton_Close_openglwindow_clicked();

private:
    boost::shared_ptr<Ui::openglwindow> window_GL;

};

#endif // OPENGLWINDOW_H
