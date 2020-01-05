#define DISPLAY_CS 14
#define DISPLAY_WR 15
#define DISPLAY_DATA 16

esp_err_t waitForAWhile()
{
    vTaskDelay(10/portTICK_PERIOD_MS);
    return ESP_OK;
}

esp_err_t sendOneBit(uint32_t level)
{
    gpio_set_level(DISPLAY_WR,1);
    gpio_set_level(DISPLAY_DATA,level);
    waitForAWhile();
    gpio_set_level(DISPLAY_WR,0);
    waitForAWhile();
}

esp_err_t sendToDisplay(int8_t command,int * data,int lengthOfData)
{
    int i,j; //generic counters
    int column; //column to be stored and then sent out
    // CS to high
    gpio_set_level(DISPLAY_CS,1);
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
            sendOneBit((column&(1<<i))/(1<<i)); //send ith bit
        }
    }
    return ESP_OK
}



