#ifndef __MEMORY_ACCESSOR_H__
#define __MEMORY_ACCESSOR_H__

class MemoryAccessor
{
  public:
    void setOffset(uint32_t offset) {
      m_nAccessOffset = offset;
    }
    void getOffset() {
      return m_nAccessOffset;
    }

  protected:
    uint32_t m_nAccessOffset;
};

#endif
