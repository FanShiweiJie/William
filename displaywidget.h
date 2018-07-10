#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QTransform>
#include <Qstring>
#include <QMutex>
#include <QLabel>
#include <opencv2/opencv.hpp>

class VideoFrame;


class DisplayWidget : public QWidget {
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);

    void setFrame(const cv::Mat &frame );
    void setMark(const QRectF &mark );
    //void setMark(const QRectF &mark , const uint8_t tarredectflag);  /*加了颜色转换标志*/
    void setMark( const QRect &border, const QRect &rect );
    void setMark_Num(const uint16_t len, uint16_t *ptr);
    void setTitle(QString text);

    /* 可以显示两个矩形框，这个函数用于显示第二个 */
    void setMark2( const QRectF &mark );
    void setMark2( const QRect &border, const QRect &rect );

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *e);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void keyReleaseEvent(QKeyEvent *);

signals:
    void markChanged( QRectF mark );
    void pixelSend(int pixelx, int pixely);
    //void markChanging( QRectF mark );

private:
    bool selected;
    cv::Mat frame;
    QMutex paint_lock;
    bool show_disconnect;

    QLabel *label_title;

    QRect rect_mark;
    uint16_t rect_Num[60];
    int Num;

    QRect  rect_marking;
    QPoint begin_pos;
    bool   marking;
    bool   moving;
    bool   flag_setMark;
    bool   contain_mouse;
    QPoint mouse_pos;

    QRect rect_mark2;
};

#endif // DISPLAYWIDGET_H
