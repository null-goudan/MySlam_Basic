# 简易双目视觉里程计
基于双目相机的视觉里程计，灵感来源于高翔博士的《视觉SLAM十四讲》

![SLAM_Basic](https://github.com/null-goudan/MySlam_Basic/assets/74131166/0932251f-19e4-40bd-a81c-4bb52b092482)


## 环境支撑：
   ```c
   操作系统： Ubuntu 20.04
   cmake >= 3.8
   OpenCV 3.14.0、 g2o、 Sophus、 Eigen 3.7、 gooletest 、pooglin 等
   ```

## 主体架构
  ### 基础数据结构
    关键帧，特征点，路标点，地图
  ### 前端
    前端拥有 初始化、 正常追踪、 追踪丢失 三种状态
    初始化状态： 根据左右目之间进行光流匹配，寻找可以三角化的点，成功时建立初始地图
    追踪阶段： 使用上一帧的特征点到当前帧的光流，根据光流结果计算图像位姿。只使用左目图像
          关键帧确定： 如果追踪点较少，确定为关键帧 
            - 如何处理： ① 提取新的特征点 ② 找到左右目的对应点进行尝试三角化 ③ 将新的关键帧和路标点加入地图，并触发一次后端优化
    追踪丢失： 重置前端，重新初始化
  ### 后端
    后端使用滑动窗口法(我的设置中，窗口大小为7个关键帧) 
    开启后端线程： 当触发时，对当前的所有路标点，关键帧等进行BA计算优化。

## 最终实现效果：
  在kitti数据集测试表现如下， 能够流畅运行
  
  ![image](https://github.com/null-goudan/MySlam_Basic/assets/74131166/d312cac6-e7cd-4087-b6af-166eb7aefdfc)


## 使用方法：
  按照环境支撑进行环境布置之后，clone 代码到本地
  ```c 
  git clone https://github.com/null-goudan/MySlam_Basic.git
  ```
  使用以下命令:
  ```c
  mkdir build
  cd build
  cmake ..
  make -j4
  ```
  这时 bin 文件夹下有编译好的 run_kitti_stereo  将其移动至 工程目录文件夹 下 使用 ./run_kitti_stereo

  需要注意的是： 算法的参数设置以及输入数据的设置将会读取config 目录下 default.yaml 里的设置, 需要您更改其中的数据集的位置到您的数据集文件夹中，读取数据集的方式这里使用的include/myslam/dataset.h 如使用kitti以外的数据集（或者您自己的数据集）还需您自己更改其读取方式。
