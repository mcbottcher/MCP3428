/*

Module for communicating with MCP3428 over I2C
with the RaspberryPi

See MCP3428.cpp for licence

*/

#define I2C_BUS "/dev/i2c-1"

#define CONFIG_INIT_CONVERSION 1U
#define CONFIG_CONVERSION_NO_EFFECT 0U

#define CONFIG_CHN1 0U
#define CONFIG_CHN2 1U
#define CONFIG_CHN3 2U
#define CONFIG_CHN4 3U

#define CONFIG_CONTINUOUS_CONVERSION_MODE 1U 
#define CONFIG_ONESHOT_CONVERSION_MODE		0U
hi
#define CONFIG_12BIT_240SPS 0U
#define CONFIG_14BIT_60SPS	1U
#define CONFIG_16BIT_15SPS	2U

#define CONFIG_GAIN_1X 0U
#define CONFIG_GAIN_2X 1U
#define CONFIG_GAIN_4X 2U
#define CONFIG_GAIN_8X 3U

class MCP3428{

	private:
	
		int _fd;
		int _PGAgain;
		struct _configReg;
		uint8_t _data;
		
		void _writeConfig();
		void _setChannel(uint8_t channel);
	
	public:
			
		MCP3428(uint8_t i2c_address);
		~MCP3428();
		
		void setConfig(uint8_t RDYflag,
									 uint8_t channel,
									 uint8_t conversion_mode,
									 uint8_t resolution,
									 uint8_t PGA);
	
		void readConfig();
		
		
		int16_t readChannel(uint8_t channel);
		double readChannelScaled(uint8_t channel);

};
