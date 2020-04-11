#ifndef __MEMORY_DEVICE_H__
#define __MEMORY_DEVICE_H__

class MemoryDevice
{
  public:
    virtual uint32_t write(uint8_t c) = 0;
    virtual uint32_t write(void* pData, uint32_t length) = 0;

    virtual uint8_t read(uint32_t addr) = 0;
    virtual void read(uint32_t addr, void* pData, uint32_t length) = 0;

    uint32_t size() { return m_nSize; }

  protected:
    uint32_t m_nSize;
};

#endif
