#include "Widget.h"
#include "ui_Widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>
#include <QTime>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);

	ui->pushButtonPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
	ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	ui->pushButtonPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	ui->pushButtonNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

	m_player = new QMediaPlayer(this);
	m_player->setVolume(70);

	ui->labelVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
	ui->horizontalSliderVolume->setValue(m_player->volume());

	connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::on_position_changed);
	connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::on_duration_changed);

	////////////////////////			Playlist			////////////////////////
	m_playlist_model = new QStandardItemModel(this);
	ui->playlistView->setModel((m_playlist_model));
	m_playlist_model->setHorizontalHeaderLabels(QStringList() << tr("Audio track") << tr("File path"));

	ui->playlistView->hideColumn(1);
//	ui->playlistView->verticalHeader()->setVisible(false);

	ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->playlistView->horizontalHeader()->setStretchLastSection(true);

	m_playlist = new QMediaPlaylist(m_player);
	m_player->setPlaylist(m_playlist);
	m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

	connect(ui->playlistView, &QTableView::doubleClicked,
			[this](const QModelIndex& index){m_playlist->setCurrentIndex(index.row());m_player->play();});

	connect(m_playlist, &QMediaPlaylist::currentIndexChanged,
			[this](int index)
	{
		ui->labelComposition->setText(m_playlist_model->data(m_playlist_model->index(index, 0)).toString());
	}
			);
}

Widget::~Widget()
{
	delete m_player;
	delete ui;
}


void Widget::on_horizontalSliderVolume_valueChanged(int value)
{
	m_player->setVolume(value);
	ui->labelVolume->setText(QString("Volume: ").append(QString::number(value)));
}

void Widget::on_pushButtonOpen_clicked()
{
//	QString file = QFileDialog::getOpenFileName(this, tr("Open files"), QString(), tr("Audio files (*.mp3)"));
//	m_player->setMedia(QUrl::fromLocalFile(file));
//	ui->labelComposition->setText(file.mid(file.lastIndexOf('/')+1));

	QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString("D:/Users/Clayman/Music/Sergo"), tr("Audio files (*.mp3)"));
	for(QString filePath: files)
	{
		QList<QStandardItem*> items;
		items.append(new QStandardItem(QDir(filePath).dirName()));
		items.append(new QStandardItem(filePath));
		m_playlist_model->appendRow(items);
		m_playlist->addMedia(QUrl(filePath));
	}
}

void Widget::on_pushButtonPlay_clicked()
{
	m_player->play();
}

void Widget::on_pushButtonPause_clicked()
{
	m_player->pause();
}

void Widget::on_pushButtonStop_clicked()
{
	m_player->stop();
}

void Widget::on_position_changed(qint64 value)
{
	ui->horizontalSliderTrack->setValue(value);
	QTime played = QTime::fromMSecsSinceStartOfDay(value);
	ui->labelPlayed->setText(QString("Played: ").append(played.toString("mm:ss")));
}
void Widget::on_duration_changed(qint64 duration)
{
	ui->horizontalSliderTrack->setMaximum(duration);
	QTime qt_duration = QTime::fromMSecsSinceStartOfDay(duration);
	ui->labelDuration->setText(QString("Duration: ").append(qt_duration.toString("mm:ss")));
}

void Widget::on_horizontalSliderTrack_valueChanged(qint64 position)
{
	m_player->setPosition(position);
}

void Widget::on_horizontalSliderTrack_sliderMoved(int position)
{
	m_player->setPosition(position);
}
