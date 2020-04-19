#ifndef __MEM_ACCESSOR_H__
#define __MEM_ACCESSOR_H__

class MemAccessor
{
  public:
    void setOffset(uint32_t nOffset);
    uint32_t getOffset() { return m_nOffset; }
  
  protected:
    uint32_t m_nOffset;
};

#endif
