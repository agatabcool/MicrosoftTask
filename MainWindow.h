#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>

 class MainWindow :public QWidget
 {
     Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);

private slots:
    // void open();
	void loadFile();

private:
	QPushButton *loadButton;
	QPushButton *quitButton;
	QTextEdit *textEdit;

};

#endif
