/* HEADERS */
#include "FaceMessage_TS.hpp"
#include "ace/Log_Msg.h"

#ifdef ACE_AS_STATIC_LIBS
# include "dds/DCPS/RTPS/RtpsDiscovery.h"
# include "dds/DCPS/transport/rtps_udp/RtpsUdp.h"
#endif
/* -HEADERS- */

/* SETUP */
// Initialize the TS interface
FACE::RETURN_CODE_TYPE status;
FACE::TS::Initialize("face_config.ini", status);

if (status != FACE::RC_NO_ERROR) {
	return static_cast<int>(status);
}

// Create the sub connection (TELEMETRY)
FACE::CONNECTION_ID_TYPE connIdS;
FACE::CONNECTION_DIRECTION_TYPE dirS;
FACE::MESSAGE_SIZE_TYPE max_msg_sizeS;
FACE::TS::Create_Connection(
	"subTelemetry", FACE::PUB_SUB, connIdS, dirS,
	max_msg_sizeS, FACE::INF_TIME_VALUE, status);

if (status != FACE::RC_NO_ERROR) {
	return static_cast<int>(status);
}

// Create the pub connection (COMMANDS)
FACE::CONNECTION_ID_TYPE connIdP;
FACE::CONNECTION_DIRECTION_TYPE dirP;
FACE::MESSAGE_SIZE_TYPE max_msg_sizeP;
FACE::TS::Create_Connection(
	"pubCommands", FACE::PUB_SUB, connIdP, dirP,
	max_msg_sizeP, FACE::INF_TIME_VALUE, status);

if (status != FACE::RC_NO_ERROR) {
	return static_cast<int>(status);
}
/* -SETUP- */

/* RECEIVE */
// Receive a message
void
receive_dds(FACE::CONNECTION_ID_TYPE connIdS, FACE::MESSAGE_SIZE_TYPE max_msg_sizeS)
{
	const FACE::TIMEOUT_TYPE timeout = FACE::INF_TIME_VALUE;
	FACE::RETURN_CODE_TYPE status;
	FACE::TRANSACTION_ID_TYPE txn;
	TMessenger::TMessage msg;

	ACE_DEBUG((
		LM_INFO, "Subscriber: about to Receive_Message()\n"));

	FACE::TS::Receive_Message(
		connIdS, timeout, txn, msg, max_msg_sizeS, status);

	if (status != FACE::RC_NO_ERROR) {
		return static_cast<int>(status);
	}

	// Output the message
	/*
	 = msg.subject_id;
	 = msg.count;
	// = msg.time_usec;
	 = msg.xacc;
	 = msg.yacc;
	 = msg.zacc;
	 = msg.xgyro;
	 = msg.ygyro;
	 = msg.zgyro;
	 = msg.xmag;
	 = msg.ymag;
	 = msg.zmag;
	 = msg.pressure_alt;
	 = msg.temperature;
	 */
}
/* -RECEIVE- */

/* SEND */
void
send_dds(FACE::CONNECTION_ID_TYPE connIdP, FACE::MESSAGE_SIZE_TYPE max_msg_sizeP)
{
	// Message to send
	CMessenger::CMessage msg;
	msg.subject_id = 15;
	/*msg.whatever = whatever*/
	/*etc.. */


	// Send message
	FACE::TRANSACTION_ID_TYPE txn;
	ACE_DEBUG((LM_INFO, "Publisher: about to Send_Message()\n"));
	FACE::TS::Send_Message(
		connIdP, FACE::INF_TIME_VALUE, txn, msg,
		max_msg_sizeP, status);
	if (status != FACE::RC_NO_ERROR) {
		exit(static_cast<int>(status));
	}
}
/* -SEND- */

/* TEARDOWN */
// Destroy the sub connection
FACE::TS::Destroy_Connection(connId, status);

if (status != FACE::RC_NO_ERROR) {
	return static_cast<int>(status);
}
/* -TEARDOWN- */
