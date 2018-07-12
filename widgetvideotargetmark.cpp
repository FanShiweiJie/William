#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "widgetvideotargetmark.h"
#include "build/version.h"

WidgetVideoTargetMark::WidgetVideoTargetMark(QWidget *parent) : QWidget(parent) {
    ui.setupUi( this );
    QString version_string = VERSION_STRING;
    QString version_desc = VERSION_DESC;
    QString version = version_string + "@" + version_desc;
     this->setWindowTitle( "视频标记工具 （版本信息："+version+"）" );
    ui.btn_last_frame->setToolTip("快捷键：R");
     ui.btn_next_frame->setToolTip("快捷键：F");
    connect( ui.widget_display, SIGNAL(markChanged(QRectF)), this, SLOT(onMarkChanged(QRectF)) );
}

WidgetVideoTargetMark::~WidgetVideoTargetMark() {
    if( vinput.isOpened() ){
        vinput.close();
    }
}

void WidgetVideoTargetMark::updateFrameAndTarget( cv::Mat &frame ) {
    int idx = vinput.getFrameIdx();
    ui.widget_display->setFrame( frame );
    if( idx>1 ){
        setDisplayMark( targets.getMark(idx) );
    }
    ui.label_cur_frame->setText( QString("帧号:%1").arg(idx+1) );
}

void WidgetVideoTargetMark::setFrameIdxLabel(int idx) {
    ui.label_cur_frame->setText( QString("帧号:%1").arg(idx+1) );
}

void WidgetVideoTargetMark::setFrameAndMark(cv::Mat &frame, const QRect &mark){
    setDisplayMark( mark );
    ui.widget_display->setFrame( frame );
}

void WidgetVideoTargetMark::setDisplayMark(const QRect &mark) {
    int video_width = vinput.getWidth();
    int video_height = vinput.getHeight();
    QRectF r( mark.x(), mark.y(), mark.width(), mark.height() );
    r.setRect( r.x()/video_width,r.y()/video_height,
               r.width()/video_width,r.height()/video_height );
    ui.widget_display->setMark( r );

}

void WidgetVideoTargetMark::onMarkChanged(QRectF mark) {
    if( !vinput.isOpened() ){
        return;
    }
    int video_width  = vinput.getWidth();
    int video_height = vinput.getHeight();
    int frame_idx    = vinput.getFrameIdx();
    QRect m = QRect(
                int(mark.x()*video_width+0.5),
                int(mark.y()*video_height+0.5),
                int(mark.width()*video_width+0.5),
                int(mark.height()*video_height+0.5) );
    ui.label_target_info->setText(
                QString("(%1,%2)\n %3,%4")
                .arg( m.x(),4 )
                .arg( m.y(),4 )
                .arg( m.width(),4 )
                .arg( m.height(),4 ) );
    qDebug() << "set mark " << frame_idx << m;
    targets.setMark( frame_idx, m );
}

void WidgetVideoTargetMark::on_btn_open_video_clicked() {
    if( vinput.isOpened() ){
        vinput.close();
    }

    QString video_path = QFileDialog::getOpenFileName( this, "打开视频文件" );
    if( video_path.isEmpty() ){
        return;
    }

    int frame_idx = vinput.getFrameIdx();

    if( vinput.open( video_path.toStdString() ) ){
        ui.label_video_info->setText( QString("帧数:%1\n宽度:%2\n高度:%3")
                .arg( vinput.getFrameCnt() )
                .arg( vinput.getWidth() )
                .arg( vinput.getHeight() ) );

        targets.getFrameCnt(vinput.getFrameCnt());
        targets.getFrameWidth(vinput.getWidth());
        targets.getFrameHeight(vinput.getHeight());
        /* 尝试读取mark文件 */
        QFileInfo finfo( video_path );
        QString mark_path = finfo.absolutePath()+"/"+finfo.baseName()+".txt";
        qDebug() << mark_path;
        targets.reset( 0 );
        if( !targets.load( mark_path.toStdString() ) ){
            qDebug() << "laod mark file failed";
            targets.reset( vinput.getFrameCnt() );
        }

        cv::Mat frame = vinput.getNextFrame();
        setFrameAndMark( frame, targets.getMark(0) );
        setFrameIdxLabel( frame_idx );

        ui.btn_save_target->setEnabled( true );
        ui.btn_first_frame->setEnabled( vinput.getFrameIdx()!=0 );
        ui.btn_next_frame->setEnabled(  vinput.getFrameIdx()+1<vinput.getFrameCnt() );
        ui.btn_last_frame->setEnabled(  vinput.getFrameIdx()!=0 );
    }
    else{
        ui.btn_next_frame->setEnabled( false );
        ui.btn_last_frame->setEnabled( false );
        ui.btn_first_frame->setEnabled( false );
        ui.btn_save_target->setEnabled( false );
    }
}

void WidgetVideoTargetMark::on_btn_first_frame_clicked() {
    cv::Mat frame = vinput.getFirstFrame();

    setFrameIdxLabel( vinput.getFrameIdx() );
    setFrameAndMark( frame, targets.getMark(0) );

    ui.btn_first_frame->setEnabled( vinput.getFrameIdx()!=0 );
    ui.btn_next_frame->setEnabled(  vinput.getFrameIdx()+1<vinput.getFrameCnt() );
    ui.btn_last_frame->setEnabled(  vinput.getFrameIdx()!=0 );
}

void WidgetVideoTargetMark::on_btn_last_frame_clicked() {
    cv::Mat frame = vinput.getPrevFrame();
    if( frame.empty() ){
        return;
    }

    int frame_idx = vinput.getFrameIdx();
    setFrameAndMark(  frame, targets.getMark(frame_idx) );
    setFrameIdxLabel( vinput.getFrameIdx() );

    ui.btn_first_frame->setEnabled( vinput.getFrameIdx()!=0 );
    ui.btn_next_frame->setEnabled(  vinput.getFrameIdx()+1<vinput.getFrameCnt() );
    ui.btn_last_frame->setEnabled(  vinput.getFrameIdx()!=0 );
}

void WidgetVideoTargetMark::on_btn_next_frame_clicked() {
    cv::Mat frame = vinput.getNextFrame();
    if( frame.empty() ){
        return;
    }

    int frame_idx = vinput.getFrameIdx();
    ui.widget_display->setFrame( frame );
    QRect mark = targets.getMark( frame_idx );


    if( mark.isEmpty() && frame_idx>0 ){
        mark = targets.getMark( frame_idx-1 );
        if( ui.checkbox_next_frame_auto->isChecked() )
            targets.setMark( frame_idx, mark );
    }
    setFrameAndMark(  frame, mark );
    setFrameIdxLabel( vinput.getFrameIdx() );

    ui.btn_first_frame->setEnabled( vinput.getFrameIdx()!=0 );
    ui.btn_next_frame->setEnabled(  vinput.getFrameIdx()+1<vinput.getFrameCnt() );
    ui.btn_last_frame->setEnabled(  vinput.getFrameIdx()!=0 );
}

void WidgetVideoTargetMark::on_btn_save_target_clicked() {
    if( !vinput.isOpened() ){
        return;
    }

    QFileInfo fileinfo( QString::fromStdString(vinput.getFilename()) );
    QString name = QFileDialog::getSaveFileName(
                this, "保存目标标记文件",
                fileinfo.absolutePath()+"/"+fileinfo.baseName()+".txt" );
    if( name.isEmpty() ){
        return;
    }

    targets.save( name.toStdString() );
}
