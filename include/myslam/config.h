#pragma once
#ifndef MYSLAM_CONFIG_H
#define MYSLAM_CONFIG_H

#include "myslam/common_include.h"

namespace myslam
{
    /**
     * 配置类，使用SetParameterFile确定配置文件
     * 然后用Get得到对应值
     * 单例模式
     */
    class Config
    {
    private:
        static std::shared_ptr<Config> config_;
        cv::FileStorage file_;

        Config() {} // 单例模式
    public:
        ~Config();
        static bool SetParameterFile(const std::string &filename);

        // access the parameter values
        template <typename T>
        static T Get(const std::string &key)
        {
            return T(Config::config_->file_[key]);
        }
    };
}

#endif