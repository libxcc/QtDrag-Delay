#ifndef			_X_WINDOW_X_H_
#define			_X_WINDOW_X_H_

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XWindowApplication;
}
QT_END_NAMESPACE

// 主界面
class XWindowApplication : public QWidget
{
Q_OBJECT

public:
	// constructor
	explicit XWindowApplication(QWidget* _Parent) noexcept;

	// destructor
	~XWindowApplication() noexcept override;

private:
	// UI
	Ui::XWindowApplication*			ui;

	// 按下状态
	bool					dragMousePress;

	// 按下坐标
	QPoint					dragMousePoint;

protected:
	// [event] 鼠标按下
	void mousePressEvent(QMouseEvent* _Event) override;

	// [event] 鼠标抬起
	void mouseReleaseEvent(QMouseEvent* _Event) override;

	// [event] 鼠标移动
	void mouseMoveEvent(QMouseEvent* _Event) override;

	// [event] 鼠标移出
	void leaveEvent(QEvent* _Event) override;

signals:
	// [signal] 拖拽开始
	void signalFileDrag();

public slots:
	// [receive] 拖拽
	virtual void receiveFileDrag() noexcept final;

	// [receive] 拖拽请求数据
	virtual void receiveDragData(const QString& _Directory) noexcept final;
};


#endif
