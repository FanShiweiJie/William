#include "targetmark.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileInfo>

TargetMark::TargetMark() {
    marks.clear();
    marks.resize( 0 );
    marks_cnt = 0;
}

const QRect &TargetMark::getMark(int idx) {
    if( idx>=marks_cnt ){
        return QRect();
    }

    return marks.at(idx);
}

void TargetMark::setMark(int idx, const QRect &item) {
    if( idx>=marks_cnt ){
        return;
    }

    marks.at(idx) = item;
}

int TargetMark::getMarkCnt() {
    return marks_cnt;
}

int TargetMark::getFrameCnt(int cnt){
    frame_cnt = cnt;
    return frame_cnt;
}

int TargetMark::getFrameWidth(int width){
    frame_width = width;
    return frame_width;
}

int TargetMark::getFrameHeight(int height){
    frame_height = height;
    return frame_height;
}

void TargetMark::reset(int size) {
    this->marks.clear();
    this->marks.resize( size );
    this->marks_cnt = size;
    this->filename = "";
}

bool TargetMark::isEmpty() {
    return  marks_cnt<=0;
}

int TargetMark::getLostCnt() {
    int cnt = 0;
    for( int idx=0; idx<marks_cnt; ++idx ){
        if( marks[idx].isEmpty() ){
            cnt ++;
        }
    }
    return cnt;
}

//bool TargetMark::load(std::string filename) {  //廖师兄原代码
//    QFile f( QString::fromStdString(filename) );
//    if( !f.open( QFile::ReadOnly ) ){
//        return false;
//    }

//    QJsonParseError error;
//    QJsonDocument doc = QJsonDocument::fromJson( f.readAll(), &error );
//    if( error.error != QJsonParseError::NoError ){
//        qDebug() << "json文件解析失败:" << error.errorString();
//        f.close();

//        return loadLegency(QString::fromStdString(filename));
//    }
//    f.close();

//    if( !doc.isObject() ){
//        qDebug() << "json文档的根不是对象";
//        return false;
//    }

//    QJsonObject root = doc.object();
//    QJsonValue  val_marks = root.value( "marks" );
//    if( !val_marks.isArray() ){
//        qDebug() << "marks不是数组";
//        return false;
//    }
//    QJsonArray  marks = val_marks.toArray();
//    this->reset( marks.size() );

//    for( int idx=0; idx<marks.size(); ++idx ){
//        QJsonValue val_mark = marks.at( idx );
//        if( !val_mark.isArray() ){
//            qDebug() << "第" << idx << "个mark不是数组";
//            return false;
//        }

//        QJsonArray mark = val_mark.toArray();
//        if( mark.size()==4
//                && mark.at(0).isDouble() && mark.at(1).isDouble()
//                && mark.at(2).isDouble() && mark.at(3).isDouble() ){
//            this->marks[idx] = QRect( mark.at(0).toDouble(), mark.at(1).toDouble(),
//                                   mark.at(2).toDouble(), mark.at(3).toDouble() );
//        }
//        else{
//            qDebug() << "第" << idx << "个mark数据无效";
//            return false;
//        }
//    }

//    this->filename = filename;
//    return true;
//}

