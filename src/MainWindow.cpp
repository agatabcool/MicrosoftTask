#include "MainWindow.h"
#include <QtGui>
#include <iostream>
#include "processdata.h"
#include <QSignalMapper>
#include <numeric>

#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
: QWidget(parent), pd(NULL)
{

	textEdit = new QTextEdit;
	textEdit->setReadOnly(true);

	loadButton = new QPushButton(tr("&Load"));
	loadButton->show();
	plotRelevButton = new QPushButton(tr("&Plot Relev"));
	plotRelevButton->show();
	quitButton = new QPushButton(tr("&Quit"));
	quitButton->show();

	customPlot = new QCustomPlot(this);

	connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
	connect(plotRelevButton, SIGNAL(clicked()), this, SLOT(plotRelev()));
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(loadButton, Qt::AlignTop);
    buttonLayout1->addWidget(plotRelevButton);
    buttonLayout1->addWidget(quitButton);
    buttonLayout1->addStretch();

    /*int m=9;
    QSignalMapper *mapper = new QSignalMapper( this );
    connect( plotRelevButton, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( mapper, SIGNAL(mapped(int)), this, SLOT(plotRelev(int)) );*/

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addLayout(buttonLayout1, 0, 0);
	mainLayout->addWidget(textEdit, 0, 1);

	customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	//layout->addWidget(button6,1,1,2,2);
	mainLayout->addWidget(customPlot, 1,0,1,2);
    setLayout(mainLayout);
    //setWindowTitle(tr("Simple Address Book"));
	//setCentralWidget(textEdit);
}

void MainWindow::loadFile(){
	std::cout << "load file funct" <<std::endl;
	textEdit->clear();

	std::cout << pd << std::endl;
	if (!pd){
		std::cout  << "new instance" << std::endl;
		pd = new PreprocessData();
	}
	else{
		pd->parsed_data = ParsedData();
	}

	 QString fileName = QFileDialog::getOpenFileName(this,
	         tr("Open Address Book"), "",
	         tr("Address Book (*.txt);;All Files (*)"));
	 if (fileName.isEmpty())
	          return;
	 else{
		 std::cout << fileName.toStdString() <<std::endl;
		 pd->loadDataFile(fileName.toStdString());
	 }

	 printSummary();
	 plotRelevPD();

	 std::cout << "end of load file " << std::endl;
}

