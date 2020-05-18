#pragma once
#include <TeenAstroStepper.h>
//geometry Axis
// backlash control
struct backlash
{
  int             inSeconds;
  volatile int    inSteps;
  volatile bool   correcting;
  volatile int    movedSteps;
  volatile double timerRate;
};

class GeoAxis
{
public:
  long   poleDef;   //in steps
  long   homeDef;   //in steps
  long   stepsPerRot; // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
  double stepsPerDegree;
  double stepsPerSecond;
  double stepsPerCentiSecond;
  long   halfRot;   //in steps
  long   quaterRot; //in steps
private:
  long   m_breakDist; //in steps
 public:
  bool atTarget(const volatile long &deltaTarget)
  {
    return abs(deltaTarget) < m_breakDist;
  }
  void setstepsPerRot(long val)
  {
    stepsPerRot = val;
    stepsPerDegree = stepsPerRot / 360.0;
    stepsPerSecond = stepsPerRot / 86400.0;
    stepsPerCentiSecond = stepsPerRot / 8640000.0;
    halfRot = stepsPerRot / 2L;
    quaterRot = stepsPerRot / 4L;
    m_breakDist = max(2, stepsPerDegree / 3600.0 * 0.2);
    return;
  }
};

class GuideAxis
{
public:
  volatile byte   dir;
  long            duration;
  unsigned long   durationLast;
  double          amount;
  volatile double timerRate;
};

class MotorAxis
{
public:
  unsigned int gear;
  unsigned int stepRot;
  byte micro;
  bool reverse;
  u_int8_t highCurr;
  u_int8_t lowCurr;
  Driver driver;
  void initMotor(Driver::MOTORDRIVER useddriver, int EnPin, int CSPin, int DirPin, int StepPin)
  {
    driver.initMotor(useddriver, stepRot, EnPin, CSPin, DirPin, StepPin, lowCurr * 10, micro);
  }
};