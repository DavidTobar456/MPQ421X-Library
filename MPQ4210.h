#include <stdint.h>

//To use this library, you need to provide the following external functions, which are the functions that the SC8815 library needs to use
extern void I2C_WriteRegByte(uint8_t SlaveAddress, uint8_t RegAddress, uint8_t ByteData);   //Write a byte to the device register via I2C
extern uint8_t I2C_ReadRegByte(uint8_t SlaveAddress, uint8_t RegAddress);                   //Read a byte from the device register via I2C
extern void SoftwareDelay(uint8_t ms);                                                      //Software delay in milliseconds

//MPQ4210 register address definition
#define MPQ4210_ADDR1                   0x50
#define MPQ4210_ADDR2                   0x50
#define MPQREG_REF_LSB                  0x00
#define MPQREG_REF_MSB                  0x01
#define MPQREG_CONTROL1                 0x02
#define MPQREG_CONTROL2                 0x03
#define MPQREG_ILIM                     0x04
#define MPQREG_INT_STATUS               0x05
#define MPQREG_INT_MASK                 0x06

/*
* MPQ4210 Hardware initialization structure parameters
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

// MPQ_CONTROL2_FSW parateters definition
#define MPQ_CONTROL2_FSW_MASK           0x3F
#define MPQ_CONTROL2_FSW_200khz         0x00
#define MPQ_CONTROL2_FSW_300khz         0x40
#define MPQ_CONTROL2_FSW_400khz         0x80
#define MPQ_CONTROL2_FSW_600khz         0xC0

// MPQ_CONTROL2_OCP_MODE parameters definition
#define MPQ_CONTROL2_OCP_MODE_MASK      0xF3
#define MPQ_CONTROL2_OCP_MODE_NONE      0x00
#define MPQ_CONTROL2_OCP_MODE_HICCUP    0x04
#define MPQ_CONTROL2_OCP_MODE_LATCH     0x08

// MPQ_CONTROL2_OCP_MODE parameters definition
#define MPQ_CONTROL2_OVP_MODE_MASK      0xFC
#define MPQ_CONTROL2_OVP_MODE_NONE      0x00
#define MPQ_CONTROL2_OVP_MODE_HICCUP    0x04
#define MPQ_CONTROL2_OVP_MODE_LATCH     0x08

// MPQ_ILIM Parameters definition
#define MPQ_ILIM_27_9mV                 0x00
#define MPQ_ILIM_33_3mV                 0x01
#define MPQ_ILIM_39_3mV                 0x02
#define MPQ_ILIM_45_1mV                 0x03
#define MPQ_ILIM_51_2mV                 0x04
#define MPQ_ILIM_56_8mV                 0x05
#define MPQ_ILIM_62_8mV                 0x06
#define MPQ_ILIM_68_7mV                 0x07

/*
* MPQ4210 hardware configuration functions
*/

// Function to set the VREF registers on the MPQ4210 device
// when MPQ4210's address is 0x64
void MPQ_SetVoltageReference1(uint16_t Vref);

// Function to set the VREF registers on the MPQ4210 device
// when MPQ4210's address is 0x66
void MPQ_SetVoltageReference2(uint16_t Vref);

// Function to set the switching frequency on the MPQ4210 device
// when MPQ4210's address is 0x64
void MPQ_SetSwitchingFrequency1(uint8_t Fsw);

// Function to set the switching frequency on the MPQ4210 device
// when MPQ4210's address is 0x66
void MPQ_SetSwitchingFrequency2(uint8_t Fsw);

// Function to set OVP Mode on the MPQ4210 device
// when MPQ4210's address is 0x64
void MPQ_setOCPMode1(uint8_t OVPMode);

// Function to set OVP Mode on the MPQ4210 device
// when MPQ4210's address is 0x66
void MPQ_setOCPMode2(uint8_t OVPMode);

// Function to set OVP Mode on the MPQ4210 device
// when MPQ4210's address is 0x64
void MPQ_setOVPMode2(uint8_t OVPMode);

// Function to set OVP Mode on the MPQ4210 device
// when MPQ4210's address is 0x66
void MPQ_setOVPMode2(uint8_t OVPMode);

// Function to set ILIM thresthold
// when MPQ4210's address is 0x64
void MPQ_setILIM1(uint8_t ILIMthreshold);

// Function to set ILIM thresthold
// when MPQ4210's address is 0x66
void MPQ_setILIM2(uint8_t ILIMthreshold);

