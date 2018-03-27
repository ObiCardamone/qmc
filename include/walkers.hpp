/**
 * @file walkers.hpp
 *
 * @brief Declarations of public methods and definitions of private/static methods for
 *        the Walkers class.
 */
#ifndef WALKERS_HPP
#define WALKERS_HPP

// External includes
#include <iostream>                 // std::cout and std::endl
#include <map>                      // std::map
#include <vector>                   // std::vector
#include <boost/dynamic_bitset.hpp> // boost::dynamic_bitset

typedef boost::dynamic_bitset<>::size_type size_t ;

/**
 * @class Walkers
 *
 * @brief Class for storing walker occupations in determinant space.
 *        Methods for conducting dynamics.
 *
 *        Our choice of mathematical library (boost) has essentially been made for us here.
 *        While there is a std::bitset, it's size has to be set at compile time, which is
 *        unnecessarily restrictive for our purposes. However, a perusal of stackoverflow:
 *
 *        https://stackoverflow.com/questions/3134718/define-bitset-size-at-initialization
 *
 *        reveals that boost contains a bitset class whose size can be set at runtime. We'll
 *        pursue this solution for the moment, but if something like armadillo or trilinos
 *        proves significantly better for the types of operation we conduct in this application,
 *        we'll have to rethink.
 */
class Walkers {

public:
  // Constructors/ Destructors
  Walkers( const size_t _nWalkers, const size_t _nSpinOrbs ) ;

  // Getters/ Setters
  void nWalkers( const size_t _nWalkers ) ;
  std::size_t nWalkers( ) const ;

  // General methods for calculation
  size_t nDiff( const boost::dynamic_bitset<> & det_a, const boost::dynamic_bitset<> & det_b ) const ;
  
private:
  std::size_t my_nWalkers ;
  // We use std::vector for determinant occupations because I think we'll need random access
  // to the array when we start doing spawning and deaths (?)
  // TODO : We need to be able to keep track of the number of walkers on each determinant,
  //        as well as other bit flags, e.g. whether walker spawned from an initiator.
  std::vector< boost::dynamic_bitset<> > my_determinants ; 
  std::vector< std::map< boost::dynamic_bitset<>, std::vector<size_t> > > my_occupation_luts ;
  
} ;

#endif /* #ifndef WALKERS_HPP */
