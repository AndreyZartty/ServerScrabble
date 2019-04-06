#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_iniciarButton_clicked();
    void on_comenzarButton_clicked();
    void on_scrabbleButton_clicked();
    void on_pasarButton_clicked();


private:

    Ui::MainWindow *ui;
    int SendJson(string boton);
    string getCodigo();
    void test();
};

#endif // MAINWINDOW_H
