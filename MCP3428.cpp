/*

Adapted from https://github.com/ControlEverythingCommunity/MCP3428/tree/master/C for C++

Original Licence:

Distributed with a free-will license.
Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
MCP3428
This code is designed to work with the MCP3428_I2CADC I2C Mini Module available from ControlEverything.com.
https://www.controleverything.com/content/Analog-Digital-Converters?sku=MCP3428_I2CADC#tabs-0-product_tabset-2

*/

#include "MCP3428.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>



MCP3428::MCP3428(uint8_t i2c_address = 0x68){
	_slaveAddress = i2c_address;
}

MCP3428::~MCP3428(){
}


void MCP3428::setConfig(uint8_t RDYflag = CONFIG_CONVERSION_NO_EFFECT,
										uint8_t channel = CONFIG_CHN1,
										uint8_t conversion_mode = CONFIG_CONTINUOUS_CONVERSION_MODE,
										uint8_t resolution = CONFIG_12BIT_240SPS,
										uint8_t PGA = CONFIG_GAIN_1X){

	_configReg.RDY_bar = RDYflag;
	_configReg.channel_select = channel;
	_configReg.conversion_mode = conversion_mode;
	_configReg.resolution = resolution;
	_configReg.gain = PGA;

	_writeConfig();

}

void MCP3428::_setChannel(uint8_t channel_number){
	_configReg.channel_select = channel_number;
	_writeConfig();
	
}

void MCP3428::_writeConfig(){
	i2c.write_std(_slaveAddress, (uint8_t*)(&_configReg), 1);
	usleep(5000); //need this since new sample after 1/240 s
}


void MCP3428::readConfig(){

}

int16_t MCP3428::readChannel(uint8_t channel_number){
	
	_setChannel(channel_number);
	
	uint8_t reg[1] = {0x00};
	i2c.write_std(_slaveAddress, reg, 1);	

	i2c.read_std(_slaveAddress, _data, 2);

	uint16_t tmp_hold = ((_data[0]&0x0f) * 256 + _data[1]);
	return *((int16_t*)(&tmp_hold));

}

double MCP3428::readChannelScaled(uint8_t channel_number){

	//int16_t digital_value = readChannel(uint8_t channel);
	//#TODO need to fix ** to pow()
	//return ((digital_value/(2**(12+(2 * _configReg.resolution)))) / (2**_configReg.gain))*2.048;
	return 2.0;

}


