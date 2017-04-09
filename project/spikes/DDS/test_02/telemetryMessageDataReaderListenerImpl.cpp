// -*- C++ -*-
// *******************************************************************
//
// (c) Copyright 2006, Object Computing, Inc.
// All Rights Reserved.
//
// *******************************************************************

#include "telemetryMessageDataReaderListenerImpl.h"
#include "telemetryTypeSupportC.h"
#include "telemetryTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>


telemetryMessageDataReaderListenerImpl::telemetryMessageDataReaderListenerImpl()
{
}

telemetryMessageDataReaderListenerImpl::~telemetryMessageDataReaderListenerImpl ()
{
}

void telemetryMessageDataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
  try {
    telemetryM::telemetryMessageDataReader_var telemetryMessage_dr
      = telemetryM::telemetryMessageDataReader::_narrow(reader);
    if (CORBA::is_nil (telemetryMessage_dr.in ())) {
      cerr << "telemetryMessageDataReaderListenerImpl::on_data_available: _narrow failed." << endl;
      ACE_OS::exit(1);
    }

    int count = 0;
    while(true) {
      telemetryM::telemetryMessage msg;
      DDS::SampleInfo si ;
      DDS::ReturnCode_t status = telemetryMessage_dr->take_next_sample(msg, si) ;

      if (status == DDS::RETCODE_OK && si.valid_data) {
        ++count;
        cout << "msg:   id        = " << msg.id	      << endl
             << "       value     = " << msg.xacc           << endl
             << "       timestamp = " << msg.timestamp      << endl;
        cout << "SampleInfo.sample_rank        = " << si.sample_rank << endl;
        cout << "SampleInfo.instance_handle    = " << hex << si.instance_handle << endl;
        cout << "SampleInfo.publication_handle = " << hex << si.publication_handle << endl;
      } else if (status == DDS::RETCODE_NO_DATA) {
        cerr << "INFO: reading complete after " << count << " samples." << endl;
        break;
      } else {
        cerr << "ERROR: read msg: Error: " <<  status << endl;
      }
    }

  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in read:" << endl << e << endl;
    ACE_OS::exit(1);
  }
}

void telemetryMessageDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr,
    const DDS::RequestedDeadlineMissedStatus &)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_requested_deadline_missed" << endl;
}

void telemetryMessageDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr,
    const DDS::RequestedIncompatibleQosStatus &)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_requested_incompatible_qos" << endl;
}

void telemetryMessageDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr,
    const DDS::LivelinessChangedStatus &)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_liveliness_changed" << endl;
}

void telemetryMessageDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr,
    const DDS::SubscriptionMatchedStatus &)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_subscription_matched" << endl;
}

void telemetryMessageDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr,
    const DDS::SampleRejectedStatus&)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_sample_rejected" << endl;
}

void telemetryMessageDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr,
  const DDS::SampleLostStatus&)
{
  cerr << "telemetryMessageDataReaderListenerImpl::on_sample_lost" << endl;
}
