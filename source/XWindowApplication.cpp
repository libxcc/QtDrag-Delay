#include <source/XWindowApplication.h>
#include "ui_XWindowApplication.h"
#include <source/XDelayMimeData.h>
#include <QApplication>
#include <QMouseEvent>
#include <QDrag>
#include <QIcon>


// constructor
XWindowApplication::XWindowApplication(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XWindowApplication)
{
	ui->setupUi(this);

	this->setWindowIcon(QIcon(":/LOGO.ico"));
	this->setWindowTitle(tr(u8"QtDrag-Delay"));

	dragMousePress = false;

	QObject::connect(this, &XWindowApplication::signalFileDrag, this, &XWindowApplication::receiveFileDrag, Qt::QueuedConnection);
}

// destructor
XWindowApplication::~XWindowApplication() noexcept
{
	delete ui;
}



// [event] 鼠标按下
void XWindowApplication::mousePressEvent(QMouseEvent* _Event)
{
	if (_Event->buttons() & Qt::LeftButton)
	{
		dragMousePress = true;
		dragMousePoint = _Event->pos();
	}
	QWidget::mousePressEvent(_Event);
}

// [event] 鼠标抬起
void XWindowApplication::mouseReleaseEvent(QMouseEvent* _Event)
{
	dragMousePress = false;
	QWidget::mouseReleaseEvent(_Event);
}

// [event] 鼠标移动
void XWindowApplication::mouseMoveEvent(QMouseEvent* _Event)
{
	if(dragMousePress && (_Event->pos() - dragMousePoint).manhattanLength() < QApplication::startDragDistance())
	{
		emit signalFileDrag();
	}
	QWidget::mouseMoveEvent(_Event);
}

// [event] 鼠标移出
void XWindowApplication::leaveEvent(QEvent* _Event)
{
	dragMousePress = false;
	QWidget::leaveEvent(_Event);
}



// [receive] 拖拽
void XWindowApplication::receiveFileDrag() noexcept
{
	auto		vMimeData = new(std::nothrow) XDelayMimeData();
	QObject::connect(vMimeData, &XDelayMimeData::signalRequestData, this, &XWindowApplication::receiveDragData, Qt::DirectConnection);
	vMimeData->addDelayFile("LOGO.png");

	auto		vDrag = new(std::nothrow) QDrag(this);
	if(vDrag == nullptr)
	{
		return;
	}
	vDrag->setMimeData(vMimeData);
	vDrag->setPixmap(QPixmap(":/LOGO.png"));

	this->setAcceptDrops(false);
	vDrag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
	this->setAcceptDrops(true);
}

// [receive] 拖拽请求数据
void XWindowApplication::receiveDragData(const QString& _Directory) noexcept
{
	// 从资源中读取
	QFile		vHandleR(":/LOGO.png");
	if(!vHandleR.open(QIODevice::ReadOnly))
	{
		return;
	}
	auto		vBytes = vHandleR.readAll();
	vHandleR.close();

	// 写入本地文件
	auto		vFilePath = _Directory + "/" + "LOGO.png";
	QFile		vHandleN(vFilePath);
	if(!vHandleN.open(QIODevice::WriteOnly))
	{
		return;
	}
	vHandleN.write(vBytes);
	vHandleN.close();
}
