#pragma once
#ifndef MAP_H
#define MAP_H

#include "myslam/common_include.h"
#include "myslam/frame.h"
#include "myslam/mappoint.h"

namespace myslam
{
    /**
     * @brief 地图
     * 和地图的交互：前端调用InsertKeyframe和InsertMapPoint插入新帧和地图点，后端维护地图的结构，判定outlier/剔除等等
     */
    class Map
    {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        typedef std::shared_ptr<Map> Ptr;
        typedef std::unordered_map<unsigned long, MapPoint::Ptr> LandmarksType;
        typedef std::unordered_map<unsigned long, Frame::Ptr> KeyframesType;

        Map() {}

        void InsertKeyFrame(Frame::Ptr frame);

        void InsertMapPoint(MapPoint::Ptr map_point);

        LandmarksType GetAllMapPoint()
        {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return landmarks_;
        }

        /// 获取所有关键帧
        KeyframesType GetAllKeyFrames()
        {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return keyframes_;
        }

        /// 获取激活地图点
        LandmarksType GetActiveMapPoints()
        {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return active_landmarks_;
        }

        /// 获取激活关键帧
        KeyframesType GetActiveKeyFrames()
        {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return active_keyframes_;
        }

        /// 清理map中观测数量为零的点
        void CleanMap();

    private:
        void RemoveOldKeyframe();
        std::mutex data_mutex_;
        LandmarksType landmarks_;
        LandmarksType active_landmarks_;
        KeyframesType keyframes_;
        KeyframesType active_keyframes_;

        Frame::Ptr current_frame_ = nullptr;

        int num_active_keyframes_ = 7; // 激活的关键帧的数量
    };
}

#endif