#ifndef TARGETMARK_H
#define TARGETMARK_H

#include <string>
#include <vector>
#include <QRect>

class TargetMark
{
public:
    TargetMark();

    const QRect &getMark( int idx );
    void        setMark( int idx, const QRect &item );
    int       getMarkCnt( void );
    int       getFrameCnt(int cnt);
    int       getFrameWidth(int width);
    int       getFrameHeight(int height);

    void reset( int size );
    bool isEmpty( void );
    int getLostCnt( void );

    /* 从文件中读取 */
    bool load( std::string filename );
    /* 写入到文件中，如果filename不指定，则写到load的文件中 */
    bool save( std::string filename=std::string() );

    static QString pathFromVideo( QString name );

    struct Score{
        bool valid;
        float mean;
        float var;
    };
    static Score  calcScore( TargetMark &correct, TargetMark &test );
private:
    bool loadLegency( const QString &filename  );
private:
    std::string filename;
    std::vector<QRect> marks;
    int                marks_cnt;
    int             frame_cnt;
    int             frame_width;
    int             frame_height;
};

typedef struct CRECT
{
    int cenX;
    int cenY;
    int width;
    int height;
}cRect;

typedef struct RSTTARINFO
{
    cRect tarinfo;
    int losenum;
    int tracknum;
}RstTarInfo;

typedef struct TRACKRST
{
    float mean;
    float var;
}TarRst;

TarRst caluateTrackRst(cRect* std_tarinfo, RstTarInfo* rst_tarinfo, int framecount);

#endif // TARGETMARK_H
