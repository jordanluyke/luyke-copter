#include "ADXL345.h"
#include "Arduino.h"
#include "Wire.h"
#include "I2C.h"

ADXL345::ADXL345() 
{
	deviceAddress = 0x53;
}

void ADXL345::SetupADXL345()
{
	byte dataFormat = 0x31;
	byte powerCTL = 0x2D; //Power Control Register
	i2c.WriteRegister(deviceAddress, 0x31, 0x01); //Put the ADXL345 into +/- 4G range by writing the value 0x01 to the DATA_FORMAT register.
	i2c.WriteRegister(deviceAddress, 0x2D, 0x08); //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
}

void ADXL345::UpdateAccelValues()
{
	byte xLSB = i2c.ReadRegister(deviceAddress, 0x32);
	byte xMSB = i2c.ReadRegister(deviceAddress, 0x33);
	x = ((xMSB << 8) | xLSB);

	byte yLSB = i2c.ReadRegister(deviceAddress, 0x34);
	byte yMSB = i2c.ReadRegister(deviceAddress, 0x35);
	y = ((yMSB << 8) | yLSB);
	
	byte zLSB = i2c.ReadRegister(deviceAddress, 0x36);
	byte zMSB = i2c.ReadRegister(deviceAddress, 0x37);
	z = ((zMSB << 8) | zLSB);
}

// http://www.analog.com/static/imported-files/data_sheets/ADXL345.pdf