/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�trackerSampler.CPP
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
 *  TrackerSampler
 */

/*
 * Constructor
 */
TrackerSampler::TrackerSampler()
{
  blockAddTrackerSampler = false;
}

/*
 * Destructor
 */
TrackerSampler::~TrackerSampler()
{

}

void TrackerSampler::sampling( const Mat& image, Rect boundingBox )
{

  clearSamples();

  for ( size_t i = 0; i < samplers.size(); i++ )
  {
    std::vector<Mat> current_samples;
    samplers[i].second->sampling( image, boundingBox, current_samples );

    //push in samples all current_samples
    for ( size_t j = 0; j < current_samples.size(); j++ )
    {
      std::vector<Mat>::iterator it = samples.end();
      samples.insert( it, current_samples.at( j ) );
    }
  }

  if( !blockAddTrackerSampler )
  {
    blockAddTrackerSampler = true;
  }
}

bool TrackerSampler::addTrackerSamplerAlgorithm( String trackerSamplerAlgorithmType )
{
  if( blockAddTrackerSampler )
  {
    return false;
  }
  Ptr<TrackerSamplerAlgorithm> sampler = TrackerSamplerAlgorithm::create( trackerSamplerAlgorithmType );

  if( sampler == 0 )
  {
    return false;
  }

  samplers.push_back( std::make_pair( trackerSamplerAlgorithmType, sampler ) );

  return true;
}

bool TrackerSampler::addTrackerSamplerAlgorithm( Ptr<TrackerSamplerAlgorithm>& sampler )
{
  if( blockAddTrackerSampler )
  {
    return false;
  }

  if( sampler == 0 )
  {
    return false;
  }

  String trackerSamplerAlgorithmType = sampler->getClassName();
  samplers.push_back( std::make_pair( trackerSamplerAlgorithmType, sampler ) );

  return true;
}

const std::vector<std::pair<String, Ptr<TrackerSamplerAlgorithm> > >& TrackerSampler::getSamplers() const
{
  return samplers;
}

const std::vector<Mat>& TrackerSampler::getSamples() const
{
  return samples;
}

void TrackerSampler::clearSamples()
{
  samples.clear();
}

} /* namespace cv */
