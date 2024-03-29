/*
    Written by Nikilesh Ramesh
*/



#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include "eigen.h"

// ----------- Constants ------- //
#define GAS_CONST 8.31446261815324 // Universal Gas Constant [J/(K*mol)] 
#define SPECIFIC_GAS_CONST 287.05287 // Gas Constant for air
#define GRAVITY_ACCEL 9.80665   // Gravitational acceleration [m/s^2]
#define SEALEVEL_PRESSURE 101325 // P0, sea level pressure [Pa]
#define SEALEVEL_TEMP 288.15 // sea level temperature [K]
#define AVAGADRO_CONST 6.02214076e23 // Avagadro's Constant
#define SEALEVEL_MOLARMASS  28.964420e-03 // (NOT PRIMARY, DERIVED) Molar mass of air at sea level [kg/mol]
#define SPECIFIC_GAS_CONST 287.05287 // specific gas constant (Assumed constant)
#define RADIUS_OF_EARTH 6356766     //See references for this number

// --- Other Definitions ---- // 

#define BASE_PRESSURE layer_const(0)
// to be completed, to tidy up the code....



/**
A class that calculates the altitude from the pressure values, using the ICAO 1993 standard. 
Altitude Calculation is different for when the tempreature gradient, beta is zero versus when not. 
When beta != 0:
    \f{eqnarray*}{
        H = H_b + \frac{T_b}{\beta} ((\frac{P_b}{P})^{\frac{\beta R}{g_0}} - 1)
    \f}
When beta = 0:
    \f{eqnarray*}{
        H = H_b + \frac{RT}{g_0} ln({\frac{P_b}{P}})
    \f}
*/
class Atmosphere {
public:
    /**
     * @brief Construct a new Atmosphere object
     * @param pressure The current air pressure [Pa]
     */
    explicit Atmosphere(float pressure);

    /**
     * Get the altitude at this point in the Atmosphere
     * @return The altitude [m] above Mean Sea Level
     */
    float get_altitude();

    /**
     * Get the layer constants for the current pressure
     * @param p The current pressure [Pa]
     * @return A vector of \f$ (H_b, T_b, \beta, P_b) \f$ which represents the layer constants
     */
    Eigen::Vector4f get_layer_constants(float p);

    float to_geopotential(float alt); // additional feture to be added, right now everything is in geometric


private:

    // Modifiable values
    int geometric_alt;
    int geopotential_alt;
    Eigen::Vector4f layer_const;

    float altitude(float pressure);

    // matrix of layer constants
    // each Layer  =  {Geopotential [m], Temperature [K], Temp Gradient[K/m]}
    Eigen::Matrix<float, 9, 4> layers;


};