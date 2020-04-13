/*

Module for communicating with MCP3428 over I2C
with the RaspberryPi

See MCP3428.cpp for licence

*/

#include <stdint.h>
#include "I2Cdev/I2Cdev.h"

/**
* Define which dev I2C bus to use
*/
#define I2C_BUS "/dev/i2c-1"

//TODO change these to enums... so its more obvious which config corresponds to what...
 
#define CONFIG_INIT_CONVERSION 1U
#define CONFIG_CONVERSION_NO_EFFECT 0U

#define CONFIG_CHN1 0U
#define CONFIG_CHN2 1U
#define CONFIG_CHN3 2U
#define CONFIG_CHN4 3U

#define CONFIG_CONTINUOUS_CONVERSION_MODE 1U 
#define CONFIG_ONESHOT_CONVERSION_MODE		0U

#define CONFIG_12BIT_240SPS 0U
#define CONFIG_14BIT_60SPS	1U
#define CONFIG_16BIT_15SPS	2U

#define CONFIG_GAIN_1X 0U
#define CONFIG_GAIN_2X 1U
#define CONFIG_GAIN_4X 2U
#define CONFIG_GAIN_8X 3U


/** A class to communicate with the MCP3428 ADC.
*/
class MCP3428{

	private:
	    
	    /** Holds the I2C address of the ADC */
		uint8_t _slaveAddress;
		int _PGAgain;
		I2Cdev i2c;

        /** Structure representing the configuration byte */
		struct configRegStruct{
			uint8_t gain : 2;			
			uint8_t resolution : 2;
			uint8_t conversion_mode : 1;
			uint8_t channel_select : 2;
			uint8_t RDY_bar : 1;
		}__attribute__((__packed__));

		uint8_t _data[2];
		configRegStruct _configReg;
		
		void _writeConfig();
		void _setChannel(uint8_t channel_number);
	
	public:
		
		/** Class constructor
		* @param i2c_address is the I2C address of the ADC represented by the object
		*/	
		MCP3428(uint8_t i2c_address);
		~MCP3428();
		
		/** Function to set the configuration of the ADC and write it to the ADC.
		* For parameter values and info please see the MCP3428 datasheet
		*/
		void setConfig(uint8_t RDYflag,
					   uint8_t channel,
					   uint8_t conversion_mode,
					   uint8_t resolution,
					   uint8_t PGA);
	
	    /** 
	    * Not yet implemented
	    */
		void readConfig();
		
		/** 
		* Function to read the value from a channel on the ADC. The channel
		* is set using setConfig() in this function to read from the correct channel
		*
		* @param channel_number is the channel number to read from.
		*/
		int16_t readChannel(uint8_t channel_number);
		
		/** 
		* Not yet implemented
		*/
		double readChannelScaled(uint8_t channel_numer);

};
