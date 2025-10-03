/**
 *  \file IMP/insulinsecretion/VesicleTraffickingSingletonScore.cpp
 *  \brief A score that pulls vesicles towards the periphery.
 *
 * Description:
 * 1, Activated vesicle[i] gains a velocity towards it’s nearest periphery, 
 *    which corresponds to a vector from the nucleus center to the vesicle center.
 * 2, Force = -k
 * 
 *  
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#include <IMP/insulinsecretion/VesicleTraffickingSingletonScore.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

//! for the definition of score
VesicleTraffickingSingletonScore::VesicleTraffickingSingletonScore
( algebra::Vector3D center,
  double k )
  : center_( center),  
    k_( k )
{}

// for the details of evaluate index
double VesicleTraffickingSingletonScore::evaluate_index
( Model *m, 
  ParticleIndex pi,
  DerivativeAccumulator *da) const {   
  // Set the log level to the object's log level, all non-trivial Object methods should start with this. 
  IMP_OBJECT_LOG;

  // check if derivatives are requested
  // IMP_USAGE_CHECK(!da, "Derivatives not available");

  core::XYZ xyz(m,pi);
  algebra::Vector3D dxyz = xyz.get_coordinates() - center_;
  double dxyz_magnitude = algebra::get_magnitude_and_normalize_in_place( dxyz );
  double score = -k_  * dxyz_magnitude; // score decreases (improves) radially 
  // The derivative accumulator
  if (da) {
    algebra::Vector3D& dxyz_normalized= dxyz; // it is now a normalized version of itself
    algebra::Vector3D deriv= -k_ * dxyz_normalized; 
    IMP_LOG(VERBOSE, "score " << score
          << " and derivative " << deriv << std::endl);
    xyz.add_to_derivatives(deriv, *da);
  }
  return score;
}

// for do_get_inputs
ModelObjectsTemp 
VesicleTraffickingSingletonScore
::do_get_inputs
( Model *m, const ParticleIndexes &pis ) const { 
  return IMP::get_particles(m, pis);  
}

IMPINSULINSECRETION_END_NAMESPACE