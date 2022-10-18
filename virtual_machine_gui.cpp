#include "virtual_machine_gui.hpp"


VirtualMachineGUI::VirtualMachineGUI(QWidget* parent) : QWidget(parent) {
	environment = new virtualMachine();
	window = new QMainWindow();
	widget = new QWidget();
	layout = new QVBoxLayout();
	mipsLayout = new QHBoxLayout();
	statusLayout = new QHBoxLayout();
	stepLayout = new QHBoxLayout();

	mipsText = new QPlainTextEdit();
	mipsText->setObjectName("text");
	mipsText->setReadOnly(true);

	statusLabel = new QLabel("status");
	statusLineEdit = new QLineEdit();
	statusLineEdit->setReadOnly(true);
	statusLineEdit->setObjectName("status");

	stepButton = new QPushButton("step");
	stepButton->setObjectName("step");

	registerTable = new QTableView();
	registerTable->setObjectName("registers");
	registerTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");

	memoryTable = new QTableView();
	memoryTable->setObjectName("memory");
	memoryTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");


	runButton = new QPushButton("run");
	runButton->setObjectName("run");
	breakButton = new QPushButton("break");
	breakButton->setObjectName("break");

	window->setCentralWidget(widget);
	resize(800, 600);

	widget->setLayout(layout);

	mipsLayout->addWidget(mipsText);
	mipsLayout->addWidget(registerTable);
	mipsLayout->addWidget(memoryTable);
	layout->addLayout(mipsLayout);
	
	statusLayout->addWidget(statusLabel);
	statusLayout->addWidget(statusLineEdit);
	layout->addLayout(statusLayout);
	
	stepLayout->addWidget(stepButton);
	stepLayout->addWidget(runButton);
	stepLayout->addWidget(breakButton);
	layout->addLayout(stepLayout);

	setLayout(layout);

	connect(stepButton, SIGNAL(clicked()), this, SLOT(stepFunction()));
	connect(runButton, SIGNAL(clicked()), this, SLOT(runFunction()));
	connect(breakButton, SIGNAL(clicked()), this, SLOT(breakFunction()));

}
VirtualMachineGUI::~VirtualMachineGUI()
{
	if (isError == false) {
		environment->userInputFunction("quit");
		environment->labelsMap.clear();
		environment->memoryLayout.clear();
		environment->constantsMap.clear();
		environment->instructionList.clear();
		delete environment;
		environment = nullptr;
	}
	
}

