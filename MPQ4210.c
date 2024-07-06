//Include header file
#include "MPQ4210.h"

/******************************************
* @ brief Configuration of the VREF voltage
* @ param Vref uint16_t containing the new VREF voltage
*       should be 11 bits at most but if its not a logical and to
*       0x7FF is done to clean any trailing bit
* @ note can be used to set a new Vout but you have to take R1 and 
*       R2 into consideration on doing so Vout would be given by:
*       Vout = ((Vref/1000)*(R1+R2))/R1
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_SetVoltageReference(uint8_t deviceAddress, uint16_t Vref){
    uint8_t refLSB,refMSB;
    // First three bits from the Vref parameter are the new ref LSB
    refLSB = (uint8_t)(Vref&MPQ_REF_LSB_MASK);
    // Bits 10:3 from the Vref parameter are the new ref MSB, and they
    // are shifted three times to the right to fill an eight bit register 
    refMSB = (uint8_t)((Vref&MPQ_REF_MSB_MASK)>>3);
    // Now we fill the I2C register which correspond to the REFLSB and REFMSB
    I2C_WriteRegByte(deviceAddress, MPQREG_REF_LSB, refLSB);
    I2C_WriteRegByte(deviceAddress, MPQREG_REF_MSB, refMSB);
    
    // Now that we have set the Vref registers, we have to turn down the power
    // switching and enable de GO_BIT for the new reference to be set
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_GO_BIT_MASK)|MPQ_CONTROL1_GO_BIT_SET);
}
/******************************************
* @ brief Disable power switching
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Clears the ENPWR bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_DisablePowerSwitching(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Clear the ENPWR bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_DIS);
}
/******************************************
* @ brief Enable power switching
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Sets the ENPWR bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_EnablePowerSwitching(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the ENPWR bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_EN);
}
/******************************************
* @ brief Set the GOB_BIT
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Sets the GO_BIT bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_SET_GOBIT(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_GO_BIT_MASK)|MPQ_CONTROL1_GO_BIT_SET);
}
/******************************************
* @ brief Disable the PNG latch functionality
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Clears the PNG_Latch bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_PNG_Latch_Disable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_PNG_LATCH_MASK)|MPQ_CONTROL1_PNG_LATCH_CLR);
}
/******************************************
* @ brief Enable the PNG latch functionality
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Sets the PNG_Latch bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_PNG_Latch_Enable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_PNG_LATCH_MASK)|MPQ_CONTROL1_PNG_LATCH_SET);
}
/******************************************
* @ brief Enable Spread Spectrum Frequency switching
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Sets the Dither bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_FreqSpreadSpectrum_Enable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_DITHER_MASK)|MPQ_CONTROL1_DITHER_EN);
}
/******************************************
* @ brief Disable Spread Spectrum Frequency switching
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Clears the Dither bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_FreqSpreadSpectrum_Disable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_DITHER_MASK)|MPQ_CONTROL1_DITHER_DIS);
}
/******************************************
* @ brief Enable discharge path to ground from Cout
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Sets the DISCHG bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_OutputDischargePath_Enable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_DISCHG_MASK)|MPQ_CONTROL1_DISCHG_ON);
}
/******************************************
* @ brief Disable discharge path to ground from Cout
* @ param uint8_t deviceAddress, contains the address of the MPQ
*       that is trying to be reached
* @ note Clears the DISCHG bit of the CONTROL1 register
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_OutputDischargePath_Disable(uint8_t deviceAddress){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_DISCHG_MASK)|MPQ_CONTROL1_DISCHG_OFF);
}
/******************************************
* @ brief Configure Slew Rate of VREF
* @ param uint8_t deviceAddress, uint8_t SlewRate can be one of these values:
*       - MPQ_CONTROL1_SR_38mV_ms
*       - MPQ_CONTROL1_SR_50mV_ms
*       - MPQ_CONTROL1_SR_75mV_ms
*       - MPQ_CONTROL1_SR_150mV_ms
* @ note Set the slewrate of Vref, but Vout SR is controlled by SS function
*******************************************/
// Must use when MPQ4210's address is 0x66
void MPQ_SetVREF_SlewRate(uint8_t deviceAddress, uint8_t SlewRate){
    // Read CONTROL1 register to a temp variable
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL1);
    // Set the GO_BIT bit and keep the others
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_SR_MASK)|SlewRate);
}
/******************************************
* @ brief Configuration of the switching frequency through FSW reg
* @ param Fsw uint8_t containing the switching frequency to be set
*       from the following selection
*       - MPQ_CONTROL2_FSW_200khz
*       - MPQ_CONTROL2_FSW_300khz
*       - MPQ_CONTROL2_FSW_400khz
*       - MPQ_CONTROL2_FSW_600khz
* @ note switching frequency changes smoothly to its new value after
*       FSW has been written.
*******************************************/
// Must use when MPQ4210's address is 0x64
void MPQ_SetSwitchingFrequency(uint8_t deviceAddress, uint8_t Fsw){
    // We read the full control2 register in order to be able to modify
    // the FSW bits without modifying any other register
    uint8_t tmp = I2C_ReadRegByte(deviceAddress,MPQREG_CONTROL2);
    // We modify only de FSW bits and set them to the new Fsw value
    I2C_WriteRegByte(deviceAddress,MPQREG_CONTROL2,(tmp&MPQ_CONTROL2_FSW_MASK)|Fsw);
}
/******************************************
* @ brief Configuration of average current limit through ILIM reg
* @ param ILIMthreshold uint8_t containing the threshold to be set
*       from the following selection for MPQ4210 devices
*       - MPQ_ILIM_27_9mV
*       - MPQ_ILIM_33_3mV
*       - MPQ_ILIM_39_3mV
*       - MPQ_ILIM_45_1mV
*       - MPQ_ILIM_51_2mV
*       - MPQ_ILIM_56_8mV
*       - MPQ_ILIM_62_8mV
*       - MPQ_ILIM_68_7mV
*       And from this selection for MPQ4214 devices
*       - MPQ4214_ILIM_26mV
*       - MPQ4214_ILIM_32mV
*       - MPQ4214_ILIM_38mV
*       - MPQ4214_ILIM_45mV
*       - MPQ4214_ILIM_50mV
*       - MPQ4214_ILIM_56mV
*       - MPQ4214_ILIM_62mV
*       - MPQ4214_ILIM_68mV               
* @ note you set a new current limit threshold given the voltage measured
*       between the IAVGP and IAVGN pins which means the actual average current
*       limit is given by:
*       IAVG Limit = Threshold(V)/Rsense(Ohms)
*******************************************/
// Must use when MPQ4210's address is 0x64
void MPQ_setILIM1(uint8_t deviceAddress, uint8_t ILIMthreshold){
    // We set the ILIM register to the new value set
    I2C_WriteRegByte(deviceAddress,MPQREG_ILIM,ILIMthreshold);
}