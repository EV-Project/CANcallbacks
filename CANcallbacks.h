#ifndef CANCALLBACKS_H
#define CANCALLBACKS_H
#include <inttypes.h>
#include <Arduino.h> // Arduino 1.0
#include <FlexCAN.h>

#define MAX_CAN_CALLBACKS 8



class CANcallbacks{
	public:
        CANcallbacks(FlexCAN *_CANbus);
		//char init();
		bool transmit (CAN_message_t &message);
        bool receive (CAN_message_t &message);
        bool set_callback(uint16_t messageID, bool (*new_callback)(CAN_message_t &message));
    private:
        int n_callbacks;
        FlexCAN *CANbus;
		uint16_t callbackID[MAX_CAN_CALLBACKS];
		bool (*callback[MAX_CAN_CALLBACKS])(CAN_message_t &message);

};

#endif