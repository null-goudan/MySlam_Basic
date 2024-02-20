#pragma once

#ifndef MYSLAM_FRAME_H
#define MYSLAM_FRAME_H

#include "myslam/common_include.h"
#include "myslam/camera.h"

namespace myslam
{

    // forward declare
    struct MapPoint;
    struct Feature;

    struct Frame
    {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
        typedef std::shared_ptr<Frame> Ptr;

        unsigned long id_ = 0;
        unsigned long keyframe_id_ = 0;
        bool is_keyframe_ = false;
        double time_stamp_;
        SE3 pose_; // Tcw 形式Pose
        std::mutex pose_mutex_;
        cv::Mat left_img_, right_img_;

        std::vector<std::shared_ptr<Feature>> features_left_;
        std::vector<std::shared_ptr<Feature>> features_right_;

    public:
        Frame() {}
        Frame(long id, double time_stamp, const SE3 &pose, const Mat &left,
        const Mat &right);

        SE3 Pose(){
            std::unique_lock<std::mutex> lck (pose_mutex_);
            return pose_;
        }

        void SetPose(const SE3 &pose){
            std::unique_lock<std::mutex> lck (pose_mutex_);
            pose_ = pose;
        }

        // 设置关键帧并分配关键帧id
        void SetKeyFrame();

        // 工厂构建模式, 分配id
        static std::shared_ptr<Frame> CreateFrame();
    };

}

#endif