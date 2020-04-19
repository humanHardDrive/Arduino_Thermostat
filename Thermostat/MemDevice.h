#ifndef __MEM_DEVICE_H__
#define __MEM_DEVICE_H__

class MemDevice
{
  public:
    uint32_t size() { return m_nSize; }

    virtual uint8_t read(uint32_t addr) = 0;
    virtual uint32_t read(uint32_t addr, void* pBuf, uint32_t len) = 0;

    virtual void write(uint32_t addr, uint8_t v) = 0;
    virtual uint32_t write(uint32_t addr, void* pBuf, uint32_t len) = 0;

  protected:
    uint32_t m_nSize;
};

#endif
