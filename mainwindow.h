#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void wyswietl();
    void powieksz();
    void pomniejsz();
    void reset();
    void about();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void RedrawImage();
    QString image_name;
    float image_resize_ratio;
};

#endif // MAINWINDOW_H
