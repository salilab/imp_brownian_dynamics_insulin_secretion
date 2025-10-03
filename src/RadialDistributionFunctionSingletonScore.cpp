/**
 * \file IMP/insulinsecretion/RadialDistributionFunctionSingletonScore.cpp
 * \brief A score on insulin vesicles based on its radial distribution function around the nucleus.
 *
 * Description:
 * 1, Read in the coefficients of the polynomial fitting for the score -k *ln(radial distribution function) of insulin vesicles around nucleus.
 * 2, Read in the coefficient k for the score -k *ln(radial distribution function).
 * 3, Read the insulin vesicle coordinates.
 * 4, Apply the contineous singlton score on insulin vesicles between Rne + Risg - Rpbc - Risg.
 * 
 * Note: Polynomial fitting is applied between 1/2 of the first shell to 1/2 of the last shell
 *       RDF is calculated by dividing the cytoplasma into 8 shells
 *       The score should be applied between Rne + (Rpbc - Rne)/8/2 ~ Rpbc - (Rpbc - Rne)/8/2, 
 *       which is slightly smaller than Risg.
 *       Thus, we can apply the RDF score between Rne + Risg - Rpbc - Risg.
 * 
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/RadialDistributionFunctionSingletonScore.h>
#include <IMP/UnaryFunction.h>
#include <cmath>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

/**
 */
RadialDistributionFunctionSingletonScore::RadialDistributionFunctionSingletonScore
( algebra::Sphere3D cell_sphere,
  algebra::Sphere3D nucleus_sphere,
  Floats poly_param,
  double k) 
  : cell_sphere_( cell_sphere ),
    nucleus_sphere_( nucleus_sphere ),
    poly_param_( poly_param ),
    k_( k )
{}

double RadialDistributionFunctionSingletonScore::evaluate_index
( Model *m,
  ParticleIndex pi,
  DerivativeAccumulator *da) const {

  IMP_OBJECT_LOG;
  core::XYZR xyzr(m,pi);
  double Rcell = cell_sphere_.get_radius(); 
  double Rnucleus = nucleus_sphere_.get_radius();
  double Rgranule = xyzr.get_radius();
  algebra::Vector3D dxyz = xyzr.get_coordinates() - cell_sphere_.get_center();
  double dxyz_magnitude = algebra::get_magnitude_and_normalize_in_place( dxyz ) - Rnucleus - Rgranule;
  if (0 <= dxyz_magnitude && dxyz_magnitude <= Rcell - Rnucleus - 2*Rgranule) {
    double score =  k_ * (poly_param_[0] * pow(dxyz_magnitude,5) + poly_param_[1] * pow(dxyz_magnitude,4) 
                    + poly_param_[2] * pow(dxyz_magnitude,3) + poly_param_[3] * pow(dxyz_magnitude,2)
                    + poly_param_[4] * dxyz_magnitude + poly_param_[5]);  //Sigmoid function
      if (da) {
      algebra::Vector3D& dxyz_normalized= dxyz; // it is now a normalized version of itself
      algebra::Vector3D deriv= k_ * (5 * poly_param_[0] * pow(dxyz_magnitude,4) + 4 * poly_param_[1] * pow(dxyz_magnitude,3) 
                    + 3 * poly_param_[2] * pow(dxyz_magnitude,2) + 2 * poly_param_[3] * dxyz_magnitude
                    + poly_param_[4]) * dxyz_normalized; 
      IMP_LOG(VERBOSE, "score " << score
          << " and derivative " << deriv << std::endl);
      xyzr.add_to_derivatives(deriv, *da);
    }
    return score;
  }
}
  
// for do_get_inputs
ModelObjectsTemp 
RadialDistributionFunctionSingletonScore
::do_get_inputs
( Model *m, const ParticleIndexes &pis ) const { 
  return IMP::get_particles(m, pis);  
}

IMPINSULINSECRETION_END_NAMESPACE