bool TargetMark::load(std::string filename) {
    QFile f( QString::fromStdString(filename) );
    if( !f.open( QFile::ReadOnly ) ){
        return false;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson( f.readAll(), &error );
    if( error.error != QJsonParseError::NoError ){
        qDebug() << "json文件解析失败:" << error.errorString();
        f.close();

        return loadLegency(QString::fromStdString(filename));
    }
    f.close();

    if( !doc.isObject() ){
        qDebug() << "json文档的根不是对象";
        return false;
    }

    QJsonObject root = doc.object();
    QJsonValue  val_notations = root.value( "notation" );
    if( !val_notations.isArray() ){
        qDebug() << "不是数组";
        return false;
    }
    QJsonArray  notation = val_notations.toArray();
    this->reset( notation.size() );

    for( int idx=0; idx<notation.size(); ++idx ){
        QJsonValue val_mark = notation.at( idx );
        if( !val_mark.isObject() ){
            qDebug() << "第" << idx << "个标记不是对象";
            return false;
        }

        QJsonObject mark = val_mark.toObject();
        QJsonValue val_frame_index = mark.value("frame_index");
        if( !val_frame_index.isDouble() ){
            qDebug() << "帧号读取错误";
            return false;
        }
        int frame_index = val_frame_index.toInt();
        QJsonArray  target = mark.value("target").toArray();
        QJsonObject targetinfo = target.at(0).toObject();
        QJsonObject region = targetinfo.value("region").toObject();
            this->marks[frame_index-1] = QRect( region.value("colum").toInt(), region.value("row").toInt(),
                                   region.value("width").toInt(), region.value("height").toInt() );
    }
    this->filename = filename;
    return true;
}

//bool TargetMark::save(std::string filename) {  //廖师兄原代码
//    if( filename.empty() ){
//        filename = this->filename;
//    }
//    if( filename.empty() ){
//        return false;
//    }

//    QJsonObject root;
//    QJsonObject info;
//    QJsonArray  items;

//    info.insert( "frame_count", marks_cnt );

//    for( int idx=0; idx<marks_cnt; ++idx ){
//        QJsonArray mark;
//        QRect r = marks.at( idx );
//        mark.append( r.x() );
//        mark.append( r.y() );
//        mark.append( r.width() );
//        mark.append( r.height() );

//        items.append( mark );
//    }

//    root.insert( "info",  info  );
//    root.insert( "marks", items );

//    QJsonDocument doc;
//    doc.setObject( root );

//    QByteArray json = doc.toJson();
//    QFile file( QString::fromStdString(filename) );
//    file.open( QFile::WriteOnly );
//    file.write( json );
//    file.close();
//}

bool TargetMark::save(std::string filename) {
    if( filename.empty() ){
        filename = this->filename;
    }
    if( filename.empty() ){
        return false;
    }

    QJsonObject root;
    QJsonArray  notation;

    for( int idx=0; idx<frame_cnt; ++idx ){
        QJsonObject mark;
        mark.insert("frame_index", idx+1);
        //只有一个目标，id为1，description为null，category为null;
        QJsonArray target;
        //for(int i = 0; i<target_cnt; ++i){
            QJsonObject targetinfo;
                targetinfo.insert("id", 1);
                targetinfo.insert("description", QJsonValue::Null );
                targetinfo.insert("category", QJsonValue::Null );
                targetinfo.insert("region_format", "rectangle");
                QJsonObject region;
                    QRect r = marks.at( idx );
                    region.insert("colum", r.x());
                    region.insert("row", r.y());
                    region.insert("width", r.width());
                    region.insert("height", r.height());
                targetinfo.insert("region", region);
            target.append(targetinfo);
        mark.insert("target", target);
        notation.append( mark );
    }

    root.insert( "Json_version",  "1.0.0"  );
    root.insert( "frame_count", frame_cnt );
    root.insert("frame_width", frame_width );
    root.insert("frame_height", frame_height);
    root.insert("notation", notation);

    QJsonDocument doc;
    doc.setObject( root );

    QByteArray json = doc.toJson();
    QFile file( QString::fromStdString(filename) );
    file.open( QFile::WriteOnly );
    file.write( json );
    file.close();
}

QString TargetMark::pathFromVideo(QString name) {
    QFileInfo fileinfo( name );
    return fileinfo.absolutePath()+"/"+fileinfo.baseName()+".txt";
}

TargetMark::Score TargetMark::calcScore(TargetMark &correct, TargetMark &test) {
    Score score;
    if( correct.getMarkCnt() != test.getMarkCnt() ){
        score.valid = false;
        return score;
    }

    int framecnt = correct.getMarkCnt();
    cRect      *std = new cRect[framecnt];
    RstTarInfo *rst = new RstTarInfo[framecnt];

    for( int idx=0; idx<framecnt; ++idx ){
        QRect rect = correct.getMark(idx);
        std[idx].cenX = rect.center().x();
        std[idx].cenY = rect.center().y();
        std[idx].width = rect.width();
        std[idx].height = rect.height();
    }

    int cnt = 0; /* 大于0表示跟踪次数，小于0表示丢失次数 */
    for( int idx=0; idx<framecnt; ++idx ){
        QRect rect = test.getMark(idx);
        rst[idx].tarinfo.cenX = rect.center().x();
        rst[idx].tarinfo.cenY = rect.center().y();
        rst[idx].tarinfo.width = rect.width();
        rst[idx].tarinfo.height = rect.height();
        if( rect.isEmpty() ){
            if( cnt<=0  ){
                cnt --;
                rst[idx].tracknum = 0;
                rst[idx].losenum  = cnt;
            }
            if( cnt>0  ){
                cnt = 1;
                rst[idx].tracknum = cnt;
                rst[idx].losenum  = 0;
            }
        }
        else{
            if( cnt>=0 ){
                cnt ++;
                rst[idx].tracknum = cnt;
                rst[idx].losenum  = 0;
            }
            else{
                cnt = -1;
                rst[idx].tracknum = 0;
                rst[idx].losenum  = cnt;
            }
        }
    }

    TarRst res = caluateTrackRst( std, rst, framecnt );
    score.mean = res.mean;
    score.var  = res.var;
    score.valid = 1;

    return score;
}

bool TargetMark::loadLegency(const QString &filename) {
    QFile file( filename );
    if( !file.open( QFile::ReadOnly ) ){
        return false;
    }

    marks.clear();

    bool ok = false;

    /* 读第一行,判断是否是一个数字 */
    QString line = file.readLine();
    if( line.split(' ').size() == 1 ){
        /* 检查是否是数字 */
        bool ok;
        line.toInt( &ok );
        if( !ok ){
            file.close();
            return false;
        }
    }
    else{
        file.seek( 0 );
    }

    while( true ){
        QString line = file.readLine();
        if( line.isEmpty() ){
            ok = true;
            break;
        }

        QStringList items = line.split( ' ' );
        if( items.count() != 4 ){
            break;
        }

        int cx = items[0].toFloat();
        int cy = items[1].toFloat();
        int w  = items[2].toFloat();
        int h  = items[3].toFloat();
        QRect rect( cx-w/2, cy-h/2, w, h );
        marks.push_back( rect );
    }

    file.close();
    if( ok ){
        this->marks_cnt = marks.size();
    }
    return ok;
}

TarRst caluateTrackRst(cRect* std_tarinfo, RstTarInfo* rst_tarinfo, int framecount)
{
    int i = 0;
    TarRst tarrst;
    float mean = 0, var = 0;
    int sx = 0, sy = 0, rx = 0, ry = 0, losenum = 0, tracknum = 0;
    for (i = 0; i < framecount; i++)
    {
        sx = std_tarinfo[i].cenX;
        sy = std_tarinfo[i].cenY;
        rx = rst_tarinfo[i].tarinfo.cenX;
        ry = rst_tarinfo[i].tarinfo.cenY;
        losenum = rst_tarinfo[i].losenum;
        tracknum = rst_tarinfo[i].tracknum;

        mean = mean + (rx - sx) + (ry - sy);

    }
    mean = mean / (float)framecount;
    float diff = 0;
    for (i = 0; i < framecount; i++)
    {
        sx = std_tarinfo[i].cenX;
        sy = std_tarinfo[i].cenY;
        rx = rst_tarinfo[i].tarinfo.cenX;
        ry = rst_tarinfo[i].tarinfo.cenY;
        losenum = rst_tarinfo[i].losenum;
        tracknum = rst_tarinfo[i].tracknum;
        diff = (rx + ry - sx - sy - mean);
        var = var + pow(diff, 2);
    }
    var = var / (float)framecount;
    tarrst.mean = mean;
    tarrst.var = var;
    return tarrst;

}
