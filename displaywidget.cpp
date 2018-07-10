#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <QTime>
#include "displaywidget.h"
#include "ui_utils.h"

#define SQRT_3 (1.736)

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent) {
    this->label_title = new QLabel( this );
    this->show_disconnect = true;
    setMouseTracking( true );

    marking = false;
    moving  = false;
    flag_setMark = true;
    contain_mouse = false;
}

void DisplayWidget::setFrame(const cv::Mat &frame ) {
    show_disconnect = false;

	paint_lock.lock();
    if( !frame.empty() ){
        this->frame = frame.clone();
		this->update();
	}
    paint_lock.unlock();
}

void DisplayWidget::setMark(const QRectF &mark) {
    this->rect_mark.setRect(
                width()*mark.x(),height()*mark.y(),
                width()*mark.width(), height()*mark.height() );
    flag_setMark = false;  //不画多个矩形框
    update();
}

void DisplayWidget::setMark(const QRect &border, const QRect &rect) {
    int w = border.width();
    int h = border.height();
    setMark( QRectF((float)rect.x()/w,(float)rect.y()/h,(float)rect.width()/w,(float)rect.height()/h) );
}

void DisplayWidget::setMark_Num(const uint16_t len, uint16_t* ptr)
{
    this->Num = len;
    flag_setMark = true;
    memcpy(this->rect_Num,ptr,60);
    update();
}

void DisplayWidget::setTitle(QString text) {
    this->label_title->setText( text );
    update();
}

void DisplayWidget::setMark2(const QRectF &mark) {
    this->rect_mark2.setRect(
                width()*mark.x(),height()*mark.y(),
                width()*mark.width(), height()*mark.height() );
    update();
}

void DisplayWidget::setMark2(const QRect &border, const QRect &rect) {
    int w = border.width();
    int h = border.height();
    setMark2( QRectF((float)rect.x()/w,(float)rect.y()/h,(float)rect.width()/w,(float)rect.height()/h) );
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
	if( !paint_lock.tryLock() ){
		return;
	}

	QPainter painter( this );
	/* 画视频帧 */
	if( !frame.empty() ){
		QImage image = cvMat2QImage( frame );
        image = image.scaled( this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
        painter.drawImage( 0,0, image );
	}

    /* 画矩形  */
    if( marking && !rect_marking.size().isEmpty() ){
        QPen pen = painter.pen();
        pen.setWidth( 2 );
        pen.setStyle( Qt::DashLine );
        pen.setColor( Qt::red );
        painter.setPen( pen );
        painter.drawRect( rect_marking );
    }

    if( !marking && !rect_mark.size().isEmpty() ){
        QPen pen = painter.pen();
        pen.setWidth( 2 );
        pen.setStyle( Qt::SolidLine );
        pen.setColor( Qt::red );
        painter.setPen( pen );
        painter.drawRect( rect_mark );
    }

    /* 画多个矩形框和矩形框编号 */
    if(flag_setMark && rect_Num!=NULL)
    {
        QPen pen = painter.pen();
        pen.setWidth( 1 );
        pen.setStyle( Qt::SolidLine );
        pen.setColor( Qt::red );
        painter.setPen( pen );
        for(int i=0;i<Num;i++)
        {
            QString rect_mark_Num = QString::number(i+1);
            painter.drawText(QRect(rect_Num[i*4]-0.5*rect_Num[i*4+2],rect_Num[i*4+1]-0.5*rect_Num[i*4+3]-15,20,15),rect_mark_Num);
            painter.drawRect(QRect(rect_Num[i*4]-0.5*rect_Num[i*4+2],rect_Num[i*4+1]-0.5*rect_Num[i*4+3],rect_Num[i*4+2],rect_Num[i*4+3]));
        }
    }

    /* 画第二个矩形 */
    if( !rect_mark2.isEmpty() ){
        QPen pen = painter.pen();
        pen.setWidth( 1 );
        pen.setStyle( Qt::SolidLine );
        pen.setColor( Qt::green );
        painter.setPen( pen );
        painter.drawRect( rect_mark2 );
    }

    if( contain_mouse && !marking ){
        QPen pen = painter.pen();
        pen.setColor( Qt::black );
        pen.setStyle( Qt::DotLine );
        pen.setWidth( 1 );
        painter.setPen( pen );
        painter.drawLine( mouse_pos.x(),0, mouse_pos.x(),height() );
        painter.drawLine( 0,mouse_pos.y(), width(),mouse_pos.y() );
    }

	paint_lock.unlock();
}

void DisplayWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent( e );
}

