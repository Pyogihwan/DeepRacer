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
/// GENERATED FILE NAME               : simactuator.h
/// SOFTWARE COMPONENT NAME           : SimActuator
/// GENERATED DATE                    : 2024-11-01 13:31:53
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_SIMACTUATOR_AA_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_SIMACTUATOR_AA_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "simactuator/aa/port/controldata.h"

#include "para/swc/port_pool.h"

namespace simactuator
{
    namespace aa
    {

        class SimActuator
        {
        public:
            /// @brief Constructor
            SimActuator();

            /// @brief Destructor
            ~SimActuator();

            /// @brief Initialize software component
            bool Initialize();

            /// @brief Start software component
            void Start();

            /// @brief Terminate software component
            void Terminate();

        private:
            /// @brief Run software component
            void Run();

            void TaskReceiveCEventCyclic();

            void OnReceiveCEvent(const deepracer::service::controldata::proxy::events::CEvent::SampleType &sample);

        private:
            bool m_running;
            /// @brief Pool of port
            ::para::swc::PortPool m_workers;

            /// @brief Logger for software component
            ara::log::Logger &m_logger;

            /// @brief Instance of Port {SimActuator.ControlData}
            std::shared_ptr<simactuator::aa::port::ControlData> m_ControlData;
        };

    } /// namespace aa
} /// namespace simactuator

#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_SIMACTUATOR_AA_H