/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonPrev;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonNext;
    QSlider *horizontalSliderVolume;
    QSlider *horizontalSliderTrack;
    QLabel *labelVolume;
    QLabel *labelDuration;
    QLabel *labelPlayed;
    QLabel *labelComposition;
    QTableView *playlistView;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(530, 374);
        pushButtonOpen = new QPushButton(Widget);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 30, 41, 21));
        pushButtonPrev = new QPushButton(Widget);
        pushButtonPrev->setObjectName(QString::fromUtf8("pushButtonPrev"));
        pushButtonPrev->setGeometry(QRect(70, 30, 31, 21));
        pushButtonPlay = new QPushButton(Widget);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(110, 30, 31, 21));
        pushButtonPause = new QPushButton(Widget);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setGeometry(QRect(150, 30, 31, 21));
        pushButtonStop = new QPushButton(Widget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(190, 30, 31, 21));
        pushButtonNext = new QPushButton(Widget);
        pushButtonNext->setObjectName(QString::fromUtf8("pushButtonNext"));
        pushButtonNext->setGeometry(QRect(230, 30, 31, 21));
        horizontalSliderVolume = new QSlider(Widget);
        horizontalSliderVolume->setObjectName(QString::fromUtf8("horizontalSliderVolume"));
        horizontalSliderVolume->setGeometry(QRect(350, 40, 160, 16));
        horizontalSliderVolume->setOrientation(Qt::Horizontal);
        horizontalSliderTrack = new QSlider(Widget);
        horizontalSliderTrack->setObjectName(QString::fromUtf8("horizontalSliderTrack"));
        horizontalSliderTrack->setGeometry(QRect(20, 90, 491, 16));
        horizontalSliderTrack->setTracking(true);
        horizontalSliderTrack->setOrientation(Qt::Horizontal);
        labelVolume = new QLabel(Widget);
        labelVolume->setObjectName(QString::fromUtf8("labelVolume"));
        labelVolume->setGeometry(QRect(400, 10, 71, 16));
        labelDuration = new QLabel(Widget);
        labelDuration->setObjectName(QString::fromUtf8("labelDuration"));
        labelDuration->setGeometry(QRect(430, 70, 81, 16));
        labelPlayed = new QLabel(Widget);
        labelPlayed->setObjectName(QString::fromUtf8("labelPlayed"));
        labelPlayed->setGeometry(QRect(230, 70, 71, 16));
        labelComposition = new QLabel(Widget);
        labelComposition->setObjectName(QString::fromUtf8("labelComposition"));
        labelComposition->setGeometry(QRect(30, 130, 481, 20));
        playlistView = new QTableView(Widget);
        playlistView->setObjectName(QString::fromUtf8("playlistView"));
        playlistView->setGeometry(QRect(20, 160, 481, 192));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Winamp", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("Widget", "Open", nullptr));
        pushButtonPrev->setText(QString());
        pushButtonPlay->setText(QString());
        pushButtonPause->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonNext->setText(QString());
        labelVolume->setText(QCoreApplication::translate("Widget", "Volume:", nullptr));
        labelDuration->setText(QCoreApplication::translate("Widget", "Duration:", nullptr));
        labelPlayed->setText(QCoreApplication::translate("Widget", "Played:", nullptr));
        labelComposition->setText(QCoreApplication::translate("Widget", "Composition:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
