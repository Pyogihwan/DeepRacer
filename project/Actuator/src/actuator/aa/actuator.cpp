///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, Adaptive Application Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : actuator.cpp
/// SOFTWARE COMPONENT NAME           : Actuator
/// GENERATED DATE                    : 2024-11-14 15:25:13
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "actuator/aa/actuator.h"
 
namespace actuator
{
namespace aa
{
 
Actuator::Actuator()
    : m_logger(ara::log::CreateLogger("ACTR", "SWC", ara::log::LogLevel::kVerbose))
    , m_workers(1)
    , m_running(false)
{
}
 
Actuator::~Actuator()
{
    servoMgr->servoSubscriber(0, 0); 
}
 
bool Actuator::Initialize()
{
    m_logger.LogVerbose() << "Actuator::Initialize";
    
    bool init{true};
    
    m_ControlData = std::make_shared<actuator::aa::port::ControlData>();
    
    servoMgr = std::unique_ptr<PWM::ServoMgr>();
    m_logger.LogInfo() << "Actuator::servoMgr";
    ledMgr = std::unique_ptr<PWM::LedMgr>();
    m_logger.LogInfo() << "Actuator::ledMgr";
    

    {
        int cal_type = 0;
        int servo_min;
        int servo_mid;
        int servo_max;
        int servo_polarity;
        
        // Print current calibration value
        servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
        m_logger.LogInfo() << ("Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);

        // Set New calibration value
        servoMgr->setCalibrationValue(cal_type, servo_min - 10, servo_mid - 10, servo_max - 10, servo_polarity == 1 ? -1 : 1);
        
        // Print updated calibration value
        servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
        m_logger.LogInfo() << ("New Servo calibration value(-10): min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);

        // Recover calibration value
        servoMgr->setCalibrationValue(cal_type, servo_min + 10, servo_mid + 10, servo_max + 10, servo_polarity == 1 ? -1 : 1);

        // Print recovered calibration value
        servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
        m_logger.LogInfo() << ("Recovered Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);    

    }
    m_logger.LogInfo() << "Actuator::ServoCalibration";

    {
        int cal_type = 1;
        int motor_min;
        int motor_mid;
        int motor_max;
        int motor_polarity; 
        // Print current calibration value
        servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
        m_logger.LogInfo() << ("Current Motor calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);

        // Set New calibration value
        servoMgr->setCalibrationValue(cal_type, motor_min - 10, motor_mid - 10, motor_max - 10, motor_polarity == 1 ? -1 : 1);

        // Print updated calibration value
        servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
        m_logger.LogInfo() << ("New Servo calibration value(-10): min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);

        // Recover calibration value
        servoMgr->setCalibrationValue(cal_type, motor_min + 10, motor_mid + 10, motor_max + 10, motor_polarity == 1 ? -1 : 1);

        // Print recovered calibration value
        servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
        m_logger.LogInfo() << ("Recovered Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);
    }
    m_logger.LogInfo() << "Actuator::MotorCalibration";
    return init;
}
 
void Actuator::Start()
{
    m_logger.LogVerbose() << "Actuator::Start";
    
    m_ControlData->Start();
    
    // run software component
    Run();
}
 
void Actuator::Terminate()
{
    m_logger.LogVerbose() << "Actuator::Terminate";
    
    m_running = false;

    servoMgr->servoSubscriber(0, 0); 

    m_ControlData->Terminate();
}
 
void Actuator::Run()
{
    m_logger.LogVerbose() << "Actuator::Run";
    
    m_running = true;

    m_workers.Async([this] { TaskReceiveCEventCyclic(); });
    
    m_workers.Wait();
}

void Actuator::TaskReceiveCEventCyclic()
{
    m_ControlData->SetReceiveEventCEventHandler([this](const auto &sample)
    {
        OnReceiveCEvent(sample);
    });
    m_ControlData->ReceiveEventCEventCyclic();
}

void Actuator::OnReceiveCEvent(const deepracer::service::controldata::proxy::events::CEvent::SampleType &sample)
{
    m_logger.LogInfo() << "Actuator::OnReceiveCEvent - data = {" << sample[0] << ", " << sample[1] << "}";

    float cur_servo = sample[0];
    float cur_motor = sample[1];
    servoMgr->servoSubscriber(cur_motor, cur_servo);
}

void Actuator::ServoCalibration(int cal_type, int servo_min, int servo_mid, int servo_max, int servo_polarity)
{
    // Print current calibration value
    servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
    m_logger.LogInfo() << ("Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);

    // Set New calibration value
    servoMgr->setCalibrationValue(cal_type, servo_min - 10, servo_mid - 10, servo_max - 10, servo_polarity == 1 ? -1 : 1);
    
    // Print updated calibration value
    servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
    m_logger.LogInfo() << ("New Servo calibration value(-10): min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);

    // Recover calibration value
    servoMgr->setCalibrationValue(cal_type, servo_min + 10, servo_mid + 10, servo_max + 10, servo_polarity == 1 ? -1 : 1);

    // Print recovered calibration value
    servoMgr->getCalibrationValue(cal_type, &servo_min, &servo_mid, &servo_max, &servo_polarity);
    m_logger.LogInfo() << ("Recovered Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", servo_min, servo_mid, servo_max, servo_polarity);    
}

void Actuator::MotorCalibration(int cal_type, int motor_min, int motor_mid, int motor_max, int motor_polarity)
{
    // Print current calibration value
    servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
    m_logger.LogInfo() << ("Current Motor calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);

    // Set New calibration value
    servoMgr->setCalibrationValue(cal_type, motor_min - 10, motor_mid - 10, motor_max - 10, motor_polarity == 1 ? -1 : 1);

    // Print updated calibration value
    servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
    m_logger.LogInfo() << ("New Servo calibration value(-10): min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);

    // Recover calibration value
    servoMgr->setCalibrationValue(cal_type, motor_min + 10, motor_mid + 10, motor_max + 10, motor_polarity == 1 ? -1 : 1);

    // Print recovered calibration value
    servoMgr->getCalibrationValue(cal_type, &motor_min, &motor_mid, &motor_max, &motor_polarity);
    m_logger.LogInfo() << ("Recovered Current Servo calibration value: min: %d, mid: %d, max: %d, polarity: %d\n", motor_min, motor_mid, motor_max, motor_polarity);
}
 
} /// namespace aa
} /// namespace actuator
