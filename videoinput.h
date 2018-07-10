#ifndef VIDEOINPUT_H
#define VIDEOINPUT_H

#include <string>
#include <opencv2/opencv.hpp>

/*
 * 视频帧索引从0开始
 */

class VideoInput
{
public:
    VideoInput();
    ~VideoInput();

    bool open( const std::string &name );
    void close( void );
    bool isOpened( void );

    std::string getFilename( void );
    int  getFrameCnt( void );

    cv::Mat getNextFrame( void );
    cv::Mat getPrevFrame( void );
    cv::Mat getFirstFrame( void );
    cv::Mat getFrame( int idx );
    bool    setFrameIdx( int idx );
    int     getFrameIdx( void );

    int getWidth();
    int getHeight();
private:
    std::string filename;
    int frame_cnt;
    int frame_idx;
    int frame_width;
    int frame_height;
    cv::VideoCapture capture;
};

#endif // VIDEOINPUT_H
