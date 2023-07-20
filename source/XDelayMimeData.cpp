#include <source/XDelayMimeData.h>
#include <platform/XPlatformCommon.h>
#include <QDir>
#include <QUrl>
#include <QFile>



// constructor
XDelayMimeData::XDelayMimeData() noexcept : QMimeData()
{
	memberRequestStatus = false;
	memberDelayDirectory = XDelayMimeData::makeDelayDirectory();
}

// destructor
XDelayMimeData::~XDelayMimeData() noexcept = default;



// [get] 创建一个延迟目录
QString XDelayMimeData::makeDelayDirectory() noexcept
{
	auto		vTempDir = QDir::tempPath() + "/" + QString("%1").arg(rand(), 8, 16, QChar('0'));
	QDir(vTempDir).mkpath(vTempDir);
	return vTempDir;
}

// [set] 设置延迟目录
void XDelayMimeData::setDelayDirectory(const QString& _Directory) noexcept
{
	memberDelayDirectory = _Directory;
}

// [set] 添加目录子项
void XDelayMimeData::addDelayDir(const QString& _Name) noexcept
{
	auto		vNativePath = memberDelayDirectory + "/" + _Name;
	QDir(vNativePath).mkpath(vNativePath);
	this->setUrls(this->urls() << QUrl::fromLocalFile(vNativePath));
}

// [set] 添加目录文件
void XDelayMimeData::addDelayFile(const QString& _Name) noexcept
{
	auto		vNativePath = memberDelayDirectory + "/" + _Name;
	QFile		vHandle(vNativePath);
	if(vHandle.open(QIODevice::WriteOnly))
	{
		vHandle.close();
	}
	this->setUrls(this->urls() << QUrl::fromLocalFile(vNativePath));
}



// [opt] 检索数据
QVariant XDelayMimeData::retrieveData(const QString& _MimeType, QVariant::Type _Type) const
{
	// 当鼠标左键松开时，表示已经放下并请求数据，此时我们可以准备(下载/写入/编码)数据
	auto		vPress = xcc_platform_mouse_left_press();
	if(!vPress && !memberRequestStatus)
	{
		emit signalRequestData(memberDelayDirectory);
		memberRequestStatus = true;
	}
	return QMimeData::retrieveData(_MimeType, _Type);
}
