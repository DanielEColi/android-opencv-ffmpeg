/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�trackerBoostingModel.HPP
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
#ifndef __OPENCV_TRACKER_BOOSTING_MODEL_HPP__
#define __OPENCV_TRACKER_BOOSTING_MODEL_HPP__

#include "precomp.hpp"
#include "opencv2/core.hpp"

namespace cv
{

/**
 * \brief Implementation of TrackerModel for BOOSTING algorithm
 */
class TrackerBoostingModel : public TrackerModel
{
 public:
  enum
  {
    MODE_POSITIVE = 1,    // mode for positive features
    MODE_NEGATIVE = 2,    // mode for negative features
    MODE_CLASSIFY = 3    // mode for classify step
  };
  /**
   * \brief Constructor
   * \param boundingBox The first boundingBox
   */
  TrackerBoostingModel( const Rect& boundingBox );

  /**
   * \brief Destructor
   */
  ~TrackerBoostingModel()
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

  /**
   * \brief return the selected weak classifiers for the detect
   * @return the selected weak classifiers
   */
  std::vector<int> getSelectedWeakClassifier();

 protected:
  void modelEstimationImpl( const std::vector<Mat>& responses );
  void modelUpdateImpl();

 private:

  std::vector<Mat> currentSample;

  int mode;
};

} /* namespace cv */

#endif
