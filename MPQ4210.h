#include <stdint.h>

//To use this library, you need to provide the following external functions, which are the functions that the SC8815 library needs to use
extern void I2C_WriteRegByte(uint8_t SlaveAddress, uint8_t RegAddress, uint8_t ByteData);   //Write a byte to the device register via I2C
extern uint8_t I2C_ReadRegByte(uint8_t SlaveAddress, uint8_t RegAddress);                   //Read a byte from the device register via I2C
extern void SoftwareDelay(uint8_t ms);                                                      //Software delay in milliseconds

//MPQ4210 address definition
#define MPQ4210_ADDR1                   0x60
#define MPQ4210_ADDR2                   0x66

//MPQ4214 address definition
#define MPQ4210_ADDR1                   0x60
#define MPQ4210_ADDR2                   0x62
#define MPQ4210_ADDR3                   0x64
#define MPQ4210_ADDR4                   0x66

//MPQ421x register definition
#define MPQREG_REF_LSB                  0x00
#define MPQREG_REF_MSB                  0x01
#define MPQREG_CONTROL1                 0x02
#define MPQREG_CONTROL2                 0x03
#define MPQREG_ILIM                     0x04
#define MPQREG_INT_STATUS               0x05
#define MPQREG_INT_MASK                 0x06

/*
* MPQ4210 and MPQ4214 Hardware initialization structure parameters
* @{
*/

// MPQ_REF parameters definition
#define MPQ_REF_LSB_MASK                0x007
#define MPQ_REF_MSB_MASK                0x7F8               

// MPQ_CONTROL1_GO_BIT parateters definition
#define MPQ_CONTROL1_GO_BIT_MASK        0xFD
#define MPQ_CONTROL1_GO_BIT_CLR         0x00
#define MPQ_CONTROL1_GO_BIT_SET         0x02

// MPQ_CONTROL1_ENPWR parameters definition
#define MPQ_CONTROL1_ENPWR_MASK         0xFE
#define MPQ_CONTROL1_ENPWR_DIS          0x00
#define MPQ_CONTROL1_ENPWR_EN           0x01

// MPQ_CONTROL1_PNG_LATCH parameters definition
#define MPQ_CONTROL1_PNG_LATCH_MASK     0xF7
#define MPQ_CONTROL1_PNG_LATCH_CLR      0x00
#define MPQ_CONTROL1_PNG_LATCH_SET      0x08

// MPQ_CONTROL1_DITHER parameters definition
#define MPQ_CONTROL1_DITHER_MASK        0xEF
#define MPQ_CONTROL1_DITHER_DIS         0x00
#define MPQ_CONTROL1_DITHER_EN          0x10

// MPQ_CONTROL1_DISCHG parameters definition
#define MPQ_CONTROL1_DISCHG_MASK        0xDF
#define MPQ_CONTROL1_DISCHG_OFF         0x00
#define MPQ_CONTROL1_DISCHG_ON          0x20

// MPQ_CONTROL1_SR parameters definition
#define MPQ_CONTROL1_SR_MASK            0x3F
#define MPQ_CONTROL1_SR_38mV_ms         0x00
#define MPQ_CONTROL1_SR_50mV_ms         0x40
#define MPQ_CONTROL1_SR_75mV_ms         0x80
#define MPQ_CONTROL1_SR_150mV_ms        0xC0

// MPQ_CONTROL2_FSW parateters definition
#define MPQ_CONTROL2_FSW_MASK           0x3F
#define MPQ_CONTROL2_FSW_200khz         0x00
#define MPQ_CONTROL2_FSW_300khz         0x40
#define MPQ_CONTROL2_FSW_400khz         0x80
#define MPQ_CONTROL2_FSW_600khz         0xC0

// MPQ_CONTROL2_BBFSW parateters definition
#define MPQ_CONTROL2_BBFSW_MASK         0xEF
#define MPQ_CONTROL2_BBFSW_OFF          0x00
#define MPQ_CONTROL2_BBFSW_ON           0x10

// MPQ_CONTROL2_OCP_MODE parameters definition
#define MPQ_CONTROL2_OCP_MODE_MASK      0xF3
#define MPQ_CONTROL2_OCP_MODE_NONE      0x00
#define MPQ_CONTROL2_OCP_MODE_HICCUP    0x04
#define MPQ_CONTROL2_OCP_MODE_LATCH     0x08

// MPQ_CONTROL2_OVP_MODE parameters definition
#define MPQ_CONTROL2_OVP_MODE_MASK      0xFC
#define MPQ_CONTROL2_OVP_MODE_NONE      0x00
#define MPQ_CONTROL2_OVP_MODE_HICCUP    0x04
#define MPQ_CONTROL2_OVP_MODE_LATCH     0x08

