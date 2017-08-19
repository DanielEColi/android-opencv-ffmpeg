/*
* Copyright (c) BUAA
* All rights reserved.
*
* �ļ����ƣ�ONLINEMIL.HPP
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
#ifndef __OPENCV_ONLINEMIL_HPP__
#define __OPENCV_ONLINEMIL_HPP__

#include "opencv2/core.hpp"
#include <limits>

namespace cv
{

//! @addtogroup tracking
//! @{

//TODO based on the original implementation
//http://vision.ucsd.edu/~bbabenko/project_miltrack.shtml

#define  sign(s)  ((s > 0 ) ? 1 : ((s<0) ? -1 : 0))

class ClfOnlineStump;

class  ClfMilBoost//CV_EXPORTS
{
 public:
  struct  Params//CV_EXPORTS
  {
    Params();
    int _numSel;
    int _numFeat;
    float _lRate;
  };

  ClfMilBoost();
  ~ClfMilBoost();
  void init( const ClfMilBoost::Params &parameters = ClfMilBoost::Params() );
  void update( const Mat& posx, const Mat& negx );
  std::vector<float> classify( const Mat& x, bool logR = true );

  inline float sigmoid( float x )
  {
    return 1.0f / ( 1.0f + exp( -x ) );
  }

 private:
  uint _numsamples;
  ClfMilBoost::Params _myParams;
  std::vector<int> _selectors;
  std::vector<ClfOnlineStump*> _weakclf;
  uint _counter;

};

class ClfOnlineStump
{
 public:
  float _mu0, _mu1, _sig0, _sig1;
  float _q;
  int _s;
  float _log_n1, _log_n0;
  float _e1, _e0;
  float _lRate;

  ClfOnlineStump();
  ClfOnlineStump( int ind );
  void init();
  void update( const Mat& posx, const Mat& negx, const cv::Mat_<float> & posw = cv::Mat_<float>(), const cv::Mat_<float> & negw = cv::Mat_<float>() );
  bool classify( const Mat& x, int i );
  float classifyF( const Mat& x, int i );
  std::vector<float> classifySetF( const Mat& x );

 private:
  bool _trained;
  int _ind;

};

//! @}

} /* namespace cv */

#endif