void MainWindow::plotRelevPD(){
	std::cout << "plotRelevPD " <<std::endl;
	//std::cout << pd.my_data.relev.size() << std::endl;

	customPlot->clearGraphs();
	relevPd_plot = new QCPBars(customPlot->xAxis, customPlot->yAxis);
	customPlot->addPlottable(relevPd_plot);
	QPen pen;
	pen.setWidthF(1.2);
	relevPd_plot->setName("Fossil fuels");
	relevPd_plot->setPen(pen);
	relevPd_plot->setBrush(QColor(255, 131, 0, 50));

	// prepare x axis with country labels:
//	QVector<double> ticks;
//	QVector<QString> labels;
//	//Unique queries
//	//std::vector<std::string> temp_qid = pd.my_data->qid;
//	//temp_qid.erase( std::unique( temp_qid.begin(), temp_qid.end() ), temp_qid.end() );
//
//	//int i=1;
//	//for (std::vector<std::string>::iterator it = temp_qid.begin() ; it != temp_qid.end(); ++it){
//	for(int i=1; i<16; i++){
//		ticks[i]= i;
//		//QString qstr = QString::fromStdString(*it);
//		//labels.push_back(qstr);
//		//i++;
//	}
	QVector<double> ticks;
	QVector<QString> labels;

	int i=0;
	for (std::vector<std::string>::iterator it = pd->parsed_data.data_stats.uniq_docs.begin() ; it != pd->parsed_data.data_stats.uniq_docs.end(); ++it){
		QString qstr = QString::fromStdString(*it);
		labels.push_back(qstr);
		ticks.push_back(i+1);
		i++;
	}

	customPlot->xAxis->setAutoTicks(false);
	customPlot->xAxis->setAutoTickLabels(false);
	customPlot->xAxis->setTickVector(ticks);
	customPlot->xAxis->setTickVectorLabels(labels);
	customPlot->xAxis->setTickLabelRotation(-60);
//	customPlot->xAxis->setSubTickCount(0);
//	customPlot->xAxis->setTickLength(0, 4);
//	customPlot->xAxis->grid()->setVisible(true);
//	customPlot->xAxis->setRange(0, 20);
////
////	// prepare y axis:
//	customPlot->yAxis->setRange(0, 40);
//	customPlot->yAxis->setPadding(5); // a bit more space to the left border
	customPlot->yAxis->setLabel("Number of Relevant \nDocuments per Query");
//	customPlot->yAxis->grid()->setSubGridVisible(true);
//	QPen gridPen;
//	gridPen.setStyle(Qt::SolidLine);
//	gridPen.setColor(QColor(0, 0, 0, 25));
//	customPlot->yAxis->grid()->setPen(gridPen);
//	gridPen.setStyle(Qt::DotLine);
//	customPlot->yAxis->grid()->setSubGridPen(gridPen);
//
//	//add data
//	//pd.my_data->data_stats.rel_per_query;
//	std::vector<double> v_double(pd.my_data->data_stats.rel_per_query.begin(), pd.my_data->data_stats.rel_per_query.end());
//	QVector<double> x = QVector<double>::fromStdVector(v_double);
//	//QVector<double>; // initialize with entries 0..100

	QVector<double> valueData;
//	for (int i=0; i<15; i++){
//		std::cout << i+1 << std::endl;
//		valueData.push_back(2*(i+1));
//	}

	//int i=0;
	for (std::vector<int>::iterator it = pd->parsed_data.data_stats.rel_per_query.begin() ; it != pd->parsed_data.data_stats.rel_per_query.end(); ++it){
		//QString qstr = QString::fromStdString(*it);
		valueData.push_back(double(*it));
		std::cout <<"vallhere" << valueData.back() << std::endl;
		//ticks.push_back(i+1);
		//i++;
	}

	//valueData.push_back(rel_per_query)

	relevPd_plot->setData(ticks, valueData);


	customPlot->rescaleAxes();
	customPlot->replot();

	std::cout << "end of PlotRelevancePD" <<std::endl;

}

void MainWindow::plotRelev(){
	std::cout << "plotRelev " <<std::endl;
	//std::cout << pd.my_data.relev.size() << std::endl;

	QVector<double> x, y; // initialize with entries 0..100

	ProcessData prd;
	prd.PlotRelevance(x,y, pd);

//	// create graph and assign data to it:
	customPlot->addGraph();
	customPlot->graph(0)->setData(x, y);
	// give the axes some labels:
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	customPlot->xAxis->setRange(-1, 1);
	customPlot->yAxis->setRange(0, 1);
	customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, 5));
	customPlot->replot();//`enter code here`
}

void MainWindow::printSummary(){
	textEdit->append("Statistics for loaded file: ");
	//std::cout << "num_queries 222: " << ds.num_feats<< std::endl;
	textEdit->append(QString("Total queries: %1").arg(pd->parsed_data.data_stats.num_queries));
	textEdit->append(QString("Unique queries: %1").arg(pd->parsed_data.data_stats.uniq_queries.size()));
	textEdit->append(QString("Number of unique docs: %1").arg(pd->parsed_data.data_stats.uniq_docs.size()));

	//get avg no docs
	double avg_doc= std::accumulate(pd->parsed_data.data_stats.docperquery.begin(), pd->parsed_data.data_stats.docperquery.end(), 0.0) / pd->parsed_data.data_stats.docperquery.size();
	textEdit->append(QString("Average docs per query: %1").arg(avg_doc));

	textEdit->append(QString("Total relevant queries: %1").arg(pd->parsed_data.data_stats.rev_queries));
	textEdit->append(QString("Number of features per query: %1").arg(pd->parsed_data.data_stats.num_feats));
	//textEdit->setText("Number of documents per query: ");
}
