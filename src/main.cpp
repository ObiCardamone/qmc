// Project includes
#include <plane_wave.hpp>
#include <walkers.hpp>

/**
 * @brief Entry point for the application.
 */
int main( int argc, char * argv[] ) {

  std::cout << " === QMC begins." << std::endl ; 

  // Initialise a fairly generic plane wave to test functionality.
  PlaneWave planeWave( 2.4 ) ;
  Walkers walkers( 200, 20 ) ;
  
  std::cout << " === QMC ends." << std::endl ; 
  
  return 0 ;
  
}
