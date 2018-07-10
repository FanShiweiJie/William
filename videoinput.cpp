#include "videoinput.h"

VideoInput::VideoInput() {
    frame_cnt = -1;
    frame_idx = -1;
}

VideoInput::~VideoInput() {
    close();
}

bool VideoInput::open(const std::string &name) {
    if( capture.isOpened() ){
        return false;
    }

    bool ok = capture.open( name );
    if( !ok ){
        return false;
    }

    this->filename = name;
    this->frame_cnt = capture.get( CV_CAP_PROP_FRAME_COUNT );
    this->frame_width  = capture.get( CV_CAP_PROP_FRAME_WIDTH );
    this->frame_height = capture.get( CV_CAP_PROP_FRAME_HEIGHT );
    this->frame_idx = -1;
    return true;
}

void VideoInput::close() {
    if( capture.isOpened() ){
        capture.release();
    }
    filename.clear();
    frame_cnt = -1;
    frame_idx = -1;
}

bool VideoInput::isOpened() {
    return capture.isOpened();
}

std::string VideoInput::getFilename() {
    return filename;
}

int VideoInput::getFrameCnt() {
    return frame_cnt;
}

cv::Mat VideoInput::getNextFrame() {
    if( !capture.isOpened() ){
        return cv::Mat();
    }

    if( !(frame_idx<frame_cnt) ){
        return cv::Mat();
    }

    cv::Mat frame;
    bool ok = false;
    try{
        ok = capture.read( frame );
    }
    catch( ... ){
        ok = false;
    }

    if( ok ) frame_idx++;

    return frame;
}

cv::Mat VideoInput::getPrevFrame() {
    if( !capture.isOpened() ){
        return cv::Mat();
    }

    if( frame_idx<1 ){
        return cv::Mat();
    }

    frame_idx = frame_idx-2;
    capture.set( CV_CAP_PROP_POS_FRAMES, frame_idx+1 );
    return getNextFrame();
}

cv::Mat VideoInput::getFirstFrame() {
    if( !capture.isOpened() ){
        return cv::Mat();
    }

    capture.set( CV_CAP_PROP_POS_FRAMES, 0 );
    frame_idx = -1;
    return getNextFrame();
}

cv::Mat VideoInput::getFrame(int idx) {
    if( idx>= frame_cnt && idx<0 ){
        return cv::Mat();
    }

    capture.set( CV_CAP_PROP_POS_FRAMES, idx );
    frame_idx = idx-1;
    return getNextFrame();
}

bool VideoInput::setFrameIdx( int idx ) {
    if( !capture.isOpened() ){
        return false;
    }
    if( idx>=frame_cnt ){
        return false;
    }

    capture.set( CV_CAP_PROP_POS_FRAMES, idx );
    frame_idx = idx;
    return true;
}

int VideoInput::getFrameIdx() {
    return frame_idx;
}

int VideoInput::getWidth() {
    if( capture.isOpened() ){
        return frame_width;
    }
    return -1;
}

int VideoInput::getHeight() {
    if( capture.isOpened() ){
        return frame_height;
    }
    return -1;
}
