// STL includes
#include <vector>
#include <string>

// C includes

// Library includes
#include <cxxtest/TestSuite.h>

// Project includes
#include <RtcEvent.h>

using namespace std;

class RtcEventTestSuite: public CxxTest::TestSuite
{
  RtcEvent rte;
public:
  void setUp()
  {
  }

  void testEmpty( void )
  {
  }
};
// vim:cin:ai:sts=2 sw=2 ft=cpp
