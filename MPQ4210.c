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
void MPQ_SetVoltageReference1(uint16_t Vref){
    // At first we make sure ENPWR is set to 0
    // Now that we have set the Vref registers, we have to turn down the power
    // switching and enable de GO_BIT for the new reference to be set
    uint8_t tmp = I2C_ReadRegByte(MPQ4210_ADDR1,MPQREG_CONTROL1);
    // We verify whether Power Switching is enabled or not
    if(tmp&(~MPQ_CONTROL1_ENPWR_MASK)==MPQ_CONTROL1_ENPWR_EN){
        // If it is enabled, we disable it by setting ENPWR bit to 0
        I2C_WriteRegByte(MPQ4210_ADDR1, MPQREG_CONTROL1, (tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_DIS);
    }
    // First, we set the new Vref value through the VrefH and VrefL
    // registers
    uint8_t refLSB,refMSB;
    // First three bits from the Vref parameter are the new ref LSB
    refLSB = (uint8_t)(Vref&MPQ_REF_LSB_MASK);
    // Bits 10:3 from the Vref parameter are the new ref MSB, and they
    // are shifted three times to the right to fill an eight bit register 
    refMSB = (uint8_t)((Vref&MPQ_REF_MSB_MASK)>>3);
    // Now we fill the I2C register which correspond to the REFLSB and REFMSB
    I2C_WriteRegByte(MPQ4210_ADDR1, MPQREG_REF_LSB, refLSB);
    I2C_WriteRegByte(MPQ4210_ADDR1, MPQREG_REF_MSB, refMSB);
    
    // Now that we have set the Vref registers, we have to turn down the power
    // switching and enable de GO_BIT for the new reference to be set
    tmp = I2C_ReadRegByte(MPQ4210_ADDR1,MPQREG_CONTROL1);
    I2C_WriteRegByte(MPQ4210_ADDR1,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_GO_BIT_MASK)|MPQ_CONTROL1_GO_BIT_SET);

    // 200 ms after Vref has started to change, we enable power switching
    SoftwareDelay(200);
    tmp = I2C_ReadRegByte(MPQ4210_ADDR1,MPQREG_CONTROL1);
    I2C_WriteRegByte(MPQ4210_ADDR1, MPQREG_CONTROL1, (tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_EN);
    // After this, Vref configuration has been completed
}

// Must use when MPQ4210's address is 0x66
void MPQ_SetVoltageReference2(uint16_t Vref){
    // At first we make sure ENPWR is set to 0
    // Now that we have set the Vref registers, we have to turn down the power
    // switching and enable de GO_BIT for the new reference to be set
    uint8_t tmp = I2C_ReadRegByte(MPQ4210_ADDR2,MPQREG_CONTROL1);
    // We verify whether Power Switching is enabled or not
    if(tmp&(~MPQ_CONTROL1_ENPWR_MASK)==MPQ_CONTROL1_ENPWR_EN){
        // If it is enabled, we disable it by setting ENPWR bit to 0
        I2C_WriteRegByte(MPQ4210_ADDR2, MPQREG_CONTROL1, (tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_DIS);
    }
    // First, we set the new Vref value through the VrefH and VrefL
    // registers
    uint8_t refLSB,refMSB;
    // First three bits from the Vref parameter are the new ref LSB
    refLSB = (uint8_t)(Vref&MPQ_REF_LSB_MASK);
    // Bits 10:3 from the Vref parameter are the new ref MSB, and they
    // are shifted three times to the right to fill an eight bit register 
    refMSB = (uint8_t)((Vref&MPQ_REF_MSB_MASK)>>3);
    // Now we fill the I2C register which correspond to the REFLSB and REFMSB
    I2C_WriteRegByte(MPQ4210_ADDR2, MPQREG_REF_LSB, refLSB);
    I2C_WriteRegByte(MPQ4210_ADDR2, MPQREG_REF_MSB, refMSB);
    
    // Now that we have set the Vref registers, we have to turn down the power
    // switching and enable de GO_BIT for the new reference to be set
    tmp = I2C_ReadRegByte(MPQ4210_ADDR2,MPQREG_CONTROL1);
    I2C_WriteRegByte(MPQ4210_ADDR2,MPQREG_CONTROL1,(tmp&MPQ_CONTROL1_GO_BIT_MASK)|MPQ_CONTROL1_GO_BIT_SET);

    // 200 ms after Vref has started to change, we enable power switching
    SoftwareDelay(200);
    tmp = I2C_ReadRegByte(MPQ4210_ADDR2,MPQREG_CONTROL1);
    I2C_WriteRegByte(MPQ4210_ADDR2, MPQREG_CONTROL1, (tmp&MPQ_CONTROL1_ENPWR_MASK)|MPQ_CONTROL1_ENPWR_EN);
    // After this, Vref configuration has been completed
}

/******************************************
* @ brief Configuration of average current limit through ILIM reg
* @ param ILIMthreshold uint8_t containing the threshold to be set
*       from the following selection
*       - MPQ_ILIM_27_9mV
*       - MPQ_ILIM_33_3mV
*       - MPQ_ILIM_39_3mV
*       - MPQ_ILIM_45_1mV
*       - MPQ_ILIM_51_2mV
*       - MPQ_ILIM_56_8mV
*       - MPQ_ILIM_62_8mV
*       - MPQ_ILIM_68_7mV
* @ note you set a new current limit threshold given the voltage measured
*       between the IAVGP and IAVGN pins which means the actual average current
*       limit is given by:
*       IAVG Limit = Threshold(mV)/Rsense
*******************************************/
// Must use when MPQ4210's address is 0x64
void MPQ_setILIM1(uint8_t ILIMthreshold){
    // We set the ILIM register to the new value set
    I2C_WriteRegByte(MPQ4210_ADDR2,MPQREG_ILIM,ILIMthreshold);
}
// Must use when MPQ4210's address is 0x66
void MPQ_setILIM2(uint8_t ILIMthreshold){
    // We set the ILIM register to the new value set
    I2C_WriteRegByte(MPQ4210_ADDR2,MPQREG_ILIM,ILIMthreshold);
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
void MPQ_SetSwitchingFrequency1(uint8_t Fsw){
    // We read the full control2 register in order to be able to modify
    // the FSW bits without modifying any other register
    uint8_t tmp = I2C_ReadRegByte(MPQ4210_ADDR1,MPQREG_CONTROL2);
    // We modify only de FSW bits and set them to the new Fsw value
    I2C_WriteRegByte(MPQ4210_ADDR1,MPQREG_CONTROL2,(tmp&MPQ_CONTROL2_FSW_MASK)|Fsw);
}
// Must use when MPQ4210's address is 0x66
void MPQ_SetSwitchingFrequency2(uint8_t Fsw){
    // We read the full control2 register in order to be able to modify
    // the FSW bits without modifying any other register
    uint8_t tmp = I2C_ReadRegByte(MPQ4210_ADDR2,MPQREG_CONTROL2);
    // We modify only de FSW bits and set them to the new Fsw value
    I2C_WriteRegByte(MPQ4210_ADDR2,MPQREG_CONTROL2,(tmp&MPQ_CONTROL2_FSW_MASK)|Fsw);
}