#include "MPQ4210.h"
#include <pigpio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define I2C_BUS 3
#define SLAVE_ADDRESS 0x50
#define POLL_DELAY 100 // Microseconds
#define POLL_RETRIES 100

// Function to poll for device readiness
int pollForDevice(uint8_t SlaveAddress) {
    int handle;
    for (int i = 0; i < POLL_RETRIES; ++i) {
        handle = i2cOpen(I2C_BUS, SlaveAddress, 0);
        if (handle >= 0) {
            int status = i2cWriteQuick(handle, 0); // Send a quick write operation
            i2cClose(handle);
            if (status == 0) {
                //printf("Number of iterations needed for device to be ready: %d\n",i);
                return 0; // Device is ready
            }
        }
        usleep(POLL_DELAY);
    }
    return -1; // Device is not ready after maximum retries
}

// We define the writing function
void I2C_WriteRegByte(uint8_t SlaveAddress, uint8_t RegAddress, uint8_t ByteData){
    if (pollForDevice(SlaveAddress) != 0) {
        fprintf(stderr, "Device at address 0x%02X is not ready\n", SlaveAddress);
        return;
    }

    // We open the I2C handle for the reading operation
    int handle = i2cOpen(I2C_BUS,SlaveAddress,0);
    // If we fail to open handle we raise error
    if (handle < 0) {
        fprintf(stderr, "Failed to open I2C device at address 0x%02X\n", SlaveAddress);
        return;
    }

    // We prepare the data buffer
    char buff[2];
    buff[0] = RegAddress;
    buff[1] = ByteData;

    // We write the device on said address the given data
    int status = i2cWriteDevice(handle,buff,2);
    // Close the I2C device
    i2cClose(handle);

    // We check whether or not the writing operation was successfull or not
    if (status < 0) {
        fprintf(stderr, "Failed to write to I2C device at address 0x%02X\n", SlaveAddress);
    }
}

// We define the reading function
uint8_t I2C_ReadRegByte(uint8_t SlaveAddress, uint8_t RegAddress){
    if (pollForDevice(SlaveAddress) != 0) {
        fprintf(stderr, "Device at address 0x%02X is not ready\n", SlaveAddress);
        return 0;
    }
    // We open the I2C handle for the reading operation
    int handle = i2cOpen(I2C_BUS,SlaveAddress,0);
    // If we fail to open handle we raise error
    if (handle < 0) {
        fprintf(stderr, "Failed to open I2C device at address 0x%02X\n", SlaveAddress);
        return 0;
    }
    // Read data byte from device's register
    int status = i2cReadByteData(handle,RegAddress);
    // Close the I2C device
    i2cClose(handle);

    // If the read operation failed, print error message and return 0
    if (status < 0) {
        fprintf(stderr, "Failed to read from register 0x%02X of I2C device at address 0x%02X\n", RegAddress, SlaveAddress);
        return 0; // Return 0 to indicate failure
    }
    // Return the retrieved value
    return (uint8_t)status;
}

void SoftwareDelay(uint8_t ms){
    usleep(ms*1000);
}

int main(){
    // Initialize the pigpio library
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio initialization failed\n");
        return 1;
    }
    // Loading of the tested register on the I2C EEPROM
    printf("Now loading the default configuration of the VREF and ILIM registers\n");
    I2C_WriteRegByte(SLAVE_ADDRESS,MPQREG_REF_LSB,0b100);
    I2C_WriteRegByte(SLAVE_ADDRESS,MPQREG_REF_MSB,0b111110);
    I2C_WriteRegByte(SLAVE_ADDRESS,MPQREG_ILIM,0b001);
    // Verification of what has been written on the eeprom
    printf("Now reading the loaded configuration\n\n");
    uint8_t RegAddress = MPQREG_REF_LSB;
    uint8_t rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    printf("Read 0x%X from register 0x%X\n", rcvd, RegAddress);
    RegAddress = MPQREG_REF_MSB;
    rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    printf("Read 0x%X from register 0x%X\n", rcvd, RegAddress);
    RegAddress = MPQREG_ILIM;
    rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    printf("Read 0x%X from register 0x%X\n\n", rcvd, RegAddress);

    // Test of the library functions which change VREF and ILIM
    // Setting voltage to 1.1 V
    // Values to be set should go as following
    // REF_LSB = 100
    // REF_MSB = 10001001
    printf("Setting voltage reference to 1.1V, VOUT should be 11V\n");
    MPQ_SetVoltageReference1(1100);

    // Setting ILIM threshold to 45.1mV
    // Value of the ILIM register should be set as follows
    // ILIM = 011
    // printf("Setting ILIM threshold to 45.1mV\n\n");
    // MPQ_setILIM1(MPQ_ILIM_45_1mV);

    // // Verification of what has been written
    // // Verification of what has been written on the eeprom
    // printf("Now reading the loaded configuration\n\n");
    // RegAddress = MPQREG_REF_LSB;
    // rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    // printf("Read 0x%X from register 0x%X\n", rcvd, RegAddress);
    // RegAddress = MPQREG_REF_MSB;
    // rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    // printf("Read 0x%X from register 0x%X\n", rcvd, RegAddress);
    // RegAddress = MPQREG_ILIM;
    // rcvd = I2C_ReadRegByte(SLAVE_ADDRESS,RegAddress);
    // printf("Read 0x%X from register 0x%X\n\n", rcvd, RegAddress);

    // // Continue with the rest of your main function

    gpioTerminate();
    return 0;
}