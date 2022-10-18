#ifndef VIRTUAL_MACHINE_GUI_HPP
#define VIRTUAL_MACHINE_GUI_HPP

#include "virtualMachine.hpp"

#include <string>
#include <fstream>
#include <bitset>
#include <cstdlib> 
#include <iostream>
#include <sstream>


#include <QFile>
#include <QChar>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QWidget>
#include <QVariant>
#include <QLineEdit>
#include <QTableView>
#include <QHeaderView>
#include <QTextCursor>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QTextBlockFormat>
#include <QAbstractTableModel>


enum modelType { registerTable, memoryTable };

class modelTable : public QAbstractTableModel
{
public:
	//Register Table
	modelTable(std::vector<std::string> memoryMap);
	//Memory Table
	modelTable(std::unordered_map<std::string, int32_t> registerMap);

	void updateRegisterTable(std::unordered_map<std::string, int32_t> registerMap);
	void updateMemoryTable(std::vector<std::string> memoryMap);

	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	modelType type;
	QVector<QVector<QString>> columns;

};
class VirtualMachineGUI: public QWidget{
	Q_OBJECT
private:
	bool isError = false;
	bool isRunning = false;
	int highlightedLineNumber;
	int nextLineNumber;

	QMainWindow* window;
	QWidget* widget;
	QVBoxLayout* layout;
	QHBoxLayout* mipsLayout;
	QHBoxLayout* statusLayout;
	QHBoxLayout* stepLayout;

	QPlainTextEdit* mipsText;
	QLabel* statusLabel;
	QLineEdit* statusLineEdit;
	QPushButton* stepButton;
	QTextCursor cursor;

	QPushButton* runButton;
	QPushButton* breakButton;
	

public: 
	//Table Contents
	virtualMachine* environment;
	QTableView* registerTable;
	modelTable* registerTableModel;
	QTableView* memoryTable;
	modelTable* memoryTableModel;


public slots:
	void runFunction();
	void stepFunction();
	void breakFunction();


public:

	VirtualMachineGUI(QWidget* parent = nullptr);
	~VirtualMachineGUI();
	void load(QString inputFile);
	void lineHighLighter();
	void intializeCursor();
	void intializeTables();
	void updateTables();
};


#endif
