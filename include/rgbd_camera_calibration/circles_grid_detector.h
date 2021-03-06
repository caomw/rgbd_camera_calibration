/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

//! \author Stephan Wirth

#ifndef RGBD_CAMERA_CALIBRATION_CIRCLES_GRID_DETECTOR_H_
#define RGBD_CAMERA_CALIBRATION_CIRCLES_GRID_DETECTOR_H_


namespace cv
{
class FeatureDetector;
}

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>

#include "rgbd_camera_calibration/BlobDetectorConfig.h"
#include "rgbd_camera_calibration/pattern_detector.h"

namespace rgbd_camera_calibration
{

/**
 * Implements a circles grid detector using OpenCV.
 * The input is an image, the output is the set of 2D pattern points.
 */
class CirclesGridDetector : public PatternDetector
{
public:

  /**
   * Creates a detector with all parameters read from
   * given node handle. See implementation or private section
   * for a the list of parameters.
   */
  CirclesGridDetector(ros::NodeHandle& nh);

  /**
   * Detect the circles grid on given image.
   * @param[in] image input image
   * @param[out] centers the image points of the circle centers.
   * @return true if circles grid has been found, false otherwise.
   */
  virtual bool detect(
      const sensor_msgs::ImageConstPtr& image,
      std::vector<cv::Point2f>& centers) const;

  inline int getNumRows() const
  {
    return num_rows_;
  }

  inline int getNumCols() const
  {
    return num_cols_;
  }

  /**
   * @return Ideal world coordinates of the points that this
   *         detector detects.
   */
  virtual std::vector<cv::Point3f> getIdealWorldPoints() const
  {
    return centers3d_;
  }

  /**
   * Dynamic reconfiguration of the blob detector.
   */
  void configureBlobDetector(BlobDetectorConfig& config, uint32_t level);

private:

  int num_rows_;
  int num_cols_;
  double square_size_;
  int flags_;

  std::vector<cv::Point3f> centers3d_;

  cv::Ptr<cv::FeatureDetector> blob_detector_;

  dynamic_reconfigure::Server<BlobDetectorConfig> reconfigure_server_;
};

}

#endif