// MPQ_ILIM Parameters definition for MPQ4210 devices
#define MPQ4210_ILIM_MASK               0xF8
#define MPQ4210_ILIM_27_9mV             0x00
#define MPQ4210_ILIM_33_3mV             0x01
#define MPQ4210_ILIM_39_3mV             0x02
#define MPQ4210_ILIM_45_1mV             0x03
#define MPQ4210_ILIM_51_2mV             0x04
#define MPQ4210_ILIM_56_8mV             0x05
#define MPQ4210_ILIM_62_8mV             0x06
#define MPQ4210_ILIM_68_7mV             0x07

// MPQ_ILIM Parameters definition for MPQ4214 devices
#define MPQ4214_ILIM_MASK               0xF8
#define MPQ4214_ILIM_26mV               0x00
#define MPQ4214_ILIM_32mV               0x01
#define MPQ4214_ILIM_38mV               0x02
#define MPQ4214_ILIM_45mV               0x03
#define MPQ4214_ILIM_50mV               0x04
#define MPQ4214_ILIM_56mV               0x05
#define MPQ4214_ILIM_62mV               0x06
#define MPQ4214_ILIM_68mV               0x07

// MPQ_INTMASK parameters definition for MPQ4210 devices
#define MPQ4210_INT_OTP                 0xEF
#define MPQ4210_INT_OVP                 0xFB
#define MPQ4210_INT_OCP                 0xFD
#define MPQ4210_INT_PNG                 0xFE

// MPQ_INTMASK parameters definition for MPQ4214 devices
#define MPQ4214_INT_OTP                 0xEF
#define MPQ4214_INT_CC                  0xF7
#define MPQ4214_INT_OVP                 0xFB
#define MPQ4214_INT_OCP                 0xFD
#define MPQ4214_INT_PNG                 0xFE

/*
* MPQ4210 hardware configuration functions
*/

// Function to set the VREF registers on the MPQ421x devices
void MPQ_SetVoltageReference(uint8_t deviceAddress,uint16_t Vref);

// Functions to set and clear ENPWR bit on MPQ421x devices
void MPQ_DisablePowerSwitching(uint8_t deviceAddress);
void MPQ_EnablePowerSwitching(uint8_t deviceAddress);

// Function to set GO_BIT on MPQ421x devices
void MPQ_SET_GOBIT(uint8_t deviceAddress);

// Functions to set and clear PNG_Latch bit in MPQ421x devices
void MPQ_PNG_Latch_Disable(uint8_t deviceAddress);
void MPQ_PNG_Latch_Enable(uint8_t deviceAddress);

// Function to enable frequency spread spectrum on MPQ421x devices
void MPQ_FreqSpreadSpectrum_Enable(uint8_t deviceAddress);

// Function to disable frequency spread spectrum on MPQ421x devices
void MPQ_FreqSpreadSpectrum_Disable(uint8_t deviceAddress);

// Function for enabling output discharge path to ground on MPQ421X devices
void MPQ_OutputDischargePath_Enable(uint8_t deviceAddress);

// Function for disabling output discharge path to ground on MPQ421X devices
void MPQ_OutputDischargePath_Disable(uint8_t deviceAddress);

// Function to set VREF slew rate on MPQ421x devices
void MPQ_SetVREF_SlewRate(uint8_t deviceAddress, uint8_t SlewRate);

// Function to set the switching frequency on the MPQ421x device
void MPQ_SetSwitchingFrequency(uint8_t deviceAddress,uint8_t Fsw);

// Functions to set and clear BB_FSW bit in MPQ421x devices
void MPQ_Set_BB_FSW_HIGH(uint8_t deviceAddress);
void MPQ_Set_BB_FSW_LOW(uint8_t deviceAddress);

// Function to set OCP Mode on the MPQ421x device
void MPQ_setOCPMode(uint8_t deviceAddress,uint8_t OCPMode);

// Function to set OVP Mode on the MPQ421x device
void MPQ_setOVPMode(uint8_t deviceAddress,uint8_t OVPMode);

// Function to set ILIM thresthold on MPQ4210 devices
void MPQ_setILIM(uint8_t deviceAddress,uint8_t ILIMthreshold);

// Function to reset Interrupt Status vector in MPQ421x devices
void MPQ_IntClear(uint8_t deviceAddress);

// Function for enabling interrupts in MPQ421x devices
void MPQ_IntEnable(uint8_t deviceAddress);

// Function for disabling interrupts in MPQ421x devices
void MPQ_IntDisable(uint8_t deviceAddress);