#pragma once
#include "SimulationStrategy.hpp"
#include <memory>

struct TelemetryFieldModel
{
    std::shared_ptr<SimulationStrategy> strategy;
};

struct NavigationSimulationConfig
{
    TelemetryFieldModel system_status;
    TelemetryFieldModel nav_mode;
    TelemetryFieldModel target_distance_m;
    TelemetryFieldModel relative_velocity_mps;
    TelemetryFieldModel yaw_rate_dps;
    TelemetryFieldModel pitch_rate_dps;
    TelemetryFieldModel roll_rate_dps;
    TelemetryFieldModel engine_temp_c;
    TelemetryFieldModel gyro_drift_ppm;
    TelemetryFieldModel hyperdrive_charge_pct;
    TelemetryFieldModel course_correction_x_m;
    TelemetryFieldModel course_correction_y_m;
    TelemetryFieldModel course_correction_z_m;
    TelemetryFieldModel positional_error_m;
    TelemetryFieldModel checksum;
};

