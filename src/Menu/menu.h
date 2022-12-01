#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_joinMatchButton_clicked();

    void on_createButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::Menu *ui;
};
#endif // MENU_H
