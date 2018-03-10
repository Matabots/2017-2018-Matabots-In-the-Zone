#ifndef I2C_H
#define I2C_H

// 7-bit address of the slave I2C device, right aligned
#define I2C_SLAVE_ADDR         0x4A
// Ficitonal "enable" register for the device
#define I2C_SLAVE_REG_ENABLE   0x38
// Fictional 32-bit "parameters" buffer for the device, 0x6D-0x6F
#define I2C_SLAVE_BUF_PARAMS   0x6D

// 7-bit address of the slave I2C device, right aligned
#define I2C_SLAVE_ADDR       0x4A
// Fictional 32-bit data buffer for the device, 0x30-0x34
#define I2C_SLAVE_BUF_DATA   0x30
class i2c{
private:
  uint8_t data_in[4];
  int32_t reading;
public:
  i2c(){
    this->reading = -1;
  };
  void read(){
    if (i2cReadRegister(I2C_SLAVE_ADDR, I2C_SLAVE_BUF_DATA, this->data_in, 4)) {
            // Combine the 8-bit incoming values by extending them and bitwise-oring them together
            //
            // NOTE: Extension to 32-bits is done using uint32_t even though this->reading is int32_t
            //       This is done to prevent "sign extension," a common problem in these scenarios
            //
            // NOTE: This implementation assumes incoming data is big-endian with the order (0, 1, 2, 3)
            //       If your I2C slave emits data as little-endian, the order needs to be reversed
            this->reading = (((uint32_t) this->data_in[0]) << 24) |
                      (((uint32_t) this->data_in[1]) << 16) |
                      (((uint32_t) this->data_in[2]) <<  8) |
                      (((uint32_t) this->data_in[3]));

            // printf("Read in a value of %ld from slave.\n", this->reading);
        }
        else {
            this->reading = -1;
            // printf("ERROR: Failed to read sensor data from slave!\n");
        }
  }

  uint8_t* getData(){
    return this->data_in;

  };
};
#endif
