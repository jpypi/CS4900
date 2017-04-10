// -*- C++ -*-
// *******************************************************************
//
// (c) Copyright 2006, Object Computing, Inc.
// All Rights Reserved.
//
// *******************************************************************

#include "telemetryTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/PublisherImpl.h>
#include <ace/streams.h>
#include <ace/OS_NS_unistd.h>
#include <orbsvcs/Time_Utilities.h>

#include "dds/DCPS/StaticIncludes.h"

// constants for Stock Quoter domain Id, types, and topic
DDS::DomainId_t SENDER_DOMAIN_ID = 1066;
const char* SENDER_TELEMETRY_TYPE = "Telemetry Type";
const char* SENDER_TELEMETRY_TOPIC = "Telemetries";


TimeBase::TimeT get_timestamp() {
  TimeBase::TimeT retval;
  ACE_hrtime_t t = ACE_OS::gethrtime ();
  ORBSVCS_Time::hrtime_to_TimeT (retval, t );
  return retval;
}

int ACE_TMAIN (int argc, ACE_TCHAR *argv[]) {

  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try {
    // Initialize, and create a DomainParticipant

    dpf = TheParticipantFactoryWithArgs(argc, argv);

    participant = dpf->create_participant(
      SENDER_DOMAIN_ID,
      PARTICIPANT_QOS_DEFAULT,
      DDS::DomainParticipantListener::_nil(),
      ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (CORBA::is_nil (participant.in ())) {
      cerr << "create_participant failed." << endl;
      ACE_OS::exit(1);
    }

    // Create a publisher for the two topics
    // (PUBLISHER_QOS_DEFAULT is defined in Marked_Default_Qos.h)
    DDS::Publisher_var pub =
      participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                    DDS::PublisherListener::_nil(),
                                    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil (pub.in ())) {
      cerr << "create_publisher failed." << endl;
      ACE_OS::exit(1);
    }

    // Register the Quote type
    telemetryM::telemetryMessageTypeSupport_var telemetryMessage_servant
      = new telemetryM::telemetryMessageTypeSupportImpl();
    if (DDS::RETCODE_OK != telemetryMessage_servant->register_type(participant.in (),
                                                        SENDER_TELEMETRY_TYPE)) {
      cerr << "register_type for " << SENDER_TELEMETRY_TYPE << " failed." << endl;
      ACE_OS::exit(1);
    }

    // Get QoS to use for our two topics
    // Could also use TOPIC_QOS_DEFAULT instead
    DDS::TopicQos default_topic_qos;
    participant->get_default_topic_qos(default_topic_qos);

    // Create a topic for the Quote type...
    DDS::Topic_var telemetryMessage_topic =
      participant->create_topic (SENDER_TELEMETRY_TOPIC,
                                 SENDER_TELEMETRY_TYPE,
                                 default_topic_qos,
                                 DDS::TopicListener::_nil(),
                                 ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil (telemetryMessage_topic.in ())) {
      cerr << "create_topic for " << SENDER_TELEMETRY_TOPIC << " failed." << endl;
      ACE_OS::exit(1);
    }

    // Get the default QoS for our Data Writers
    // Could also use DATAWRITER_QOS_DEFAULT
    DDS::DataWriterQos dw_default_qos;
    pub->get_default_datawriter_qos (dw_default_qos);

    // Create a DataWriter for the Quote topic
    DDS::DataWriter_var telemetryMessage_base_dw =
      pub->create_datawriter(telemetryMessage_topic.in (),
                             dw_default_qos,
                             DDS::DataWriterListener::_nil(),
                             ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil (telemetryMessage_base_dw.in ())) {
      cerr << "create_datawriter for " << SENDER_TELEMETRY_TOPIC << " failed." << endl;
      ACE_OS::exit(1);
    }
    telemetryM::telemetryMessageDataWriter_var telemetryMessage_dw
      = telemetryM::telemetryMessageDataWriter::_narrow(telemetryMessage_base_dw.in());
    if (CORBA::is_nil (telemetryMessage_dw.in ())) {
      cerr << "telemetryMessageDataWriter could not be narrowed"<< endl;
      ACE_OS::exit(1);
    }

    // Register the Exchange Event and the two Quoted securities (SPY and MDY)
    /*StockQuoter::ExchangeEvent ex_evt;
    ex_evt.exchange = STOCK_EXCHANGE_NAME;
    DDS::InstanceHandle_t exchange_handle = exchange_evt_dw->register_instance(ex_evt);
	*/
    telemetryM::telemetryMessage spy;
    //spy.ticker = CORBA::string_dup("SPY");
    DDS::InstanceHandle_t spy_handle = telemetryMessage_dw->register_instance(spy);
	/*
    StockQuoter::Quote mdy;
    mdy.ticker = CORBA::string_dup("MDY");
    DDS::InstanceHandle_t mdy_handle = quote_dw->register_instance(mdy);*/

    // Publish...

    /*pc::ExchangeEvent opened;
    opened.exchange = STOCK_EXCHANGE_NAME;
    opened.event = StockQuoter::TRADING_OPENED;
    opened.timestamp = get_timestamp();

    cout << "Publishing TRADING_OPENED" << endl;
    DDS::ReturnCode_t ret = exchange_evt_dw->write(opened, exchange_handle);
    if (ret != DDS::RETCODE_OK) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: OPEN write returned %d.\n"), ret));
    }*/
	DDS::ReturnCode_t ret;
    ACE_Time_Value quarterSecond( 0, 250000 );
    for ( int i = 0; i < 20; ++i ) {
      telemetryM::telemetryMessage msg;
	  msg.id = i;
	  msg.xacc = 1200.0 + 10.0*i;
	  msg.timestamp = get_timestamp();

      cout << "Publishing msg: " << msg.xacc << endl;
      ret = telemetryMessage_dw->write(msg, spy_handle);
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: SPY write returned %d.\n"), ret));
      }

      ACE_OS::sleep( quarterSecond );

      /*StockQuoter::Quote mdy_quote;
      mdy_quote.exchange = STOCK_EXCHANGE_NAME;
      mdy_quote.ticker = CORBA::string_dup("MDY");
      mdy_quote.full_name = CORBA::string_dup("S&P Midcap Depository Receipts");
      mdy_quote.value = 1400.0 + 10.0*i;
      mdy_quote.timestamp = get_timestamp();

      cout << "Publishing MDY Quote: " << mdy_quote.value <<endl;
      ret = quote_dw->write(mdy_quote, mdy_handle);
      if (ret != DDS::RETCODE_OK) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: MDY write returned %d.\n"), ret));
      }

      ACE_OS::sleep( quarterSecond );*/
    }

    /*StockQuoter::ExchangeEvent closed;
    closed.exchange = STOCK_EXCHANGE_NAME;
    closed.event = StockQuoter::TRADING_CLOSED;
    closed.timestamp = get_timestamp();

    cout << "Publishing TRADING_CLOSED" << endl;
    ret = exchange_evt_dw->write(closed, exchange_handle);
    if (ret != DDS::RETCODE_OK) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: CLOSED write returned %d.\n"), ret));
    }

    cout << "Exiting..." << endl;*/
  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in main.cpp:" << endl
         << e << endl;
    ACE_OS::exit(1);
  }

  // Cleanup
  try {
    if (!CORBA::is_nil (participant.in ())) {
      participant->delete_contained_entities();
    }
    if (!CORBA::is_nil (dpf.in ())) {
      dpf->delete_participant(participant.in ());
    }
  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in cleanup." << endl << e << endl;
    ACE_OS::exit(1);
  }
  TheServiceParticipant->shutdown();
  return 0;
}
