/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�trackerModel.CPP
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
#include "precomp.hpp"

namespace cv
{

/*
 *  TrackerModel
 */

TrackerModel::TrackerModel()
{
  stateEstimator = Ptr<TrackerStateEstimator>();
  maxCMLength = 1;
}

TrackerModel::~TrackerModel()
{

}

bool TrackerModel::setTrackerStateEstimator( Ptr<TrackerStateEstimator> trackerStateEstimator )
{
  if( stateEstimator != 0 )
  {
    return false;
  }

  stateEstimator = trackerStateEstimator;
  return true;
}

Ptr<TrackerStateEstimator> TrackerModel::getTrackerStateEstimator() const
{
  return stateEstimator;
}

void TrackerModel::modelEstimation( const std::vector<Mat>& responses )
{
  modelEstimationImpl( responses );

}

void TrackerModel::clearCurrentConfidenceMap()
{
  currentConfidenceMap.clear();
}

void TrackerModel::modelUpdate()
{
  modelUpdateImpl();

  if( maxCMLength != -1 && (int) confidenceMaps.size() >= maxCMLength - 1 )
  {
    int l = maxCMLength / 2;
    confidenceMaps.erase( confidenceMaps.begin(), confidenceMaps.begin() + l );
  }
  if( maxCMLength != -1 && (int) trajectory.size() >= maxCMLength - 1 )
  {
    int l = maxCMLength / 2;
    trajectory.erase( trajectory.begin(), trajectory.begin() + l );
  }
  confidenceMaps.push_back( currentConfidenceMap );
  stateEstimator->update( confidenceMaps );

  clearCurrentConfidenceMap();

}

bool TrackerModel::runStateEstimator()
{
  if( stateEstimator == 0 )
  {
    CV_Error( -1, "Tracker state estimator is not setted" );
    return false;
  }
  Ptr<TrackerTargetState> targetState = stateEstimator->estimate( confidenceMaps );
  if( targetState == 0 )
    return false;

  setLastTargetState( targetState );
  return true;
}

void TrackerModel::setLastTargetState( const Ptr<TrackerTargetState>& lastTargetState )
{
  trajectory.push_back( lastTargetState );
}

Ptr<TrackerTargetState> TrackerModel::getLastTargetState() const
{
  return trajectory.back();
}

const std::vector<ConfidenceMap>& TrackerModel::getConfidenceMaps() const
{
  return confidenceMaps;
}

const ConfidenceMap& TrackerModel::getLastConfidenceMap() const
{
  return confidenceMaps.back();
}

/*
 *  TrackerTargetState
 */

Point2f TrackerTargetState::getTargetPosition() const
{
  return targetPosition;
}

void TrackerTargetState::setTargetPosition( const Point2f& position )
{
  targetPosition = position;
}

int TrackerTargetState::getTargetWidth() const
{
  return targetWidth;
}

void TrackerTargetState::setTargetWidth( int width )
{
  targetWidth = width;
}
int TrackerTargetState::getTargetHeight() const
{
  return targetHeight;
}

void TrackerTargetState::setTargetHeight( int height )
{
  targetHeight = height;
}

} /* namespace cv */
