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
	if( PlaneWave::kinetic( kPoint ) <= this->cutoff() ) this->mesh( kPoint ) ;
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
  return this->my_cutoff;
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
 *        Note that we don't support random insertion into the list. Furthermore, we don't
 *        have a getter for a k-point. Hopefully this encourages the use of a std::list
 *        iterator for fast access!
 *
 * @param[out] triple_t & : The k-point to append to the mesh list.
 */
void PlaneWave::mesh( const triple_t & _kPoint ) {
  this->my_mesh.push_back( _kPoint ) ;
}

/**
 * @brief Sort the mesh in order of ascending k-point kinetic energy.
 *
 *        We use the std::list::sort method which has been overloaded to support a comparison
 *        statement with which to perform the sorting. Lambda is given as argument to
 *        std::list::sort, comparing the kinetic energy of two k-points.
 */
void PlaneWave::sort( ) {
  this->my_mesh.sort( [] (const triple_t & a, const triple_t & b) { return PlaneWave::kinetic( a ) < PlaneWave::kinetic( b ) ;} ) ;
}

/**
 * @brief Print some details about the mesh. 
 *
 *        Probably fairly overwhelming even for small kinetic energy cutoffs, but likely useful 
 *        for debugging. Note the proper usage of the iterator to traverse the mesh!
 */
void PlaneWave::print( ) {
  std::cout << "k-point Mesh with Cutoff : " << this->cutoff() << " Number of Orbitals : " << this->my_mesh.size() << std::endl ;
  std::list<triple_t>::iterator it ;
  for( it=this->my_mesh.begin() ; it!=this->my_mesh.end() ; ++it ) {
    triple_t kPoint = * it ;
    std::cout
      << "k-point Indices (" 
      << std::setw( 3 ) << std::get<0>( kPoint ) << ","
      << std::setw( 3 ) << std::get<1>( kPoint ) << ","
      << std::setw( 3 ) << std::get<2>( kPoint ) << ")"
      << "  Kinetic : " << std::setw( 10 ) << std::setprecision( 6 ) << std::fixed << kinetic( kPoint ) <<
      std::endl ;
  }
}
