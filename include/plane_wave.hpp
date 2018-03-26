/**
 * @file plane_wave.hpp
 *
 * @brief Declarations of public methods and definitions of private/static methods for
 *        the PlaneWave class.
 */
#ifndef PLANE_WAVE_HPP
#define PLANE_WAVE_HPP

// External includes
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cmath>
#include <tuple>
#include <list>

// TODO : This needs to go into some global header
typedef double float_p ;
typedef std::tuple<int, int, int> triple_t ;

/**
 * @class PlaneWave
 *
 * @brief Mesh in k-space bounded by some cutoff kinetic energy specified at initialisation.
 *
 *        The k-points in the mesh are stored in a list, since once sorted, we only ever need to 
 *        iterate through (?), and never require random access. The k-points are sorted on initialisation 
 *        in order of ascending kinetic energy.
 */
class PlaneWave {

public:
  // Constructors/ Destructors
  PlaneWave( const float_p _cutoff ) ;

  // Getters/ Setters
  float_p cutoff() const ;
  void cutoff( const float_p _cutoff ) ;
  void mesh( const triple_t & _kPoint ) ;

  // General methods for calculation
  void sort( ) ;

  // I/O methods
  void print( ) ;

  /**
   * @brief Compute the kinetic energy of a k-point.
   *
   *        Bit of a painful decision making this static. I suppose ideally we'd have an
   *        independent k-point class (?), but I have a feeling this needlessly extends the
   *        class hierarchy, and will inevitably result in an overly-bloated code.
   *
   *        Can't make this a class method because we're using list::sort with lambda for the 
   *        mesh, so we don't have a "this" pointer available within the lambda body.
   *
   * @param[in]  triple_t & : The k-point tuple.
   * @param[out] float_p    : The k-point's kinetic energy.
   */
  static float_p kinetic( const triple_t & _kPoint ) {
    // Extract the k-point indices from the tuple and compute the L2-norm, the kinetic energy
    int n = std::get<0>( _kPoint ), m = std::get<1>( _kPoint ), l = std::get<2>( _kPoint ) ;
    return std::sqrt( n*n + m*m + l*l ) ;
  }

private:
  // Kinetic energy cutoff for k-points
  float_p my_cutoff ;
  // The k-point mesh
  std::list<triple_t> my_mesh ;
  
} ;

#endif /* #ifndef PLANE_WAVE_HPP */
