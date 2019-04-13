#include "MB85RS.h"

MB85RS::MB85RS(byte csPin) :
  m_CSPin(csPin)
{
  pinMode(m_CSPin, INPUT);
}

MB85RS::~MB85RS()
{

}

