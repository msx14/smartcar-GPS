#include "MySPI.h"

/*!
 *  @brief      icm20602+д�Ĵ���
 *  @param      address   �Ĵ�����ַ
 *  @param      data        ��Ҫд�������
 *  @return     ��
 *  @since      XMU-���ܳ���
 *  Sample usage:    
 */
void icm20602_writebyte(uint8 address,uint8 data)
{
  spi_mosi_cmd(icm20602_SPI, icm20602_CS, &address, NULL, &data, NULL, 1 , 1); 
}

/*!
 *  @brief      icm20602+���Ĵ���
 *  @param      address   �Ĵ�����ַ
 *  @return     ����������
 *  @since      XMU-���ܳ���
 *  Sample usage:       
 */
uint8 icm20602_readbyte(uint8 address)
{
  uint8 data;
  uint8 address_read = address | 0x80;
  spi_mosi_cmd(icm20602_SPI, icm20602_CS, &address_read , NULL, NULL, &data, 1 , 1);
  return data;
}

/*!
 *  @brief      icm20602+��ȡ����+���ݺϳ�
 *  @param      address   �Ĵ���
 *  @return     �ϳɵ�����
 *  @since      XMU-���ܳ���
 *  Sample usage:    
 */

int16 icm20602_GetDoubleData(uint8 address)
{
  uint16 data=0x0000;
  data=icm20602_readbyte(address);
  data=(uint16)((data<<8)&0xff00);                              //icm20602_...._H��8λ��������8λ
  data+=icm20602_readbyte(address+1); 
  return (int16)data;//�ϳ����ݣ�Ϊ�з���������  icm20602_...._H��icm20602_...._L��ͬ���16λ����
}