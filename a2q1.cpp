#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "imageclassifier.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define WARPED_XSIZE 200
#define WARPED_YSIZE 300

///////////
////
//// Usage notes: requires c++14
//// To complile:  g++ -std=c++14 a2q1.cpp imageclassifier.cpp -o a2q1 `pkg-config --libs opencv`


using namespace cv;
//using namespace std;




#define VERY_LARGE_VALUE 100000

//#define NO_MATCH    0
//#define STOP_SIGN            1
//#define SPEED_LIMIT_40_SIGN  2
//#define SPEED_LIMIT_80_SIGN  3


/*The goal of the program you are going to write is to classify street signs, in
particular stop signs and two different speed limit signs (40km and 80km). There
are seven images that you will use to test your program; speedsign3.jpg – a 40km
speed sign, speedsign4.jpg – a 100km speed sign (no match), speedsign5.jpg – a
40km speed sign, speedsign12.jpg – an 80km speed sign, speedsign13.jpg – an
80km speed sign, speedsign14.jpg – an 80km speed sign, and finally stop4.jpg – a
stop sign. I have given you a program called classify_sign_template.cpp, which
you can extend to do the classification. The result will be a copy of the input
image with the appropriate label (a stop sign, speed limit 40, speed limit 80, or no
match) for each of these seven input images. There are two parts to the program,
the first decides on which type of sign you are looking at (stop sign or speed
limit). To do this you should use the routines Canny, findContours, and
approxPolyDP. To help you I am giving you some information on the parameters
of these routines. First of all, Canny(, , canny_thresh, canny_thresh*2, 3) where
canny_thresh is set to 120 (this worked for me). Also, findContours(, , ,
RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0, 0)), and approxPolyDP(, ,
contours[i].size()*.008, true). These are the parameter values which worked
for me so you can use them if you want, but you do not need to use them. The
second part of the program will use the routines getPerspectiveTransform ,
warpPerspective along with images speed_40.bmp, and speed_80.bmp to tell the
type of speed limit sign, but they are used only when you have determined that
you are indeed looking at a speed limit sign and not a stop sign. Finally the
routine matchtemplate( , , cv2.TM_CCOEFF_NORMED) is the best way to compare
the stored template (from the .bmp files) for the 80/40 speed limit signs and the
warped input sub-image. Hand in the source code, and tell me the version of
OpenCV that you are using. You should also include the four output files that you
have produced, one for each of the seven test cases.*/

int main(int argc, char* argv[]) {
    
    //cv::Mat src; 
    cv::Mat src_gray;
    cv::Mat warped_result;
    //cv::Mat speed_80, speed_40;
    int canny_thresh = 120;
    
    
    if(argc < 2){
        std::cout << "Usage: ./a2q1 <filename.jpg>" << std::endl;
        exit(-1);
    }
    
    std::string filename = argv[1];
    std::cout << "Attempting to classify sign in image " << filename << std::endl;
    
    int sign_recog_result = NO_MATCH;
    auto speed_40 = cv::imread("speed_40.bmp", 0);
    auto speed_80 = cv::imread("speed_80.bmp", 0);

    std::string final_sign_output_name = "OUT_" + filename;

	/// Load source image and convert it to gray
    auto src = cv::imread(filename, 1);

	/// Convert image to gray and blur it
	//cvtColor(src, src_gray, COLOR_BGR2GRAY);
	//blur(src_gray, src_gray, Size(5, 5));
	//warped_result = Mat(Size(WARPED_XSIZE, WARPED_YSIZE), src_gray.type());

	// here you add the code to do the recognition, and set the variable 
	// sign_recog_result to one of STOP_SIGN, SPEED_LIMIT_40_SIGN, SPEED_LIMIT_80_SIGN, or NO_MATCH

    std::string text = "Hi";
	//if (sign_recog_result == SPEED_LIMIT_40_SIGN) text = "Speed 40";
	//else if (sign_recog_result == SPEED_LIMIT_80_SIGN) text = "Speed 80";
	//else if (sign_recog_result == STOP_SIGN) text = "Stop";
	//else if (sign_recog_result == NO_MATCH) text = "Fail";

    
    //Define the font for output window
    int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;
    cv::Point textOrg(10, 130);
    cv::putText(src, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);

    // Create output window
    const char* source_window = "Result";
    cv::namedWindow(source_window, cv::WINDOW_AUTOSIZE);
    cv::imshow(source_window, src);
    cv::imwrite(final_sign_output_name, src);

    cv::waitKey(0);

    return(0);
}