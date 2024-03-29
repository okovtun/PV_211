#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

private slots:
	void on_horizontalSliderVolume_valueChanged(int value);

	void on_pushButtonOpen_clicked();
	void on_pushButtonPlay_clicked();
	void on_pushButtonPause_clicked();
	void on_pushButtonStop_clicked();

	void on_position_changed(qint64 value);
	void on_duration_changed(qint64 position);

	void on_horizontalSliderTrack_valueChanged(qint64 position);
	void on_horizontalSliderTrack_sliderMoved(int position);

private:
	Ui::Widget *ui;

	QMediaPlayer* m_player;

	QMediaPlaylist* m_playlist;
	QStandardItemModel* m_playlist_model;

};
#endif // WIDGET_H
