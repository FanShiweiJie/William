#ifndef _UI_UTILS_
#define _UI_UTILS_

class QImage;
class QRect;
#include "opencv2/opencv.hpp"

/*
 * cv::Mat -> QImage
 */
QImage cvMat2QImage(const cv::Mat &mat);

/*
 * QImage -> cv::Mat
 */
cv::Mat QImage2cvMat(QImage image);

/*
 * cv::Rect -> QRect
 */
QRect cvRect2QRect( const cv::Rect &rect );

/*
 * QRect -> cv::Rect
 */
cv::Rect QRect2cvRect( const QRect &rect );

#endif
