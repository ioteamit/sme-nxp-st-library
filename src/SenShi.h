/*
 * cc12541.h
 *
 * Created: 01/01/2016 22:14:39
 *  Author: development
 */


#ifndef _SEN_SHI_H_
#define _SEN_SHI_H_


class SenShi {
    
    
public:
    SenShi(void);
    virtual ~SenShi(){};

private:	

byte readRegister(byte _address, byte regToRead);

// Writes a single byte (dataToWrite) into regToWrite
bool writeRegister(byte _address, byte regToWrite, byte dataToWrite);

  
// library API
public:
    void begin(void);
    void ledRedLight(uint32_t value);
    void ledGreenLight(uint32_t value);
    void ledYellowLight(uint32_t value);
};


extern SenShi  senShi;

#endif /* CC2541_H_ */
