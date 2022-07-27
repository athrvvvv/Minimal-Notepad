#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QClipboard>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_settings();
    this->setCentralWidget(ui->textEdit);
    connect(ui->actionWord_wrap, &QAction::toggled, [=]{
        wrap_text();
    });
    connect(ui->actionDark_mode, &QAction::toggled, [=]{
        enable_dark_mode();
    });
    switch_max_normal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","File not opened");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

// IF FILE IS NOT SAVED
void MainWindow::save_it() {
    //("Text files (*.txt)")
    QString file_name = QFileDialog::getSaveFileName(this,"Save file", QDir::currentPath(), "Text files (*.txt);;All files (*.*)", new QString("Text files (*.txt)"));
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this,"..","File not saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::information(this,"..","File not saved");
        save_it();
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    //("Text files (*.txt)")
    QString file_name = QFileDialog::getSaveFileName(this,"Save file", QDir::currentPath(), "Text files (*.txt);;All files (*.*)", new QString("Text files (*.txt)"));
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        //QMessageBox::information(this,"..","File not saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::wrap_text(){
    if (ui->actionWord_wrap->isChecked() == false){
        QString text = ui->textEdit->toPlainText();
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        ui->textEdit->setPlainText(text);
    }
    else if (ui->actionWord_wrap->isChecked() == true){
        QString text = ui->textEdit->toPlainText();
        ui->textEdit->setLineWrapMode(QTextEdit::FixedColumnWidth);
        ui->textEdit->setLineWrapColumnOrWidth(200);
        ui->textEdit->setPlainText(text);

    }
    save_settings();
}

void MainWindow::enable_dark_mode(){
    if (ui->actionDark_mode->isChecked() == true){
        qDebug() << "ENABLE DARK MODE TRUE";
        QString program_dir("");
        program_dir = qApp->applicationDirPath();
        QDir D;
        D.setCurrent(program_dir);
        QFile f("darkstyle.qss");
        if ( !f.exists() )
        {
           qWarning() << "Unable to set dark stylesheet, file not found";
        }
        else
        {
           f.open( QFile::ReadOnly | QFile::Text );
           QTextStream ts( &f );
           qApp->setStyleSheet( ts.readAll() );
        }
    }
    else if (ui->actionDark_mode->isChecked() == false) {
        QString program_dir("");
        program_dir = qApp->applicationDirPath();
        QDir D;
        D.setCurrent(program_dir);
        QFile f("lightstyle.qss");
        if (!f.exists()){
            qWarning() << "Unable to set light stylesheet, file not found";
        }
        else{
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
        }
    }
    save_settings();
}

void MainWindow::save_settings(){
    //SAVE SETTINGS FOR DARK MODE
    QSettings setting("MyCompany","Minimal-Notepad");
    setting.beginGroup("Dark_mode");
    if (ui->actionDark_mode->isChecked() == true){
        setting.setValue("status",true);
    }

    else if (ui->actionDark_mode->isChecked() == false){
        setting.setValue("status",false);
    }
    setting.endGroup();
    //SAVE SETTINGS FOR WORD WRAP
    QSettings setting1("MyCompany","Minimal-Notepad");
    setting1.beginGroup("Word_Wrap");
    if (ui->actionWord_wrap->isChecked() == true){
        setting1.setValue("status",true);
    }

    else if (ui->actionWord_wrap->isChecked() == false){
        setting1.setValue("status",false);
    }
    setting1.endGroup();
    qDebug() << "Saved settings";
}

void MainWindow::load_settings(){
    //LOAD SETTINGS FOR DARK MODE
    QSettings setting("MyCompany","Minimal-Notepad");
    setting.beginGroup("Dark_Mode");
    QString status = setting.value("status").toString();
    qDebug() << status;
    if (status == "true"){
        qDebug() << "DARK MODE IS ON";
        ui->actionDark_mode->setChecked(true);
        enable_dark_mode();
    }
    else if  (status == "false"){
        qDebug() << "DARK MODE IS OFF";
        ui->actionDark_mode->setChecked(false);
        enable_dark_mode();
    }
    setting.endGroup();
    //LOAD SETTINGS FOR WORD WRAP
    QSettings setting1("MyCompany","Minimal-Notepad");
    setting1.beginGroup("Word_Wrap");
    QString status_ww = setting1.value("status").toString();
    qDebug() << status_ww;
    if (status_ww == "true"){
        qDebug() << "WORD WRAP IS ON";
        ui->actionWord_wrap->setChecked(true);
        enable_dark_mode();
    }
    else if  (status_ww == "false"){
        ui->actionWord_wrap->setChecked(false);
        qDebug() << "WORD WRAP IS OFF";
    }
    setting1.endGroup();

}

void MainWindow::on_actionBold_triggered()
{
//    QFont font = ui->textEdit->font();
//    font.setWeight(QFont::Bold); // or
//    ui->textEdit->setFont(font);
        ui->textEdit->copy();
        QClipboard* pClip = QApplication::clipboard();
        QString str = pClip->text(QClipboard::Clipboard);

        QString sFullString = ui->textEdit->toPlainText();
        int pos = ui->textEdit->textCursor().position();

        pos -= str.length();
        QString str1 = "<html><b>" + str + "</b></html>";
        sFullString.replace(pos, str.length(), str1);

        ui->textEdit->setText(sFullString);
}

void MainWindow::switch_max_normal(){
    if(isMaximized()){
        showNormal();
    }
    else{
        showMaximized();
    }
}

