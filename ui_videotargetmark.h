/********************************************************************************
** Form generated from reading UI file 'videotargetmark.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOTARGETMARK_H
#define UI_VIDEOTARGETMARK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "displaywidget.h"

QT_BEGIN_NAMESPACE

class Ui_VideoTargetMark
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    DisplayWidget *widget_display;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_open_video;
    QPushButton *btn_save_target;
    QLabel *label_video_info;
    QLabel *label_cur_frame;
    QLabel *label_target_info;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_first_frame;
    QCheckBox *checkbox_last_frame_auto;
    QPushButton *btn_last_frame;
    QCheckBox *checkbox_next_frame_auto;
    QPushButton *btn_next_frame;

    void setupUi(QWidget *VideoTargetMark)
    {
        if (VideoTargetMark->objectName().isEmpty())
            VideoTargetMark->setObjectName(QStringLiteral("VideoTargetMark"));
        VideoTargetMark->resize(595, 355);
        horizontalLayout = new QHBoxLayout(VideoTargetMark);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(VideoTargetMark);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(420, 320));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(203, 203, 203);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_display = new DisplayWidget(frame);
        widget_display->setObjectName(QStringLiteral("widget_display"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_display->sizePolicy().hasHeightForWidth());
        widget_display->setSizePolicy(sizePolicy);
        widget_display->setMinimumSize(QSize(0, 0));
        widget_display->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(widget_display);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(VideoTargetMark);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        btn_open_video = new QPushButton(frame_2);
        btn_open_video->setObjectName(QStringLiteral("btn_open_video"));

        verticalLayout_2->addWidget(btn_open_video);

        btn_save_target = new QPushButton(frame_2);
        btn_save_target->setObjectName(QStringLiteral("btn_save_target"));
        btn_save_target->setEnabled(false);

        verticalLayout_2->addWidget(btn_save_target);

        label_video_info = new QLabel(frame_2);
        label_video_info->setObjectName(QStringLiteral("label_video_info"));

        verticalLayout_2->addWidget(label_video_info);

        label_cur_frame = new QLabel(frame_2);
        label_cur_frame->setObjectName(QStringLiteral("label_cur_frame"));

        verticalLayout_2->addWidget(label_cur_frame);

        label_target_info = new QLabel(frame_2);
        label_target_info->setObjectName(QStringLiteral("label_target_info"));

        verticalLayout_2->addWidget(label_target_info);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btn_first_frame = new QPushButton(frame_2);
        btn_first_frame->setObjectName(QStringLiteral("btn_first_frame"));
        btn_first_frame->setEnabled(false);

        verticalLayout_2->addWidget(btn_first_frame);

        checkbox_last_frame_auto = new QCheckBox(frame_2);
        checkbox_last_frame_auto->setObjectName(QStringLiteral("checkbox_last_frame_auto"));
        checkbox_last_frame_auto->setEnabled(false);

        verticalLayout_2->addWidget(checkbox_last_frame_auto);

        btn_last_frame = new QPushButton(frame_2);
        btn_last_frame->setObjectName(QStringLiteral("btn_last_frame"));
        btn_last_frame->setEnabled(false);
        btn_last_frame->setAutoRepeat(true);
        btn_last_frame->setAutoRepeatInterval(40);

        verticalLayout_2->addWidget(btn_last_frame);

        checkbox_next_frame_auto = new QCheckBox(frame_2);
        checkbox_next_frame_auto->setObjectName(QStringLiteral("checkbox_next_frame_auto"));

        verticalLayout_2->addWidget(checkbox_next_frame_auto);

        btn_next_frame = new QPushButton(frame_2);
        btn_next_frame->setObjectName(QStringLiteral("btn_next_frame"));
        btn_next_frame->setEnabled(false);
        btn_next_frame->setAutoRepeat(true);
        btn_next_frame->setAutoRepeatInterval(40);

        verticalLayout_2->addWidget(btn_next_frame);


        horizontalLayout->addWidget(frame_2);


        retranslateUi(VideoTargetMark);

        QMetaObject::connectSlotsByName(VideoTargetMark);
    } // setupUi

    void retranslateUi(QWidget *VideoTargetMark)
    {
        VideoTargetMark->setWindowTitle(QApplication::translate("VideoTargetMark", "Form", 0));
        btn_open_video->setText(QApplication::translate("VideoTargetMark", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        btn_save_target->setText(QApplication::translate("VideoTargetMark", "\344\277\235\345\255\230\347\233\256\346\240\207", 0));
        label_video_info->setText(QString());
        label_cur_frame->setText(QString());
        label_target_info->setText(QString());
        btn_first_frame->setText(QApplication::translate("VideoTargetMark", "\351\246\226\345\270\247", 0));
        checkbox_last_frame_auto->setText(QApplication::translate("VideoTargetMark", "\344\270\212\344\270\200\345\270\247\347\232\204\346\240\207\350\256\260\344\270\272\347\251\272\346\227\266\n"
"\344\275\277\347\224\250\345\275\223\345\211\215\345\270\247\347\232\204\346\240\207\350\256\260", 0));
        btn_last_frame->setText(QApplication::translate("VideoTargetMark", "\344\270\212\344\270\200\345\270\247", 0));
        btn_last_frame->setShortcut(QApplication::translate("VideoTargetMark", "R", 0));
        checkbox_next_frame_auto->setText(QApplication::translate("VideoTargetMark", "\344\270\213\344\270\200\345\270\247\347\232\204\346\240\207\350\256\260\344\270\272\347\251\272\346\227\266\n"
"\344\275\277\347\224\250\345\275\223\345\211\215\345\270\247\347\232\204\346\240\207\350\256\260", 0));
        btn_next_frame->setText(QApplication::translate("VideoTargetMark", "\344\270\213\344\270\200\345\270\247", 0));
        btn_next_frame->setShortcut(QApplication::translate("VideoTargetMark", "F", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoTargetMark: public Ui_VideoTargetMark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOTARGETMARK_H
