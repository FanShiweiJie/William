#ifndef WIDGETVIDEOTARGETMARK_H
#define WIDGETVIDEOTARGETMARK_H

#include <QWidget>
#include <QList>
#include <QVector>
#include <opencv2/opencv.hpp>
#include "videoinput.h"
#include "ui_videotargetmark.h"
#include "targetmark.h"

/*
 * JSON文件格式
 * {
 *     info:{
 *         filename: STRING,
 *         frame_count: NUMBER,
 *     }
 *     marks:[
 *         [ NUMBER,NUMBER,NUMBER,NUMBER ] // x,y,width,height
 *         [ NUMBER,NUMBER,NUMBER,NUMBER ] // x,y,width,height
 *         ...
 *     ]
 * }
 *
 */

class WidgetVideoTargetMark : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetVideoTargetMark(QWidget *parent = 0);
    ~WidgetVideoTargetMark();

signals:

private:
    void updateFrameAndTarget( cv::Mat &frame );
    cv::Mat readNextFrame( void );
    cv::Mat readLastFrame( void );

    void setFrameIdxLabel( int idx );
    void setFrameAndMark( cv::Mat &frame, const QRect &mark );
    void setDisplayMark( const QRect &mark );

private slots:
    void onMarkChanged( QRectF mark );
    void on_btn_open_video_clicked();
    void on_btn_first_frame_clicked();
    void on_btn_last_frame_clicked();
    void on_btn_next_frame_clicked();
    void on_btn_save_target_clicked();

private:
    Ui::VideoTargetMark ui;

    VideoInput vinput;
    TargetMark targets;
};

#endif // WIDGETVIDEOTARGETMARK_H
