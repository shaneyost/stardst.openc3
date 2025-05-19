#include "NavigationSubsystem.hpp"
#include "CcsdsPrimaryHeader.hpp"
#include "CcsdsSecondaryHeader.hpp"
#include "CcsdsPacket.hpp"
#include "Logger.hpp"
#include "IncrementalStrategy.hpp"
#include "RandomNoiseStrategy.hpp"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdint>
#include <cstring>

// Constructor initializes default simulation strategies
NavigationSubsystem::NavigationSubsystem(std::atomic<bool>& runningFlag)
    : running(runningFlag)
{
    auto default_strategy = std::make_shared<IncrementalStrategy>();

    config_.system_status.strategy = default_strategy;
    config_.nav_mode.strategy = default_strategy;
    config_.target_distance_m.strategy = default_strategy;
    config_.relative_velocity_mps.strategy = default_strategy;
    config_.yaw_rate_dps.strategy = default_strategy;
    config_.pitch_rate_dps.strategy = default_strategy;
    config_.roll_rate_dps.strategy = default_strategy;
    config_.engine_temp_c.strategy = default_strategy;
    config_.gyro_drift_ppm.strategy = default_strategy;
    config_.hyperdrive_charge_pct.strategy = default_strategy;
    config_.course_correction_x_m.strategy = default_strategy;
    config_.course_correction_y_m.strategy = default_strategy;
    config_.course_correction_z_m.strategy = default_strategy;
    config_.positional_error_m.strategy = default_strategy;
    config_.checksum.strategy = default_strategy;
}

void NavigationSubsystem::simulate()
{
    if (config_.system_status.strategy) config_.system_status.strategy->apply(telemetry_.system_status);
    if (config_.nav_mode.strategy) config_.nav_mode.strategy->apply(telemetry_.nav_mode);
    if (config_.target_distance_m.strategy) config_.target_distance_m.strategy->apply(telemetry_.target_distance_m);
    if (config_.relative_velocity_mps.strategy) config_.relative_velocity_mps.strategy->apply(telemetry_.relative_velocity_mps);
    if (config_.yaw_rate_dps.strategy) config_.yaw_rate_dps.strategy->apply(telemetry_.yaw_rate_dps);
    if (config_.pitch_rate_dps.strategy) config_.pitch_rate_dps.strategy->apply(telemetry_.pitch_rate_dps);
    if (config_.roll_rate_dps.strategy) config_.roll_rate_dps.strategy->apply(telemetry_.roll_rate_dps);
    if (config_.engine_temp_c.strategy) config_.engine_temp_c.strategy->apply(telemetry_.engine_temp_c);
    if (config_.gyro_drift_ppm.strategy) config_.gyro_drift_ppm.strategy->apply(telemetry_.gyro_drift_ppm);
    if (config_.hyperdrive_charge_pct.strategy) config_.hyperdrive_charge_pct.strategy->apply(telemetry_.hyperdrive_charge_pct);
    if (config_.course_correction_x_m.strategy) config_.course_correction_x_m.strategy->apply(telemetry_.course_correction_x_m);
    if (config_.course_correction_y_m.strategy) config_.course_correction_y_m.strategy->apply(telemetry_.course_correction_y_m);
    if (config_.course_correction_z_m.strategy) config_.course_correction_z_m.strategy->apply(telemetry_.course_correction_z_m);
    if (config_.positional_error_m.strategy) config_.positional_error_m.strategy->apply(telemetry_.positional_error_m);
    if (config_.checksum.strategy) config_.checksum.strategy->apply(telemetry_.checksum);
}

void NavigationSubsystem::setFieldModel(const std::string& field_name, std::shared_ptr<SimulationStrategy> strategy)
{
    if (field_name == "system_status") config_.system_status.strategy = strategy;
    else if (field_name == "nav_mode") config_.nav_mode.strategy = strategy;
    else if (field_name == "target_distance_m") config_.target_distance_m.strategy = strategy;
    else if (field_name == "relative_velocity_mps") config_.relative_velocity_mps.strategy = strategy;
    else if (field_name == "yaw_rate_dps") config_.yaw_rate_dps.strategy = strategy;
    else if (field_name == "pitch_rate_dps") config_.pitch_rate_dps.strategy = strategy;
    else if (field_name == "roll_rate_dps") config_.roll_rate_dps.strategy = strategy;
    else if (field_name == "engine_temp_c") config_.engine_temp_c.strategy = strategy;
    else if (field_name == "gyro_drift_ppm") config_.gyro_drift_ppm.strategy = strategy;
    else if (field_name == "hyperdrive_charge_pct") config_.hyperdrive_charge_pct.strategy = strategy;
    else if (field_name == "course_correction_x_m") config_.course_correction_x_m.strategy = strategy;
    else if (field_name == "course_correction_y_m") config_.course_correction_y_m.strategy = strategy;
    else if (field_name == "course_correction_z_m") config_.course_correction_z_m.strategy = strategy;
    else if (field_name == "positional_error_m") config_.positional_error_m.strategy = strategy;
    else if (field_name == "checksum") config_.checksum.strategy = strategy;
    else
        throw std::invalid_argument("Unknown field name: " + field_name);
}

std::vector<uint8_t> NavigationSubsystem::packTelemetry() const
{
    std::vector<uint8_t> buffer;

    auto append = [&buffer](auto value) {
        uint8_t* bytes = reinterpret_cast<uint8_t*>(&value);
        buffer.insert(buffer.end(), bytes, bytes + sizeof(value));
    };

    append(telemetry_.system_status);
    append(telemetry_.nav_mode);
    append(telemetry_.target_distance_m);
    append(telemetry_.relative_velocity_mps);
    append(telemetry_.yaw_rate_dps);
    append(telemetry_.pitch_rate_dps);
    append(telemetry_.roll_rate_dps);
    append(telemetry_.engine_temp_c);
    append(telemetry_.gyro_drift_ppm);
    append(telemetry_.hyperdrive_charge_pct);
    append(telemetry_.course_correction_x_m);
    append(telemetry_.course_correction_y_m);
    append(telemetry_.course_correction_z_m);
    append(telemetry_.positional_error_m);
    append(telemetry_.checksum);

    return buffer;
}

void NavigationSubsystem::run()
{
    auto random_strategy = std::make_shared<RandomNoiseStrategy>();
    setFieldModel("engine_temp_c", random_strategy);
    setFieldModel("yaw_rate_dps", random_strategy);

    auto prihdr = CcsdsPrimaryHeader::createTelemetryPacket(42);

    while (running.load())
    {
        auto sechdr = CcsdsSecondaryHeader::now();
        prihdr.incrementSequenceCount();

        simulate();

        std::vector<uint8_t> data = packTelemetry();

        CcsdsPacket packet(prihdr, sechdr, std::move(data));
        auto serialized = packet.serialize();  // fully compliant ccsds packet v1

        /*LOG_VECTOR(serialized, serialized.size());*/
        LOG_VECTOR(serialized, 14);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    LOG_WARN("Stopping NavigationSubsystem thread");
}
