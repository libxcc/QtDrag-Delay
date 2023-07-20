#include <source/XWindowApplication.h>
#include <platform/XPlatformCommon.h>
#include <QApplication>



// 入口函数
int main(int _Argc, char** _Argv)
{
	xcc_platform_initialize();
	QApplication		vApplication(_Argc, _Argv);

	// QT的初始化工作
	qsrand((unsigned int)std::time(nullptr));

	// 创建并运行应用程序
	auto		vWindow = new(std::nothrow) XWindowApplication(nullptr);
	if(vWindow)
	{
		vWindow->show();
	}

	auto		vExec = QApplication::exec();
	xcc_platform_release();
	return vExec;
}
