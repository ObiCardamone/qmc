/**
 * @file plane_wave.cpp
 *
 * @brief Definitions of the public methods in the PlaneWave class.
 */
// Project includes
#include <plane_wave.hpp>

/**
 * @brief PlaneWave constructor.
 *
 *        Initialise the mesh using a kinetic energy cutoff for the k-points. Consequently
 *        sort the k-points in order of ascending kinetic energy.
 *
 * @param[in] float_p : Kinetic energy cutoff we use for k-points.
 */
PlaneWave::PlaneWave( const float_p _cutoff ) {

  this->cutoff( _cutoff ) ;
  // Compute the highest permissible value for an index of a k-point in the mesh
  float_p kMax = std::ceil( this->cutoff() * this->cutoff() ) ;
  // Make sure we don't get anything stupid
  if( kMax < 0 ) throw std::out_of_range( "Cannot set a negative kMax.\n" ) ;

  // Initialise all k-points in the mesh which are within the specified kinetic energy cutoff
  for( int n=-kMax ; n<=kMax ; n++ ) {
    for( int m=-kMax ; m<=kMax ; m++ ) {
      for( int l=-kMax ; l<=kMax ; l++ ) {
	triple_t kPoint( n, m, l ) ;
	if( this->kinetic( kPoint ) <= this->cutoff() ) this->mesh( kPoint ) ;
      }
    }
  }
  // Sort the k-points in the mesh
  this->sort() ;
  
}

/**
 * @brief Getter for the mesh kinetic energy cutoff.
 *
 * @param[out] float_p : The cutoff.
 */
float_p PlaneWave::cutoff() const {
  return this->my_cutoff ;
}

/**
 * @brief Setter for the mesh kinetic energy cutoff.
 *
 * @param[in] float_p : The cutoff.
 */
void PlaneWave::cutoff( const float_p _cutoff ) {
  if( _cutoff < 0 ) throw std::out_of_range( "Cannot set a negative cutoff.\n" ) ;
  this->my_cutoff = _cutoff ;
}

/**
 * @brief Setter for a mesh k-point.
 *
 * @param[in] triple_t & : The k-point to append to the mesh list.
 */
void PlaneWave::mesh( const triple_t & _kPoint ) {
  this->my_mesh.push_back( _kPoint ) ;
}

/**
 * @brief Getter for a mesh k-point.
 *
 * @param[in]  _idx       : Index from the std::vector to extract the k-point from.
 * @param[out] triple_t & : The k-point to append to the mesh list.
 */
triple_t PlaneWave::mesh( const size_t _idx ) const {
  return this->my_mesh.at( _idx ) ;
}

/**
 * @brief Compute the kinetic energy of a k-point.
 *
 *        I suppose ideally we'd have an independent k-point class (?), but I have a 
 *        feeling this needlessly extends the class hierarchy, and will inevitably result 
 *        in an overly-bloated code.
 *
 * @param[in]  triple_t & : The k-point tuple.
 * @param[out] float_p    : The k-point's kinetic energy.
 */
float_p PlaneWave::kinetic( const triple_t & _kPoint ) {
  // Extract the k-point indices from the tuple and compute the L2-norm, the kinetic energy
  int n = std::get<0>( _kPoint ), m = std::get<1>( _kPoint ), l = std::get<2>( _kPoint ) ;
  return std::sqrt( n*n + m*m + l*l ) ;
}


/**
 * @brief Sort the mesh in order of ascending k-point kinetic energy.
 *
 *        We use the std::sort method which has been overloaded to support a comparison
 *        statement with which to perform the sorting. Lambda is given as argument to
 *        std::sort, comparing the kinetic energy of two k-points. We capture "this" in
 *        the lambda so we have access to PlaneWave::kinetic().
 */
void PlaneWave::sort( ) {
  std::sort(
	     std::begin( this->my_mesh ),
	     std::end( this->my_mesh ),
	     [this] (const triple_t & a, const triple_t & b) -> bool {
	       return this->kinetic( a ) < this->kinetic( b ) ;
	     }
	   ) ;
}

/**
 * @brief Print some details about the mesh. 
 *
 *        Probably fairly overwhelming even for small kinetic energy cutoffs, but likely useful 
 *        for debugging. Note the proper usage of the iterator to traverse the mesh!
 */
void PlaneWave::print( ) {
  std::cout << "k-point Mesh with Cutoff : " << this->cutoff()
	    << " Number of Orbitals : " << this->my_mesh.size() << std::endl ;

  for( auto & it : this->my_mesh ) {
    std::cout
      << "k-point Indices (" 
      << std::setw( 3 ) << std::get<0>( it ) << ","
      << std::setw( 3 ) << std::get<1>( it ) << ","
      << std::setw( 3 ) << std::get<2>( it ) << ")"
      << "  Kinetic : " << std::setw( 10 ) << std::setprecision( 6 ) << std::fixed << kinetic( it ) << std::endl ;
  }
}
