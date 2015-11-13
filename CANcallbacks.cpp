
#include <CANcallbacks.h>

CANcallbacks::CANcallbacks(FlexCAN *_CANbus){
    //return mcp2515_init(CANSPEED_1000);
    CANbus = _CANbus;
    n_callbacks = 0;
}

bool CANcallbacks::transmit (CAN_message_t &message){
    //mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
    //if (mcp2515_send_message(message)) {
    //	return true;
	//}
	//return false;
	CANbus->write(message);
	return true;
}

bool CANcallbacks::receive (CAN_message_t &message){
	
	if (CANbus->available()) 
    {
        if (CANbus->read(message)) 
        {
        	//distribute messages here.
        	for(int i=0; i<n_callbacks; i++){
        		if(message.id == callbackID[i]){
        			(*callback[i])(message);
        		}
        	}

        	return true;
        }
    }
    return false;
}

bool CANcallbacks::set_callback(uint16_t messageID, bool (*new_callback)(CAN_message_t &message)) {
	if(n_callbacks < MAX_CAN_CALLBACKS){
		callbackID[n_callbacks] = messageID;
		(callback[n_callbacks])= new_callback;
		n_callbacks++;
		return true;
	}
	return false;

}