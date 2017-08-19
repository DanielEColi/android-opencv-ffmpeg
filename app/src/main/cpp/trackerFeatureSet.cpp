/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�trackerFeatureSet.CPP
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
 *  TrackerFeatureSet
 */

/*
 * Constructor
 */
TrackerFeatureSet::TrackerFeatureSet()
{
  blockAddTrackerFeature = false;
}

/*
 * Destructor
 */
TrackerFeatureSet::~TrackerFeatureSet()
{

}

void TrackerFeatureSet::extraction( const std::vector<Mat>& images )
{

  clearResponses();
  responses.resize( features.size() );

  for ( size_t i = 0; i < features.size(); i++ )
  {
    Mat response;
    features[i].second->compute( images, response );
    responses[i] = response;
  }

  if( !blockAddTrackerFeature )
  {
    blockAddTrackerFeature = true;
  }
}

void TrackerFeatureSet::selection()
{

}

void TrackerFeatureSet::removeOutliers()
{

}

bool TrackerFeatureSet::addTrackerFeature( String trackerFeatureType )
{
  if( blockAddTrackerFeature )
  {
    return false;
  }
  Ptr<TrackerFeature> feature = TrackerFeature::create( trackerFeatureType );

  if( feature == 0 )
  {
    return false;
  }

  features.push_back( std::make_pair( trackerFeatureType, feature ) );

  return true;
}

bool TrackerFeatureSet::addTrackerFeature( Ptr<TrackerFeature>& feature )
{
  if( blockAddTrackerFeature )
  {
    return false;
  }

  String trackerFeatureType = feature->getClassName();
  features.push_back( std::make_pair( trackerFeatureType, feature ) );

  return true;
}

const std::vector<std::pair<String, Ptr<TrackerFeature> > >& TrackerFeatureSet::getTrackerFeature() const
{
  return features;
}

const std::vector<Mat>& TrackerFeatureSet::getResponses() const
{
  return responses;
}

void TrackerFeatureSet::clearResponses()
{
  responses.clear();
}

} /* namespace cv */
