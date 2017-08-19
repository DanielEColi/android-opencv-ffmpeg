/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�TrackerMILMODEL.HPP
* �ļ���ʶ�������ù���ƻ���
* ժ Ҫ����Ҫ�������ļ�������
*
* ��ǰ�汾��1.01
* �� �ߣ�Henry
* ������ڣ�2017��08��12��
*
* ȡ���汾��1.00
* ԭ���� ��HENRY
* ������ڣ�2017��07��12��
*/
#ifndef __OPENCV_TRACKER_MIL_MODEL_HPP__
#define __OPENCV_TRACKER_MIL_MODEL_HPP__

#include "opencv2/core.hpp"

namespace cv
{

/**
 * \brief Implementation of TrackerModel for MIL algorithm
 */
class TrackerMILModel : public TrackerModel
{
 public:
  enum
  {
    MODE_POSITIVE = 1,  	// mode for positive features
    MODE_NEGATIVE = 2,  	// mode for negative features
    MODE_ESTIMATON = 3	// mode for estimation step
  };

  /**
   * \brief Constructor
   * \param boundingBox The first boundingBox
   */
  TrackerMILModel( const Rect& boundingBox );

  /**
   * \brief Destructor
   */
  ~TrackerMILModel()
  {
  }
  ;

  /**
   * \brief Set the mode
   */
  void setMode( int trainingMode, const std::vector<Mat>& samples );

  /**
   * \brief Create the ConfidenceMap from a list of responses
   * \param responses The list of the responses
   * \param confidenceMap The output
   */
  void responseToConfidenceMap( const std::vector<Mat>& responses, ConfidenceMap& confidenceMap );

 protected:
  void modelEstimationImpl( const std::vector<Mat>& responses );
  void modelUpdateImpl();

 private:
  int mode;
  std::vector<Mat> currentSample;

  int width;	//initial width of the boundingBox
  int height;  //initial height of the boundingBox
};

} /* namespace cv */

#endif
