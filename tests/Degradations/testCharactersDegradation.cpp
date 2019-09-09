#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Degradations/GrayscaleCharsDegradationModel.hpp"

#include "testCommon.hpp" //checkEqual

static
void
testSimple(int imageType)
{
  //Apply GrayscaleCharsDegradationModel on random image
  //Check that the output type is the same than the input type.
  //Check that the input image is not modified.
  
  const int ROWS = 100;
  const int COLS = 100;    
    
  cv::Mat img(ROWS, COLS, imageType);

  //add gaussian noise
  cv::randn(img, 128, 30);

  REQUIRE( imageType == img.type() );  

  cv::Mat imgClone = img.clone();
  
  const int level = 5;

  dc::GrayscaleCharsDegradationModel dcm(img);

  cv::Mat out = dcm.degradateByLevel_cv(level);

 REQUIRE( out.type() == imageType );
 REQUIRE( checkEqual(img, imgClone) );
}

TEST_CASE( "Testing CharactersDegradation" )
{ 

  SECTION("Testing Characters Degradation produces output image of same type")
  {
    testSimple(CV_8UC1);
    //testSimple(CV_8UC3);
    //testSimple(CV_8UC4);
  }

}


