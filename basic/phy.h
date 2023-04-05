/**
 * @brief PHY.h
 *  this header define some physical constants that can be used with 
 *  some sensors
 * 
 * @param student: Sameer Almaldein
 * @param ID:679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _PHY_H_
#define _PHY_H_

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdalign.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>

#include <alloca.h>
#include <limits.h>
#include <syslimits.h>
#include <string.h>

//********************************************************************************************
//
//    constants
//
//********************************************************************************************

/* Constants */
#define SENSORS_GRAVITY_EARTH        (9.80665F)               /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON         (1.6F)                   /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN          (275.0F)                 /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD     (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX   (60.0F)                  /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN   (30.0F)                  /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA (1013.25F)               /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS          (0.017453293F)           /**< Degrees/s to rad/s multiplier */
#define SENSORS_RADS_TO_DPS          (57.29577793F)           /**< Rad/s to degrees/s  multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA  (100)                    /**< Gauss to micro-Tesla multiplier */

//********************************************************************************************
//
// macros
//
//********************************************************************************************


//********************************************************************************************
//
//  data structures
//
//********************************************************************************************

//********************************************************************************************
//
// global variables
//
//********************************************************************************************


//********************************************************************************************
//
//  function prototypes
//
//********************************************************************************************


#endif /* _PHY_H_ */