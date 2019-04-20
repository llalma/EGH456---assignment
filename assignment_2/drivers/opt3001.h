/**************************************************************************************************
*  Filename:       opt3001.h
*  By:             Jesse Haviland, Contains adapted code authored by TI and applicable licenses apply
*  Created:        1 February 2019
*  Revised:        2 February 2019
*  Revision:       1.0
*
*  Description:    API for controlling and reading from the TI OP3001 Optical Sensor
*************************************************************************************************/



#ifndef OPT3001_H
#define OPT3001_H

#ifdef __cplusplus
extern "C"
{
#endif



// ----------------------- Exported prototypes -----------------------
extern bool SensorOpt3001Init(void);
extern void SensorOpt3001Enable(bool enable);
extern bool SensorOpt3001ReadLight(uint16_t *rawData);
extern void SensorOpt3001ReadConfig(uint16_t *rawData);
extern void SensorOpt3001ReadResult(uint16_t *rawData);
void SensorOpt3001SetRegister(uint16_t rawData,int reg);
extern void SensorOpt3001Convert(uint16_t rawData, float *convertedLux);
extern bool SensorOpt3001Test(void);

extern bool SensorOpt3001WriteLow(void);
//extern uint8_t SensorOpt3001ReadConfig();



#ifdef __cplusplus
}
#endif

#endif /* OPT3001_H */
