// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  Nigeru.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "Nigeru.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const nigeru_spec[] =
#else
static const char* nigeru_spec[] =
#endif
  {
    "implementation_id", "Nigeru",
    "type_name",         "Nigeru",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.velocity_by_count", "-0.01",
    "conf.default.dead_band", "10",
    "conf.default.debug", "0",
    "conf.default.rotation_vel_by_count", "-0.01",
    // Widget
    "conf.__widget__.velocity_by_count", "text",
    "conf.__widget__.dead_band", "text",
    "conf.__widget__.debug", "text",
    "conf.__widget__.rotation_vel_by_count", "text",
    // Constraints
    ""

  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Nigeru::Nigeru(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Nigeru::~Nigeru()
{
}



RTC::ReturnCode_t Nigeru::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // 
  bindParameter("velocity_by_count", m_velocity_by_count, "-0.0001");
  bindParameter("dead_band", m_dead_band, "200");
  bindParameter("debug", m_debug, "0");
  bindParameter("rotation_vel_by_count", m_roation_vel_by_count, "-0.1");
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Nigeru::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t Nigeru::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Nigeru::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t Nigeru::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Nigeru::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Nigeru::onExecute(RTC::UniqueId /*ec_id*/)
{
    if (m_inIn.isNew()) {
        m_inIn.read();
        if (m_in.data == 0) {  //前進
            m_out.data.vx = 0.5;
            m_out.data.va = 0;
        }
        else if (m_in.data == 1){  //右回転
            m_out.data.vx = 0;
            m_out.data.va = -1.0;
        }
        else if (m_in.data == 2) {  //左回転
            m_out.data.vx = 0;
            m_out.data.va = 1.0;
        }
        else {
            m_out.data.vx = 0;
            m_out.data.va = 0;
        }
        m_out.data.vy = 0;
        m_outOut.write();
    }
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t Nigeru::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Nigeru::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Nigeru::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Nigeru::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t Nigeru::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}



extern "C"
{
 
  void NigeruInit(RTC::Manager* manager)
  {
    coil::Properties profile(nigeru_spec);
    manager->registerFactory(profile,
                             RTC::Create<Nigeru>,
                             RTC::Delete<Nigeru>);
  }
  
}
