#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QtCore>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void save_it();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void wrap_text();

    void enable_dark_mode();

    void save_settings();

    void load_settings();

    void on_actionBold_triggered();

    void switch_max_normal();

private:
    Ui::MainWindow *ui;
    QString file_path_;
};
#endif // MAINWINDOW_H
