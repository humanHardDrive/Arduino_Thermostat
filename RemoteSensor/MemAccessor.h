#ifndef __MEM_ACCESSOR_H__
#define __MEM_ACCESSOR_H__

#include <stdint.h>

class MemAccessor
{
  public:
    void setOffset(uint32_t nOffset);
    uint32_t getOffset() { return m_nOffset; }

    uint32_t size() { return m_nSize; }
  
  protected:
    uint32_t m_nOffset;
    uint32_t m_nSize;
};

#endif
