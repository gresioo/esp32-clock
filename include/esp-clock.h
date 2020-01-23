/**
 * @file esp-clock.h
 * @author Grzegorz Wyszyński (gresioo@gmail.com)
 * @brief Header for esp32-clock basing on Sure 3208 display
 * @version 0.1
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef HT1632_h
#define HT1632_h
// Standard command list.
// This list is modified from original code by Bill Westfield

#define HT1632_ID_CMD 0b100	/* ID = 100 - Commands */
#define HT1632_ID_RD  0b110	/* ID = 110 - Read RAM */
#define HT1632_ID_WR  0b101	/* ID = 101 - Write RAM */
#define HT1632_ID_LEN 3         /* IDs are 3 bits */

// Do note that SYSON has been changed to SYSEN
#define HT1632_CMD_SYSDIS 0x00	/* CMD= 0000-0000-x Turn off oscil */
#define HT1632_CMD_SYSEN  0x01	/* CMD= 0000-0001-x Enable system oscil */
#define HT1632_CMD_LEDOFF 0x02	/* CMD= 0000-0010-x LED duty cycle gen off */
#define HT1632_CMD_LEDON  0x03	/* CMD= 0000-0011-x LEDs ON */
#define HT1632_CMD_BLOFF  0x08	/* CMD= 0000-1000-x Blink ON */
#define HT1632_CMD_BLON   0x09	/* CMD= 0000-1001-x Blink Off */
#define HT1632_CMD_SLVMD  0x10	/* CMD= 0001-00xx-x Slave Mode */
#define HT1632_CMD_MSTMD  0x14	/* CMD= 0001-01xx-x Master Mode */
#define HT1632_CMD_RCCLK  0x18	/* CMD= 0001-10xx-x Use on-chip clock */
#define HT1632_CMD_EXTCLK 0x1C	/* CMD= 0001-11xx-x Use external clock */
#define HT1632_CMD_COMS00 0x20	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS01 0x24	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS10 0x28	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS11 0x2C	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_PWM_T  0xA0	/* CMD= 101x-PPPP-x PWM duty cycle - template*/
#define HT1632_CMD_PWM(lvl) (HT1632_CMD_PWM_T | (lvl-1))
  /* Produces the correct command from the given value of lvl. lvl = [0..15] */
#define HT1632_CMD_LEN    8	/* Commands are 8 bits long, excluding the trailing bit */
#define HT1632_ADDR_LEN   7	/* Addresses are 7 bits long */
#define HT1632_WORD_LEN   4     /* Words are 4 bits long */

/**
 * @brief Sends binary data to display device
 * 
 * @param data all the binary data to be sent to device
 * @param lengthOfData length of data
 * @return Returns error code
 */ 
esp_err_t sendToDisplay(int8_t command,int * data,int lengthOfData);
/**
 * @brief Writes one char to display device
 * 
 * 
 * @param textin Char to be displayed
 * @param position Where to position the char (in lines)
 * @return Returns error code
 */
esp_err_t writeToDisplay(char textin,int position);
/**
 * @brief Wait for a short period of time
 * 
 */
esp_err_t waitForAWhile();
esp_err_t sendCommandToDisplay(int8_t command);
esp_err_t sendOneBit(uint32_t level);
void app_main();

#else
//#error "HT1632.h" already defined!
#endif