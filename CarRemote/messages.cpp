#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */
namespace opendlv { namespace proxy {

uint32_t GroundSteeringReading::ID() {
    return 1045;
}

const std::string GroundSteeringReading::ShortName() {
    return "GroundSteeringReading";
}
const std::string GroundSteeringReading::LongName() {
    return "opendlv.proxy.GroundSteeringReading";
}

GroundSteeringReading& GroundSteeringReading::steeringAngle(const float &v) noexcept {
    m_steeringAngle = v;
    return *this;
}
float GroundSteeringReading::steeringAngle() const noexcept {
    return m_steeringAngle;
}

}}

#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */
namespace opendlv { namespace proxy {

uint32_t PedalPositionReading::ID() {
    return 1041;
}

const std::string PedalPositionReading::ShortName() {
    return "PedalPositionReading";
}
const std::string PedalPositionReading::LongName() {
    return "opendlv.proxy.PedalPositionReading";
}

PedalPositionReading& PedalPositionReading::percent(const float &v) noexcept {
    m_percent = v;
    return *this;
}
float PedalPositionReading::percent() const noexcept {
    return m_percent;
}

}}

#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


uint32_t VehicleControl::ID() {
    return 9999;
}

const std::string VehicleControl::ShortName() {
    return "VehicleControl";
}
const std::string VehicleControl::LongName() {
    return "VehicleControl";
}

VehicleControl& VehicleControl::pedalPosition(const float &v) noexcept {
    m_pedalPosition = v;
    return *this;
}
float VehicleControl::pedalPosition() const noexcept {
    return m_pedalPosition;
}

VehicleControl& VehicleControl::steeringAngle(const float &v) noexcept {
    m_steeringAngle = v;
    return *this;
}
float VehicleControl::steeringAngle() const noexcept {
    return m_steeringAngle;
}

VehicleControl& VehicleControl::odometerData(const int &v) noexcept {
    m_odometerData = v;
    return *this;
}
int VehicleControl::odometerData() const noexcept {
    return m_odometerData;
}



