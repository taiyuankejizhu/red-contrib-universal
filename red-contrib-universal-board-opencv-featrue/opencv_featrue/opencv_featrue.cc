// Test to check the OpenCV version
// Build on Linux with:
// g++ test_1.cpp -o test_1 -lopencv_core

#include <opencv2/opencv.hpp>
#include <iostream>
#include <nan.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>


#define NODE_RED_DASHBOARD_DIR "/root/.node-red/node_modules/node-red-dashboard/dist/"

void DeleteOldCaptrue(void) {
    DIR *dir;
    struct dirent *file;
    char name[32];
    char full_name[64];
    int i = 0;
    
    if(!(dir = opendir(NODE_RED_DASHBOARD_DIR))) return;
    while((file = readdir(dir)) != NULL) {
        if (strlen(file->d_name) > strlen(".png")) {
            strncpy(name, file->d_name, strlen(file->d_name) - strlen(".png"));
            name[strlen(file->d_name) - strlen(".png")] = '\0';
            for (i = 0; i < strlen(name); i++) {
                if (!isdigit(name[i])) break;
            }
            if (i < strlen(name)) continue;
            else {
                memset(full_name, '\0', sizeof(full_name));
                strcpy(full_name, NODE_RED_DASHBOARD_DIR);
                strcat(full_name, file->d_name);
                std::cout << full_name << std::endl;
                remove(full_name);
            }
        }
    }
    
    closedir(dir);
    return;
}

void Captrue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Int32> num = Nan::New(0);

    if (info.Length() < 2) {
        num = Nan::New(-1);
        info.GetReturnValue().Set(num);
        return;
    }

    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
        num = Nan::New(-2);
        info.GetReturnValue().Set(num);
        return;
    }

    int width = info[0]->NumberValue();
    int hight = info[1]->NumberValue();
  
    cv::VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH , width);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT ,hight);
    
    std::cout << "Brightness:" << 
        capture.get(CV_CAP_PROP_BRIGHTNESS) << "  " <<
        capture.get(CV_CAP_PROP_CONTRAST) << "  " <<
        capture.get(CV_CAP_PROP_SATURATION) << "  " <<
        capture.get(CV_CAP_PROP_HUE) << "  "
        << std::endl;
        
    if(!capture.isOpened()) {
        num = Nan::New(-3);
        info.GetReturnValue().Set(num);
        return;
    }
    
    DeleteOldCaptrue();
    
    cv::Mat image;
    capture >> image;
    usleep(100);
    capture >> image;
    usleep(100);
    capture >> image;
    usleep(100);
    capture >> image;
    usleep(100);
    capture >> image;
    usleep(100);
    capture >> image;
    
    struct  timeval    tv;
    struct  timezone   tz;
    gettimeofday(&tv, &tz);
    
    std::string url = NODE_RED_DASHBOARD_DIR;
    url += std::to_string(tv.tv_sec);
    url += ".png";
    
    cv::imwrite(url, image);
    capture.release();

    num = Nan::New((int)tv.tv_sec);
    info.GetReturnValue().Set(num);
    return;
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("captrue").ToLocalChecked(),
        Nan::New<v8::FunctionTemplate>(Captrue)->GetFunction());
}

NODE_MODULE(opencv_featrue, Init)