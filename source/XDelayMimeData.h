#ifndef			_X_DELAY_MIME_DATA_H_
#define			_X_DELAY_MIME_DATA_H_

#include <QMimeData>


// 拖动: 数据集
class XDelayMimeData : public QMimeData
{
Q_OBJECT

public:
	// constructor
	XDelayMimeData() noexcept;

	// destructor
	~XDelayMimeData() noexcept override;

private:
	// 是否已经请求数据
	mutable bool			memberRequestStatus;

	// 延迟目录
	QString				memberDelayDirectory;

public:
	// [get] 创建一个延迟目录
	static QString makeDelayDirectory() noexcept;

	// [set] 设置延迟目录
	virtual void setDelayDirectory(const QString& _Directory) noexcept final;

	// [set] 添加目录子项
	virtual void addDelayDir(const QString& _Name) noexcept final;

	// [set] 添加目录文件
	virtual void addDelayFile(const QString& _Name) noexcept final;

protected:
	// [opt] 检索数据
	QVariant retrieveData(const QString& _MimeType, QVariant::Type _Type) const override;

signals:
	// [signal] 请求数据
	void signalRequestData(const QString& _Directory) const;
};

#endif
