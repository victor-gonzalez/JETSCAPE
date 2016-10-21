// Copyright JETSCAPE Collaboration @ 2016
// This is a general basic class for hydrodynamics
// This is written by Longgang Pang and Chun Shen

#include "./fluid_dynamics.h"

/** make sure the space time point (tau, x, y, eta) is inside
 * evolution history */
void EvolutionHistory::check_in_range(real tau, real x, real y, real eta){
        if (tau < tau_min || tau > tau_max()) {
            throw InvalidSpaceTimeRange("tau=" + std::to_string(tau)
                    + " is not in range [" + tau_min + "," 
                    + tau_max() + "]");
        }
        if (x < x_min || x > x_max()) {
            throw InvalidSpaceTimeRange("x=" + std::to_string(x)
                    + " is not in range [" + x_min + "," 
                    + x_max() + "]");
        }
        if (y < y_min || y > y_max()) {
            throw InvalidSpaceTimeRange("y=" + std::to_string(y)
                    + " is not in range [" + y_min + "," 
                    + y_max() + "]");
        }
        if (eta < eta_min || eta > eta_max()) {
            throw InvalidSpaceTimeRange("eta=" + std::to_string(eta)
                    + " is not in range [" + eta_min + "," 
                    + eta_max() + "]");
        }
}

/** For one given time step id_tau,
 * get FluidCellInfo at spatial point*/
FluidCellInfo EvolutionHistory::get_at_time_step(int id_tau,
                                     real x, real y, real eta) {
    int id_x = get_id_x(x);
    int id_y = get_id_y(y);
    int id_eta = get_id_eta(eta);
}

FluidCellInfo EvolutionHistory::get(real tau, real x, real y, real eta){
    int id_tau = get_id_tau(tau);
    int id_x = get_id_x(x);
    int id_y = get_id_y(y);
    int id_eta = get_id_eta(eta);

}

// if EvolutionHistory is not empty, use JetScape get_hydro_info()
// except this function is overloaded by users
void FluidDynamics::get_hydro_info(real t, real x, real y, real z,
        FluidCellInfo * fluid_cell_info_ptr) {
    if (hydro_status != FINISHED || bulk_info.data.size() == 0) {
        throw std::runtime_error("Hydro evolution is not finished "
                + "or EvolutionHistory is empty");
    }
    // judge whether to use 2D interpolation or 3D interpolation
    if (!tau_eta_is_tz) {
        real tau = std::sqrt(t * t - z * z);
        real eta = 0.5 * (std::log(t + z) - std::log(t - z));
        bulk_info.check_in_range(tau, x, y, eta);
        //return bulk_info.get(tau, x, y, eta);
    } else {
        bulk_info.check_in_range(t, x, y, z);
        //return bulk_info.get(t, x, y, z);
    }
}

real FluidDynamics::get_energy_density(real time, real x, real y, real z) {
    // this function returns the energy density [GeV] at a space time point
    // (time, x, y, z)
    FluidCellInfo *fluid_cell_ptr = new FluidCellInfo;
    get_hydro_info(time, x, y, z, fluid_cell_ptr);
    real energy_density = fluid_cell_ptr->energy_density;
    delete fluid_cell_ptr;
    return(energy_density);
}

real FluidDynamics::get_entropy_density(real time, real x, real y, real z) {
    // this function returns the entropy density [GeV] at a space time point
    // (time, x, y, z)
    FluidCellInfo *fluid_cell_ptr = new FluidCellInfo;
    get_hydro_info(time, x, y, z, fluid_cell_ptr);
    real entropy_density = fluid_cell_ptr->entropy_density;
    delete fluid_cell_ptr;
    return(entropy_density);
}

real FluidDynamics::get_temperature(real time, real x, real y, real z) {
    // this function returns the temperature [GeV] at a space time point
    // (time, x, y, z)
    FluidCellInfo *fluid_cell_ptr = new FluidCellInfo;
    get_hydro_info(time, x, y, z, fluid_cell_ptr);
    real temperature = fluid_cell_ptr->temperature;
    delete fluid_cell_ptr;
    return(temperature);
}

real FluidDynamics::get_qgp_fraction(real time, real x, real y, real z) {
    // this function returns the QGP fraction at a space time point
    // (time, x, y, z)
    FluidCellInfo *fluid_cell_ptr = new FluidCellInfo;
    get_hydro_info(time, x, y, z, fluid_cell_ptr);
    real qgp_fraction = fluid_cell_ptr->qgp_fraction;
    delete fluid_cell_ptr;
    return(qgp_fraction);
}