modelTable::modelTable(std::unordered_map<std::string, int32_t> registerMap)
{
	type = registerTable;
	QVector<QString> registerNumber;
	QVector<QString> registerName;
	QVector<QString> registerHexValues;

	registerNumber.push_back("");
	registerNumber.push_back("");
	registerNumber.push_back("");
	for (int i = 0; i < 32; i++) {
		std::string tempRegister = "$" + std::to_string(i);
		registerNumber.push_back(QString::fromStdString(tempRegister));
	}

	registerName.push_back("$pc");
	registerName.push_back("$hi");
	registerName.push_back("$lo");
	registerName.push_back("$zero");
	registerName.push_back("$at");
	registerName.push_back("$v0");
	registerName.push_back("$v1");

	for (int i = 0; i < 4; i++) {
		std::string tempRegister = "$a" + std::to_string(i);
		registerName.push_back(QString::fromStdString(tempRegister));
	}
	for (int i = 0; i < 8; i++) {
		std::string tempRegister = "$t" + std::to_string(i);
		registerName.push_back(QString::fromStdString(tempRegister));
		}
	for (int i = 0; i < 8; i++) {
		std::string tempRegister = "$s" + std::to_string(i);
		registerName.push_back(QString::fromStdString(tempRegister));
	}

	registerName.push_back("$t8");
	registerName.push_back("$t9");
	registerName.push_back("$k0");
	registerName.push_back("$k1");
	registerName.push_back("$gp");
	registerName.push_back("$sp");
	registerName.push_back("$fp");
	registerName.push_back("$ra");
	
	QString registerHexValue;
	auto iterator = registerMap.find("$pc");
	registerHexValue = QString("0x%1").arg((int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	iterator = registerMap.find("$hi");
	registerHexValue = QString("0x%1").arg((int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	iterator = registerMap.find("$lo");
	registerHexValue = QString("0x%1").arg((int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	for (int i = 0; i < 32; i++) {
		std::string tempRegister = "$" + std::to_string(i);
		iterator = registerMap.find(tempRegister);
		registerHexValue = QString("0x%1").arg((int)(iterator->second), 8, 16, QChar('0'));
		registerHexValues.push_back(registerHexValue);
	}
	columns.push_back(registerNumber);
	columns.push_back(registerName);
	columns.push_back(registerHexValues);
	
}
modelTable::modelTable(std::vector<std::string> memoryMap) {
	type = memoryTable;
	QVector<QString> addressIndexes;
	QVector<QString> addressValues;
	for (unsigned i = 0; i < memoryMap.size(); i++) {
		QString address = QString("0x%1").arg((int)i, 8, 16, QLatin1Char('0'));
		addressIndexes.push_back(address);
	}
	columns.push_back(addressIndexes);
	for (unsigned i = 0; i < memoryMap.size(); i++) {
		std::string value = "0x" + memoryMap[i];
		addressValues.push_back(QString::fromStdString(value));
	}
	columns.push_back(addressValues);
	
}

void VirtualMachineGUI::load(QString inputFile) {
	std::string fileString = inputFile.toStdString();
	std::ifstream mipsStream;
	mipsStream.open(fileString);
	//Open File
	if (!mipsStream.is_open()) {
		std::cerr << "Error:0: no file exists" << std::endl;
		statusLineEdit->setText("Error:0: no file exists");
		isError = true;
	}
	else {
		//Open file in QT
		QFile qFile(inputFile);
		qFile.open(QFile::ReadOnly | QFile::Text);
		QTextStream qFileStream(&qFile);
		mipsText->setPlainText(qFileStream.readAll());
		//Parse File
		Parser mipsParser;
		if (mipsParser.parse(mipsStream)) {
			statusLineEdit->setText("Ok");
			//Set Maps and Check Main Label
			environment->setMaps(mipsParser);
			if (!environment->checkMainLabel()) {
				std::cerr << "Error:0: no main in text file" << std::endl;
				statusLineEdit->setText("Error:0: no main in text file");
				isError = true;
			}
			else {
				intializeCursor();
				intializeTables();
			}
		}
		else {
			QString error = QString::fromStdString(mipsParser.errorMessage);
			statusLineEdit->setText(error);
			isError = true;
		}
	}
}

void VirtualMachineGUI::intializeCursor() {
	//set up highlighter index
	std::unordered_map<std::string, labelType>::iterator findMainLabel = environment->labelsMap.find("main");
	highlightedLineNumber = findMainLabel->second.lineNumber;
	cursor = mipsText->textCursor();
	for (unsigned i = 0; i < unsigned(highlightedLineNumber); i++) {
		cursor.movePosition(QTextCursor::NextBlock);
	}
	QTextBlockFormat highlightedLine;
	highlightedLine.setBackground(Qt::yellow);
	cursor.select(QTextCursor::LineUnderCursor);
	cursor.setBlockFormat(highlightedLine);
	cursor.clearSelection();
	mipsText->setTextCursor(cursor);
}
void VirtualMachineGUI::intializeTables() {

	registerTableModel = new modelTable(environment->registersMap);
	memoryTableModel = new modelTable(environment->memoryLayout);
	registerTableModel->setObjectName("registerTableModel");
	memoryTableModel->setObjectName("memoryTableModel");
	
	registerTable->setModel(registerTableModel);
	registerTable->verticalHeader()->hide();
	
	registerTable->setColumnWidth(0, 60);
	registerTable->setColumnWidth(1, 60);
	registerTable->setColumnWidth(2, 100);
	registerTable->setFixedWidth(230);

	memoryTable->setModel(memoryTableModel);
	memoryTable->verticalHeader()->hide();
	memoryTable->setColumnWidth(0, 90);
	memoryTable->setColumnWidth(1, 90);
	memoryTable->setFixedWidth(180);
}

void modelTable::updateRegisterTable(std::unordered_map<std::string, int32_t> registerMap) {
	QVector<QString> registerHexValues;
	QString registerHexValue;
	auto iterator = registerMap.find("$pc");
	registerHexValue = QString("0x%1").arg((unsigned int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	iterator = registerMap.find("$hi");
	registerHexValue = QString("0x%1").arg((unsigned int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	iterator = registerMap.find("$lo");
	registerHexValue = QString("0x%1").arg((unsigned int)(iterator->second), 8, 16, QChar('0'));
	registerHexValues.push_back(registerHexValue);
	for (int i = 0; i < 32; i++) {
		std::string tempRegister = "$" + std::to_string(i);
		iterator = registerMap.find(tempRegister);
		registerHexValue = QString("0x%1").arg((unsigned int)(iterator->second), 8, 16, QChar('0'));
		registerHexValues.push_back(registerHexValue);
	}
	columns[2] = registerHexValues;
}
void modelTable::updateMemoryTable(std::vector<std::string> memoryMap) {
	QVector<QString> addressValues;
	for (unsigned i = 0; i < memoryMap.size(); i++) {
		addressValues.push_back(QString::fromStdString("0x" + memoryMap[i]));
	}
	columns[1] = addressValues;
}

void VirtualMachineGUI::updateTables() {
	QModelIndex blankIndex;
	QVariant blankRegister = QVariant(tr("registerModel"));
	QVariant blankMemory = QVariant(tr("memoryModel"));

	registerTableModel->updateRegisterTable(environment->registersMap);
	registerTableModel->setData(blankIndex, blankRegister, Qt::EditRole);

	memoryTableModel->updateMemoryTable(environment->memoryLayout);
	memoryTableModel->setData(blankIndex, blankRegister, Qt::EditRole);
}

int modelTable::rowCount(const QModelIndex& parent) const
{
	return columns[0].size();
}
int modelTable::columnCount(const QModelIndex& parent) const
{
	return columns.size();
}
QVariant modelTable::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) 
	{
		return columns[index.column()][index.row()];
	}
	return QVariant::Invalid; 
}
bool modelTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::EditRole) {
		emit dataChanged(index, index);
		return true;
	}
	return false;
}
QVariant modelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {

		if (section == 0) {
			if (type == registerTable)
				return QString("Number");
			else if (type == memoryTable)
				return QString("Address (Hex)");
		}
		else if (section == 1) {
			if (type == registerTable)
				return QString("Alias");
			else if (type == memoryTable)
				return QString("Value (Hex)");
		}
		else if (section == 2) {
			if (type == registerTable)
				return QString("Value (Hex)");
		}
	}
	return QVariant::Invalid;
}

void VirtualMachineGUI::stepFunction() {

	if (isRunning == false) {
		if (!environment->errorMessage.empty() || isError == true) {
			statusLineEdit->setText(QString::fromStdString(environment->errorMessage));
		}
		else if (unsigned(environment->pcRegister->second) == environment->instructionList.size() - 1) {
			environment->executeInstruction(environment->instructionList.at(environment->pcRegister->second));
			if (unsigned(environment->pcRegister->second) < environment->instructionList.size()) {
				nextLineNumber = environment->instructionList.at(environment->pcRegister->second).lineNumber - 1;
				lineHighLighter();
				updateTables();
			}
			else {
				lineHighLighter();
				updateTables();
				statusLineEdit->setText("Error: reached end of file");
			}
		}
		else if (unsigned(environment->pcRegister->second) < environment->instructionList.size() - 1) {
			environment->executeInstruction(environment->instructionList.at(environment->pcRegister->second));
			nextLineNumber = environment->instructionList.at(environment->pcRegister->second).lineNumber - 1;
			lineHighLighter();
			updateTables();
		}
	}
	else {
		statusLineEdit->setText("Error: currently running a process");
	}
}
void VirtualMachineGUI::runFunction() {
	
	if (isRunning == true) {
		statusLineEdit->setText("Error: currently running a process");
	}
	else if (environment->checkEndOfFile() && isError == false && isRunning == false) {
		environment->userInputFunction("run");
		isRunning = true;
	}
	else {
		statusLineEdit->setText("Error: has reached the end of the file");
	}
	
}
void VirtualMachineGUI::breakFunction() {
	
	if (isError == false && isRunning == true) {
		isRunning = false;
		environment->userInputFunction("break");
		statusLineEdit->clear();
		nextLineNumber = environment->instructionList.at(environment->pcRegister->second).lineNumber - 1;
		lineHighLighter();
		updateTables();
	}
	else if (isRunning == false) {
		statusLineEdit->setText("Error: no process is running");
	}
	else {
		statusLineEdit->setText("Error: has reached the end of the file");
	}
	
	

}
void VirtualMachineGUI::lineHighLighter() {
	QTextBlockFormat unHighLightLine;
	unHighLightLine.setBackground(Qt::white);
	cursor.select(QTextCursor::LineUnderCursor);
	cursor.setBlockFormat(unHighLightLine);
	cursor.clearSelection();
	mipsText->setTextCursor(cursor);
	int difference = nextLineNumber - highlightedLineNumber;

	if (difference > 0) {
		for (int i = highlightedLineNumber; i < nextLineNumber; i++) {
			cursor.movePosition(QTextCursor::NextBlock);
		}
		highlightedLineNumber = nextLineNumber;

	}
	else if(difference < 0){
		for (int i = highlightedLineNumber; i > nextLineNumber; i--) {
			cursor.movePosition(QTextCursor::PreviousBlock);
		}
		highlightedLineNumber = nextLineNumber;
	}

	QTextBlockFormat highlightedLine;
	highlightedLine.setBackground(Qt::yellow);
	cursor.select(QTextCursor::LineUnderCursor);
	cursor.setBlockFormat(highlightedLine);
	cursor.clearSelection();
	mipsText->setTextCursor(cursor);
}
