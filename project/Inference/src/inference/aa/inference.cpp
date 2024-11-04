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
/// GENERATED FILE NAME               : inference.cpp
/// SOFTWARE COMPONENT NAME           : Inference
/// GENERATED DATE                    : 2024-11-04 08:32:44
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "inference/aa/inference.h"
 
namespace inference
{
namespace aa
{
 
Inference::Inference()
    : m_logger(ara::log::CreateLogger("INFR", "SWC", ara::log::LogLevel::kVerbose))
    , m_workers(2)
{
}
 
Inference::~Inference()
{
}
 
bool Inference::Initialize()
{
    m_logger.LogVerbose() << "Inference::Initialize";
    
    bool init{true};
    
    m_FusionData = std::make_shared<inference::aa::port::FusionData>();
    m_InferenceData = std::make_shared<inference::aa::port::InferenceData>();
    
    return init;
}
 
void Inference::Start()
{
    m_logger.LogVerbose() << "Inference::Start";
    
    m_FusionData->Start();
    m_InferenceData->Start();
    
    // run software component
    Run();
}
 
void Inference::Terminate()
{
    m_logger.LogVerbose() << "Inference::Terminate";
    
    m_FusionData->Terminate();
    m_InferenceData->Terminate();
}
 
void Inference::Run()
{
    m_logger.LogVerbose() << "Inference::Run";
    
    m_workers.Async([this] { m_FusionData->ReceiveEventFEventCyclic(); });
    m_workers.Async([this] { m_InferenceData->SendEventIEventCyclic(); });
    
    m_workers.Wait();
}
 
} /// namespace aa
} /// namespace inference
