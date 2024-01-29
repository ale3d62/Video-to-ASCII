#include <iostream>
#include <opencv2/opencv.hpp>

#include <thread>
#include <condition_variable>

//To get terminal dimensions
#include <windows.h>

//To disable info messages
#include <opencv2/core/utils/logger.hpp>

using namespace std;
using namespace cv;



tuple<int, int> resDimensions(int resX, int resY, int termX, int termY){
    int newResX, newResY;

    if((termX/(double)termY) > (resX/(double)resY)){
        newResY = termY;
        newResX = termY*resX/resY;
    }   
    else{
        newResX = termX;
        newResY = termX*resY/resX;
    }

    tuple<int,int> newRes(newResX, newResY);
    return newRes;
}



char pixelToChar(int pixelVal){
    string chars = "@#$*+;:,.";
    int nChars = chars.size();

    return chars[pixelVal/(double)256*nChars];
}




int main(){

    //Disable info messages
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    VideoCapture cap("video.mp4");
    int fps = cap.get(5);
    int frameCount = cap.get(7);


    //GET RESOLUTIONS
    //Video
    int resX = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int resY = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    //Terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int termX = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int termY = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    


    thread timer(timerThread);

    for(int i = 0; i<frameCount; i++){

        //CLEAR CONSOLE
        system("cls");


        //RESIZE
        Mat frame, resizedFrame;
        cap.read(frame);

        int newResX, rewResY;
        tie (newResX, rewResY) = resDimensions(resX, resY, termX, termY);
        resize(frame, resizedFrame, Size(newResX, rewResY), INTER_LINEAR);

        

        //CONVERT TO GRAYSCALE
        Mat gray;
        cvtColor(resizedFrame, gray, COLOR_YUV2BGR);
        cvtColor(resizedFrame, gray, COLOR_BGR2GRAY);


        //CONTERT TO CHARS
        string charFrame = "";

        for (int i = 0; i < gray.rows; i++) {
            for (int j = 0; j < gray.cols; j++) {
                charFrame += pixelToChar(static_cast<int>(gray.at<uchar>(i, j)));
                charFrame += " ";
            }
            charFrame+="\n";
        }

        cout<<charFrame;

    }

    return 0;
}