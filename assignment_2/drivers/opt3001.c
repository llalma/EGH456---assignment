/**************************************************************************************************
*  Filename:       opt3001.h
*  By:             Jesse Haviland, Contains adapted code authored by TI and applicable licenses apply
*  Created:        1 February 2019
*  Revised:        23 March 2019
*  Revision:       2.0
*
*  Description:    API for controlling and reading from the TI OP3001 Optical Sensor
*************************************************************************************************/



// ----------------------- Includes -----------------------
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "opt3001.h"
#include "utils/uartstdio.h"
#include "i2cOptDriver.h"



// ----------------------- Constants -----------------------

// Slave address
#define OPT3001_I2C_ADDRESS             0x47
#define OPT3001_I2C_ADDRESS_R           0xC7

// Register addresses
#define REG_RESULT                      0x00
#define REG_CONFIGURATION               0x01
#define REG_LOW_LIMIT                   0x02
#define REG_HIGH_LIMIT                  0x03
#define REG_MANUFACTURER_ID             0x7E
#define REG_DEVICE_ID                   0x7F

// Register values
#define MANUFACTURER_ID                 0x5449  // TI
#define DEVICE_ID                       0x3001  // Opt 3001
#define CONFIG_RESET                    0xC810
#define CONFIG_TEST                     0xCC10
#define CONFIG_ENABLE                   0x10C4 // 0xC410   - 100 ms, continuous
#define CONFIG_DISABLE                  0x10C0 // 0xC010   - 100 ms, shutdown

// Bit values
#define DATA_RDY_BIT                    0x0080  // Data ready



/*
 * Sets the sensor into shutdown mode
 */
bool SensorOpt3001Init(void)
{
    SensorOpt3001Enable(false);
    return true;
}



/*
 * Sets the sensor configuration into either shutdown mode (false) or continuous mode (true)
 */
void SensorOpt3001Enable(bool enable)
{
    uint16_t val;

    if (enable)
    {
        val = CONFIG_ENABLE;
    }
    else
    {
        val = CONFIG_DISABLE;
    }

    WriteI2C(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, (uint8_t*)&val);
}



/*
 * Checks CONFIGURATION register to see if data is ready
 * If ready, reads data from RESULT register and stores it in *rawData
 * Returns true if data is valid
 */
bool SensorOpt3001ReadLight(uint16_t *rawData)
{
    bool success;
    uint16_t val;

    SensorOpt3001ReadConfig(&val);

    success = ( (val >> 8 & 0x00FF) & DATA_RDY_BIT) == DATA_RDY_BIT;

    if (success)
    {
        SensorOpt3001ReadResult(&val);

        *rawData = (val << 8) | (val>>8 &0xFF);
    } else {
        *rawData = 0;
    }

    return success;
}



/*
 * Reads RESULT register
 */
void SensorOpt3001ReadResult(uint16_t *rawData)
{
    ReadI2C(OPT3001_I2C_ADDRESS, REG_RESULT, (uint8_t *)rawData);
}

/*
 * Set limit-register
 */
void SensorOpt3001SetRegister(uint16_t rawData,int reg)
{
    if(reg == 1){
        WriteI2C(OPT3001_I2C_ADDRESS, REG_LOW_LIMIT, (uint8_t *)&rawData);
    }else{
        WriteI2C(OPT3001_I2C_ADDRESS, REG_HIGH_LIMIT, (uint8_t *)&rawData);
    }

}



/*
 * Reads CONFIGURATION register
 * Returns contents of register
 */
void SensorOpt3001ReadConfig(uint16_t *rawData)
{
    ReadI2C(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, (uint8_t *)rawData);
}



/*
 * Reads MANUFACTURER_ID register to check if i2c and device is working
 * Reads DEVICE_ID register to check if i2c and device is working
 * Returns true if data is valid
 */
bool SensorOpt3001Test(void)
{
    uint16_t val = 0;

    // Check manufacturer ID
    ReadI2C(OPT3001_I2C_ADDRESS, REG_MANUFACTURER_ID, (uint8_t *)&val);

    uint8_t a, b;

    a = val & 0x00FF;
    b = val >> 8 & 0x00FF;

    if (!a == 84 || !b == 73)
    {
        return false;
    }

    UARTprintf("Manufacturer ID Correct: %c%c\n", a, b);

    // Check device ID
    ReadI2C(OPT3001_I2C_ADDRESS, REG_DEVICE_ID, (uint8_t *)&val);

    a = val & 0x00FF;
    b = val >> 8 & 0x00FF;

    if (!a == 48 || !b == 1)
    {
        return false;
    }

    UARTprintf("Device ID Correct: %2x%02x\n", a, b);

    return true;
}



/*
 * Converts rawData into lux measurement
 * Returns converted lux
 */
void SensorOpt3001Convert(uint16_t rawData, float *convertedLux)
{
    uint16_t e, m;

    m = rawData & 0x0FFF;
    e = (rawData & 0xF000) >> 12;

    *convertedLux = m * (0.01 * exp2(e));
}