void DisplayWidget::mousePressEvent( QMouseEvent *evt ) {
    if( rect_mark.contains(evt->pos()) ){
        moving = true;
        this->rect_marking = this->rect_mark;
    }
    else{
        moving = false;
        this->rect_marking.setTopLeft( evt->pos() );
        this->rect_marking.setSize( QSize(0,0) );
    }
    this->marking = true;
    this->begin_pos = evt->pos();
    update();
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *evt){
    this->marking = false;
    this->moving  = false;
    if( !rect_marking.size().isEmpty() && rect().contains(this->rect_marking) ){
        this->rect_mark = this->rect_marking;
    }
    else{
        this->rect_mark = QRect();
    }
    emit( markChanged( QRectF( rect_mark.x()/(float)width(), rect_mark.y()/(float)height(),
                               rect_mark.width()/(float)width(), rect_mark.height()/(float)height())) );
    update();
}

void DisplayWidget::mouseMoveEvent( QMouseEvent *evt ) {
    mouse_pos = evt->pos();
    emit( pixelSend(mouse_pos.x(),mouse_pos.y()));
    if( moving ){
        int dx = evt->pos().x() - begin_pos.x();
        int dy = evt->pos().y() - begin_pos.y();
        QRect temp = rect_mark;
        temp.moveCenter( rect_mark.center() + QPoint(dx,dy) );
        if( rect().contains(temp) ){
            rect_marking = temp;
        }
        else{
            rect_marking.setBottomRight( rect_marking.topLeft() );
        }
    }
    else{
        if( !rect().contains(evt->pos()) ){
            rect_marking.setBottomRight( rect_marking.topLeft() );
        }
        else{
            rect_marking.setBottomRight( evt->pos() );
        }
    }
    update();
}

void DisplayWidget::wheelEvent(QWheelEvent *evt) {
    if( rect_mark.contains( evt->pos() ) ){
        QRect temp = rect_mark;
        QPoint delta = evt->angleDelta();
        if( delta.y()>0 )
            temp.adjust(0,-1,0,1);
        else if( delta.y()<0 ){
            temp.adjust(0,1,0,-1);
        }
        if( delta.x()>0 ){
            temp.adjust( -1,0,1,0 );
        }
        else if( delta.x()<0 ){
            temp.adjust( 1,0,-1,0 );
        }

        if( this->rect().contains(temp) ){
            rect_mark = temp;
            emit( markChanged( QRectF( rect_mark.x()/(float)width(), rect_mark.y()/(float)height(),
                               rect_mark.width()/(float)width(), rect_mark.height()/(float)height())) );
        }
    }
    update();
}

void DisplayWidget::enterEvent(QEvent *) {
    contain_mouse = true;
    update();
}

void DisplayWidget::leaveEvent(QEvent *) {
    contain_mouse = false;
    update();
}

void DisplayWidget::keyReleaseEvent(QKeyEvent *evt) {
    QRect temp = rect_mark;
    if( evt->modifiers() == Qt::ControlModifier ){
        if( evt->key() == Qt::Key_W ){
            temp.adjust( 0,-1, 0,1 );
        }
        else if( evt->key() == Qt::Key_S ){
            temp.adjust( 0,1, 0,-1 );
        }
        else if( evt->key() == Qt::Key_A ){
            temp.adjust( 1,0, -1,0 );
        }
        else if( evt->key() == Qt::Key_D ){
            temp.adjust( -1,0, 1,0 );
        }
    }
    else{
        if( evt->key() == Qt::Key_W ){
            temp.adjust( 0,-1, 0,-1 );
        }
        else if( evt->key() == Qt::Key_S ){
            temp.adjust( 0,1, 0,1 );
        }
        else if( evt->key() == Qt::Key_A ){
            temp.adjust( -1,0, -1,0 );
        }
        else if( evt->key() == Qt::Key_D ){
            temp.adjust( 1,0, 1,0 );
        }
    }

    if( temp.width()>0 && temp.height()>0 && rect().contains(temp) ){
        this->rect_mark = temp;
    }
    update();
    emit( markChanged( QRectF( rect_mark.x()/(float)width(), rect_mark.y()/(float)height(),
                               rect_mark.width()/(float)width(), rect_mark.height()/(float)height())) );
}


