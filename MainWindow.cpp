#include "MainWindow.h"
#include <QtGui>
#include <iostream>

#include "preprocessdata.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
: QWidget(parent)
{

	textEdit = new QTextEdit;
	textEdit->setReadOnly(true);

	loadButton = new QPushButton(tr("&Load"));
	loadButton->show();
	quitButton = new QPushButton(tr("&Quit"));
	quitButton->show();

	connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(loadButton, Qt::AlignTop);
    buttonLayout1->addWidget(quitButton);
    buttonLayout1->addStretch();

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addLayout(buttonLayout1, 0, 0);
	mainLayout->addWidget(textEdit, 1, 1);
    setLayout(mainLayout);
    //setWindowTitle(tr("Simple Address Book"));
	//setCentralWidget(textEdit);
}

void MainWindow::loadFile(){
	std::cout << "load file funct" <<std::endl;

	 QString fileName = QFileDialog::getOpenFileName(this,
	         tr("Open Address Book"), "",
	         tr("Address Book (*.txt);;All Files (*)"));
	 if (fileName.isEmpty())
	          return;
	 else{
		 std::cout << fileName.toStdString() <<std::endl;
		 PreprocessData pd;
		 pd.loadDataFile(fileName.toStdString());
		 std::cout << "helllow: " << pd.my_data.docid.front() <<std::endl;

	 }

}

//void MainWindow::changeEvent(QEvent *e)
//{
//    QMainWindow::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        ui->retranslateUi(this);
//        break;
//    default:
//        break;
//    }
//}
//
//void MainWindow::startParsing()
//{
//    QFile file("./file.txt");
//
//    if (!file.open(QFile::ReadOnly))
//        return;
//
//    QTextStream ts(&file);
//
//    FrameElement *frameElement;
//    BoardElement *boardElement;
//
//    QChar ch;
//    int depth = 0;
//    int currentState = 0;
//    //states tell the parser which element it is parsing.
//    // 1 = Frame element
//    // 2 = BoardList element
//    // 3 = Board element
//    // 4 = Id element
//    // 5 = ame element (between "")
//
//    QList<int> stateList;
//
//    QString element = "";
//    do {
//        ts >> ch;
//
//        if (ch == '(') {
//            ++depth;
//
//            if (element == "Frame" || element == "frame") {
//                stateList.append(1);
//                frameElement = new FrameElement;
//                qDebug() << "Found a Frame element";
//            }
//            if (element == "BoardList" || element == "boardlist") {
//                stateList.append(2);
//                qDebug() << "Found a BoardList element";
//            }
//            if (element == "Board" || element == "board") {
//                stateList.append(3);
//                if (!frameElement) {
//                    qDebug() << "Parsing error: no frame element found!";
//                    return;
//                }
//                boardElement = new BoardElement;
//                frameElement->boardElements.append(boardElement);
//                qDebug() << "Found a Board element";
//            }
//            if (element == "Id" || element == "id" || element == "ID") {
//                stateList.append(4);
//                qDebug() << "Found an Id element";
//            }
//
//
//            element = "";
//        }
//        else if (ch == ')') {
//            --depth;
//
//            if (element.startsWith("\"")) {
//                if (stateList.count() < 2) {
//                    //parsing error, the list should have at least 2 items
//                    return;
//                }
//                int currentState = stateList.at(stateList.count() - 2); // Go back two states, the previous is the id, the one before the id
//                                                                        // tells wich object receives the name
//                qDebug() << "Found a name element in state " << currentState;
//
//                element = element.section("\"",1,1);
//                if (currentState == 3) {
//                    boardElement->id = element;
//                    qDebug() << "Set the board element id to:" << boardElement->id;
//                }
//
//            }
//
//            if (!stateList.isEmpty())
//                stateList.removeLast();
//            element = "";
//        }
//        else if (ch == '\r' || ch == '\n' || ch == ' ') {
//            // do nothing
//            // If you are able to use spaces in names, then create a boolean value to check if you're parsing a name.
//            // If you do (boolean = true), do not swallow spaces but add them to the parsed string.
//            // If you don't (boolean = false), swallow the spaces
//        }
//        else {
//            element += ch;
//        }
//    } while (!ts.atEnd());
//
//    file.close();
//}
