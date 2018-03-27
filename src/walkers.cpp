/**
 * @file walkers.cpp
 *
 * @brief Definitions of the public methods in the Walkers class.
 */
// Project includes
#include <walkers.hpp>

/**
 * @brief Initialise a Walkers object.
 *
 * @param[in] std::size_t :: Number of walkers.
 * @param[in] int         :: Number of spin orbitals (for the boost::dynamic_bitset constructor).
 */
Walkers::Walkers( const std::size_t _nWalkers, const size_t _nSpinOrbs ) {
  this->nWalkers( _nWalkers ) ;
  for( size_t iWalker=0 ; iWalker<this->nWalkers() ; iWalker++ ) {  
    this->my_determinants.push_back( boost::dynamic_bitset<>( _nSpinOrbs ) ) ;
  }
}

/**
 * @brief Setter for the number of walkers.
 *
 * @param[in] std::size_t :: The number of walkers.
 */
void Walkers::nWalkers( const std::size_t _nWalkers ) {
  if( _nWalkers < 1 ) throw std::out_of_range( "Cannot set fewer than one walkers." ) ;
  this->my_nWalkers = _nWalkers ;
}

/**
 * @brief Getter for the number of walkers.
 *
 * @param[out] std::size_t : The number of walkers.
 */
std::size_t Walkers::nWalkers( ) const {
  return this->my_nWalkers ;
}

/**
 * @brief Compute the number of occupied spin orbitals which differ between two determinants.
 *
 *        Note that we divide the result by two: a simple logical and would return twice the number
 *        that we want as each determinant possesses a spin-orbital not occupied by the other.
 *
 * @param[in]  boost::dynamic_bitset : The first determinant.
 * @param[in]  boost::dynamic_bitset : The second determinant.
 * @param[out] size_t                : The number of different occupied spin-orbitals between the two determinants.
 */
size_t Walkers::nDiff( const boost::dynamic_bitset<> & det_a, const boost::dynamic_bitset<> & det_b ) const {
  boost::dynamic_bitset<> a_and_b = det_a & det_b ;
  return a_and_b.count() / 2 ;
}
