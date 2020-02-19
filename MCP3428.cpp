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
	
	char *bus = I2C_BUS;
	if((_fd = open(bus, O_RDWR)) < 0){
		std::cout << "Failed to open the bus" << std::endl;
	}

	ioctl(_fd, I2C_SLAVE, i2c_address);

}

MCP3428::~MCP3428(){
	
	close(_fd);	
}


struct MCP3428::_configReg{
	uint8_t RDY_bar : 1;
	uint8_t channel_select : 2;
	uint8_t conversion_mode : 1;
	uint8_t resolution : 2;
	uint8_t gain : 2;
};


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

void MCP3428::_setChannel(uint8_t channel){
	_configReg.channel_select = channel;
	_writeConfig();
	
}

void MCP3428::_writeConfig(){
	write(_fd, &_configReg, 1);
}


void MCP3428::readConfig(){

}

int16_t MCP3428::readChannel(uint8_t channel){
	
	_setChannel(channel);
	
	uint8_t reg[1] = {0x00};
	write(_fd, reg, 1);

	if(read(_fd, &_data, 2) != 2){
		printf("Error : Input/Output error \n");
	}

	uint16_t tmp_hold = ((_data[0]) * 256 + _data[1]);
	return *((int16_t*)(&tmp_hold));

}

double MCP3428::readChannelScaled(uint8_t channel){

	int16_t digital_value = readChannel(uint8_t channel);

	return ((digital_value/(2**(12+(2 * _configReg.resolution)))) / (2**_configReg.gain))*2.048;
}


