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


/**
 * @brief Sends binary data to display device
 * 
 * @param data all the binary data to be sent to device
 * @param lengthOfData length of data
 * @return Returns error code
 */ 
esp_err_t sendToDisplay(int8_t command,int * data,int lengthOfData)
/**
 * @brief Writes one char to display device
 * 
 * 
 * @param textin Char to be displayed
 * @param position Where to position the char (in lines)
 * @return Returns error code
 */
esp_err_t writeToDisplay(char textin,int position)