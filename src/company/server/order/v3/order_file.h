#ifndef __ORDER_FILE__
#define __ORDER_FILE__

//create file function
void COMM_CREATE_FILE( char *FILE_NAME );

//save the ip address
int COMM_SAVE_IPADDRESS( char * IP_ADDRESS );

//change the state
int COMM_FILE_STATE_EXCHANGE( char *EXCHANGE_IP );

#endif
