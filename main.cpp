//#include "boost/filesystem.hpp"
//#include <iostream>
//#include <QtGui>
//#include "MainWindow.h"
//
//namespace fs = boost::filesystem;
//
//#include <QApplication>
//#include <QWidget>
//#include <QPushButton>



//class MyButton : public QWidget
//{
// public:
//     MyButton(QWidget *parent = 0);
//     void loadFromFile();
// private slots:
//     void handleButton();
// private:
//     QPushButton *load;
//};
//
//
//MyButton::MyButton(QWidget *parent)
//    : QWidget(parent)
//{
//  QPushButton *quit = new QPushButton("Quit", this);
//  load = new QPushButton("Load File", this);
//  load->setGeometry(50, 40, 75, 30);
//
//  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
//  connect(load, SIGNAL(released()), this, SLOT(handleButton()));
//}
//
//void MyButton::handleButton()
//{
//	std::cout << "hellow my button" <<std::endl;
//	load = new QPushButton("My Button", this);
//    // change the text
//	load->setText("Example");
//    // resize button
//	load->resize(100,100);
//}
//
//void MyButton::loadFromFile(){
//}

//int main(int argc, char *argv[])
//{
//  QApplication app(argc, argv);
//
//  MyButton window;
//
//  window.resize(250, 150);
//  window.move(300, 300);
//  window.setWindowTitle("button");
//  window.show();
//
//  return app.exec();
//}

#include "MainWindow.h"

#include <QtGui/QApplication>
//#include <QApplication> //For Qt5

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(250, 150);
    mainWindow.setWindowTitle("Simple menu");
    mainWindow.show();
    return app.exec();
}
