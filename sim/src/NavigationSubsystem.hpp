#pragma once
#include "Subsystem.hpp"
#include "NavigationSimulationConfig.hpp"

#include <atomic>
#include <memory>
#include <string>

class NavigationSubsystem : public Subsystem
{
public:
    NavigationSubsystem(std::atomic<bool>& runningFlag);
    void run() override;
    void setFieldModel(const std::string& field_name, std::shared_ptr<SimulationStrategy> strategy);

private:
    struct NavigationTelemetry
    {
        uint8_t  system_status = 0;
        uint8_t  nav_mode = 0;
        uint32_t target_distance_m = 0;
        int32_t  relative_velocity_mps = 0;
        int16_t  yaw_rate_dps = 0;
        int16_t  pitch_rate_dps = 0;
        int16_t  roll_rate_dps = 0;
        float    engine_temp_c = 0.0f;
        float    gyro_drift_ppm = 0.0f;
        uint8_t  hyperdrive_charge_pct = 0;
        double   course_correction_x_m = 0.0;
        double   course_correction_y_m = 0.0;
        double   course_correction_z_m = 0.0;
        float    positional_error_m = 0.0f;
        uint16_t checksum = 0;
    };

    std::atomic<bool>& running;
    NavigationTelemetry telemetry_;
    NavigationSimulationConfig config_;
    void simulate();
    std::vector<uint8_t> packTelemetry() const;
};
