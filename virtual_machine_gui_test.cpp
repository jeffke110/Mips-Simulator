#include <QTest>
#include <QPlainTextEdit>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

#include "virtual_machine_gui.hpp"

#include "test_config.hpp"
#include <chrono>
#include <thread>

class VirtualMachineGUITest : public QObject {
  Q_OBJECT

private slots:

  void initTestCase();
  void fileTestCase();
  void initTablesTestCase();
  void pcCounterTestCase();
  void memoryLayoutinitTestCase();
  void registerMapTestCase();
  void registerMapTestCaseTwo();
  void memoryMapTestCase();
  void branchCounterTestCase();
  void threadFunctionTestCase();
  //void threadFunctionTestCaseTwo();
private:

  VirtualMachineGUI widget;

};
// this section just verifies the object names and API
void VirtualMachineGUITest::fileTestCase() {

	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/fail00.asm"));
	auto statusViewWidget = widget.findChild<QLineEdit*>("status");
	QString statusString = statusViewWidget->text();
	QVERIFY2(statusString == QString::fromStdString("Error:0: no file exists"), "Error");

}
void VirtualMachineGUITest::initTablesTestCase() {

	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test00.asm"));
	QModelIndex blankIndex;

	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of columns in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 0, "Error wrong amount of columns in the register table");


}
void VirtualMachineGUITest::pcCounterTestCase() {
	VirtualMachineGUI widgetCounterTest;
	widgetCounterTest.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test11.asm"));
	auto stepButtonWidget = widgetCounterTest.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
	QModelIndex blankIndex;

	QVERIFY2(widgetCounterTest.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widgetCounterTest.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widgetCounterTest.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widgetCounterTest.memoryTableModel->rowCount(blankIndex) == 12, "Error wrong amount of rows in the memory table");


	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000000", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000001", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000002", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000003", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000004", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000005", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000006", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000007", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000008", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000009", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000a", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000b", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000c", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000d", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000e", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000f", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000010", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000011", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000012", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000013", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000014", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000015", "error");

}
void VirtualMachineGUITest::memoryLayoutinitTestCase() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test12.asm"));
	QModelIndex blankIndex;

	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 8, "Error wrong amount of rows in the memory table");

	QVERIFY2(widget.memoryTableModel->columns.at(1).at(0) == "0x02", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(1) == "0x00", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(2) == "0x00", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(3) == "0x00", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(4) == "0x01", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(5) == "0x00", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(6) == "0x00", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(7) == "0x40", "Error wrong memory layout");

}
void VirtualMachineGUITest::registerMapTestCase() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test13.asm"));
	auto stepButtonWidget = widget.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
	QModelIndex blankIndex;

	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 8, "Error wrong amount of rows in the memory table");

	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000003", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x0000000c", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(12) == "0x0000000a", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(13) == "0x00000008", "Error wrong memory layout");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000004", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x0000000c", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(12) == "0x0000000a", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(13) == "0x00000000", "Error wrong memory layout");

}
void VirtualMachineGUITest::registerMapTestCaseTwo() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test14.asm"));
	auto stepButtonWidget = widget.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
	QModelIndex blankIndex;

	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 8, "Error wrong amount of rows in the memory table");

	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000003", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x0000000c", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(12) == "0x0000000a", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(13) == "0xfffffff1", "Error wrong memory layout");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000004", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x0000000c", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(12) == "0x0000000a", "Error wrong memory layout");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(13) == "0xfffffff0", "Error wrong memory layout");

}
void VirtualMachineGUITest::memoryMapTestCase() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test02.asm"));
	auto stepButtonWidget = widget.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
	QModelIndex blankIndex;

	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 24, "Error wrong amount of rows in the memory table");

	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);

	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000007", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(0) == "0x07", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(4) == "0x07", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(8) == "0x07", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(12) == "0x07", "Error wrong memory layout");
	QVERIFY2(widget.memoryTableModel->columns.at(1).at(16) == "0x07", "Error wrong memory layout");


}
void VirtualMachineGUITest::branchCounterTestCase() {
	VirtualMachineGUI widgetCounterTest;
	widgetCounterTest.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test19.asm"));
	auto stepButtonWidget = widgetCounterTest.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
	QModelIndex blankIndex;

	QVERIFY2(widgetCounterTest.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widgetCounterTest.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widgetCounterTest.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	QVERIFY2(widgetCounterTest.memoryTableModel->rowCount(blankIndex) == 16, "Error wrong amount of rows in the memory table");


	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000000", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000007", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000008", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000a", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000b", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000d", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x0000000e", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000010", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000011", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000013", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000014", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000016", "error");
	QTest::mouseClick(stepButtonWidget, Qt::LeftButton);
	QVERIFY2(widgetCounterTest.registerTableModel->columns.at(2).at(0) == "0x00000017", "error");

}
void VirtualMachineGUITest::threadFunctionTestCase() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test05.asm"));
	
	auto runButtonWidget = widget.findChild<QPushButton*>("run");
	QVERIFY2(runButtonWidget, "Could not find QTableView widget for memory");
	
	auto breakButtonWidget = widget.findChild<QPushButton*>("break");
	QVERIFY2(breakButtonWidget, "Could not find QTableView widget for memory");

	QModelIndex blankIndex;
	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	//QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 24, "Error wrong amount of rows in the memory table");

	

	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000000", "error");

	QTest::mouseClick(runButtonWidget, Qt::LeftButton);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//QTest::mouseClick(breakButtonWidget, Qt::LeftButton);
	/*
	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000007", "error");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x00000004", "error");
	QVERIFY2(widget.registerTableModel->columns.at(2).at(12) == "0x00000007", "error");
	widget.close();
	*/
}
/*
void VirtualMachineGUITest::threadFunctionTestCaseTwo() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test19.asm"));

	auto runButtonWidget = widget.findChild<QPushButton*>("run");
	QVERIFY2(runButtonWidget, "Could not find QTableView widget for memory");

	auto breakButtonWidget = widget.findChild<QPushButton*>("break");
	QVERIFY2(breakButtonWidget, "Could not find QTableView widget for memory");

	QModelIndex blankIndex;
	QVERIFY2(widget.registerTableModel->columnCount(blankIndex) == 3, "Error wrong amount of columns in the register table");
	QVERIFY2(widget.registerTableModel->rowCount(blankIndex) == 35, "Error wrong amount of rows in the register table");

	QVERIFY2(widget.memoryTableModel->columnCount(blankIndex) == 2, "Error wrong amount of columns in the memory table");
	//QVERIFY2(widget.memoryTableModel->rowCount(blankIndex) == 4, "Error wrong amount of rows in the memory table");


	QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000000", "error");
	QTest::mouseClick(runButtonWidget, Qt::LeftButton);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	QTest::mouseClick(breakButtonWidget, Qt::LeftButton);
	
	widget.environment->userInputFunction("quit");
	widget.~VirtualMachineGUI();
	//QVERIFY2(widget.registerTableModel->columns.at(2).at(0) == "0x00000003", "error");
	//QVERIFY2(widget.registerTableModel->columns.at(2).at(11) == "0x00000001", "error");
	//QVERIFY2(widget.registerTableModel->columns.at(2).at(13) == "0x00000001", "error");
}

*/


void VirtualMachineGUITest::initTestCase() {
	VirtualMachineGUI widget;
	widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test00.asm"));

	auto textWidget = widget.findChild<QPlainTextEdit*>("text");
	QVERIFY2(textWidget, "Could not find QPLainText widget");

	auto registerViewWidget = widget.findChild<QTableView*>("registers");
	QVERIFY2(registerViewWidget, "Could not find QTableView widget for registers");

	auto memoryViewWidget = widget.findChild<QTableView*>("memory");
	QVERIFY2(memoryViewWidget, "Could not find QTableView widget for memory");

	auto statusViewWidget = widget.findChild<QLineEdit*>("status");
	QVERIFY2(statusViewWidget, "Could not find QLineEdit widget for status");

	auto stepButtonWidget = widget.findChild<QPushButton*>("step");
	QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");

}

QTEST_MAIN(VirtualMachineGUITest)
#include "virtual_machine_gui_test.moc"

