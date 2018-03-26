/**
 * @file plane_wave.hpp
 *
 * @brief Declarations of public methods and definitions of private/static methods for
 *        the PlaneWave class.
 */
#ifndef PLANE_WAVE_HPP
#define PLANE_WAVE_HPP

// External includes
#include <iostream>   // std::cout and std::endl
#include <iomanip>    // std::setw(), std::setprecision(), std::fixed
#include <cstddef>    // std::size_t
#include <cmath>      // std::sqrt()
#include <tuple>      // std::tuple, std::get
#include <vector>     // std::vector
#include <algorithm>  // std::sort(), std::begin(), std::end()

// TODO : This needs to go into some global header
typedef double float_p ;
typedef std::tuple<int, int, int> triple_t ;

/**
 * @class PlaneWave
 *
 * @brief Mesh in k-space bounded by some cutoff kinetic energy specified at initialisation.
 *
 *        The k-points in the mesh are stored in a std::vector, since we wish to retain random access
 *        without penalty. This may be overkill (perhaps we can use std::list?), but we err on the
 *        side of caution for the moment. The k-points are sorted on initialisation in order of ascending 
 *        kinetic energy.
 */
class PlaneWave {

public:
  // Constructors/ Destructors
  PlaneWave( const float_p _cutoff ) ;
  
  // Getters/ Setters
  float_p cutoff() const ;
  void cutoff( const float_p _cutoff ) ;
  void mesh( const triple_t & _kPoint ) ;
  triple_t mesh( const size_t _idx ) const ;

  // General methods for calculation
  void sort( ) ;
  float_p kinetic( const triple_t & _kPoint ) ;
  
  // I/O methods
  void print( ) ;

private:
  // Kinetic energy cutoff for k-points
  float_p my_cutoff ;
  // The k-point mesh
  std::vector<triple_t> my_mesh ;
  
} ;

#endif /* #ifndef PLANE_WAVE_HPP */
