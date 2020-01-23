#define DISPLAY_CS 23
#define DISPLAY_WR 5
#define DISPLAY_DATA 18
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<DISPLAY_CS) | (1ULL<<DISPLAY_WR) | (1ULL<<DISPLAY_DATA))
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp-clock.h"


esp_err_t waitForAWhile()
{
    vTaskDelay(1/portTICK_PERIOD_MS);
    return ESP_OK;
}

esp_err_t sendOneBit(uint32_t level)
{
    gpio_set_level(DISPLAY_DATA,level);
    waitForAWhile();
    gpio_set_level(DISPLAY_WR,1);
    waitForAWhile();
    gpio_set_level(DISPLAY_WR,0);
    waitForAWhile();
    printf("%i",level);
    return ESP_OK;
}

esp_err_t sendToDisplay(int8_t command,int * data,int lengthOfData)
{
    int i,j; //generic counters
    int column; //column to be stored and then sent out
    // CS to high
    gpio_set_level(DISPLAY_CS,1);
    waitForAWhile();
    gpio_set_level(DISPLAY_CS,0);
    //sending command (3 bits)
    for (i=0;i<3;i++){
        sendOneBit((command&(1<<i))/(1<<i)); //send ith bit
    }
    //memory address - 7 bits - we set it to 0
    for (i=0;i<7;i++){
        sendOneBit(0);
    }
    for (i=0;i<lengthOfData;i++){
        column=data[i];
        for (j=0;j<8;j++)
        {       
            sendOneBit((column&(1<<j))/(1<<j)); //send jth bit
        }
    }
    gpio_set_level(DISPLAY_CS,1);
    return ESP_OK;
}


esp_err_t sendCommandToDisplay(int8_t command)
{
    int i,j; //generic counters
    int column; //column to be stored and then sent out
    // CS to high
    gpio_set_level(DISPLAY_CS,0);
    //sending command (3 bits)
    for (i=0;i<3;i++){
        sendOneBit((command&(1<<i))/(1<<i)); //send ith bit
    }
    return ESP_OK;
}


void app_main()
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    int i,j;
    int LEDstate[32];
    for(i=0;i<8;i++)
    {
        for(j=0;j<32;j++)
        {
            LEDstate[j]=1<<i;
        }
        printf("\naaa\n");
        sendToDisplay(0b101,LEDstate,32);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

