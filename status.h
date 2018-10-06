// status payload operations
#define STATUS_PLD_OP_READ 3

// status numbers
#define STATUS_CURR_TEMP 0
#define STATUS_CURR_TANK_LEVEL 1



typedef union {
    __pack struct {
        uint8_t operation;
        union { //second byte
            uint8_t read_setting_num;
        };
        union { // thrid and fourth bytes
            uint16_t status_value;
        };
    };
    uint8_t arr[4];
        

}STATUS_payload_t;
