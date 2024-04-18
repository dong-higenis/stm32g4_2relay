/*
 * flash.h
 *
 *  Created on: Apr 17, 2024
 *      Author: chand
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

uint8_t flash_spi(uint8_t data);
uint32_t flash_SectorToPage(uint32_t SectorAddress);
uint32_t flash_BlockToPage(uint32_t BlockAddress);
void flash_wait_end(void);
void flash_write_enable(void);
void flash_write_disable(void);
void flash_write_byte(uint8_t pBuffer, uint32_t WriteAddr_inBytes);
void flash_write_page(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize);
void flash_write_sector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);

void flash_read_byte(uint8_t* pBuffer, uint32_t Bytes_Address);
void flash_read_bytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void flash_read_page(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize);
void flash_read_sector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);

uint8_t flash_read_Status(uint8_t register_num);
void flash_erase_chip(void);
void flash_erase_sector(uint32_t SectorAddr);
void flash_erase_block(uint32_t BlockAddr);
uint32_t flash_read_ID(void);
void flash_read_uniqID(void);



#endif /* INC_FLASH_H_ */
