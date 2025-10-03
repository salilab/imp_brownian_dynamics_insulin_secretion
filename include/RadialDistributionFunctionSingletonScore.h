/**
 * \file IMP/insulinsecretion/RadialDistributionFunctionSingletonScore.h
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

#ifndef IMPINSULINSECRETION_RADIAL_DISTRIBUTION_FUNCTION_SINGLETON_SCORE_H
#define IMPINSULINSECRETION_RADIAL_DISTRIBUTION_FUNCTION_SINGLETON_SCORE_H
        
#include <IMP/insulinsecretion/insulinsecretion_config.h> // provide macros to mark functions and classes as exported and to set up namespaces
#include <IMP/enums.h>
#include <IMP/SingletonScore.h> // Define SingletonScore.
#include <IMP/singleton_macros.h> // Macros for various classes
#include <IMP/algebra/Vector3D.h>
#include <limits>
#include <IMP/core/XYZR.h>
#include <IMP/algebra/Vector3D.h>
#include <IMP/algebra/Sphere3D.h> 
#include <IMP/atom/smoothing_functions.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

/** 
  A score on insulin vesicles based on its radial distribution function around the nucleus.
*/
//template <class UF>
class IMPINSULINSECRETIONEXPORT RadialDistributionFunctionSingletonScore 
: public IMP::SingletonScore
{ algebra::Sphere3D cell_sphere_;
  algebra::Sphere3D nucleus_sphere_;
  Floats poly_param_; // 1D vector, will accept a list of floats from Python.
  double k_; //RDF list
  
 public:
  /**
    * 1, Read in the coefficients of the polynomial fitting for the score -k *ln(radial distribution function) of insulin vesicles around nucleus.
    * 2, Read in the coefficient k for the score -k *ln(radial distribution function)
    * 3, Read the insulin vesicle coordinates  
    * 4, Apply the contineous singlton score on insulin vesicles between Rne + Risg - Rpbc - Risg.
  
     @param m the model of p
     @param p the index in m of an object of type Particle
     @param da a DerivativeAccumulator that weights
                computed derivatives. If nullptr, derivatives
                will not be computed.
     @param cell_sphere the sphere of the cell with center point and radius, A.
     @param nucleus_sphere the sphere of the nucleus with center point and radius, A.
     @param poly_param_ 1D vector with coefficients for polynomial fitting on RDF (6 coefficient for a 5-order polynomail fitting).
     @param k the coefficient for the score -k*ln(radial distribution function), kcal/mol.
    */

  RadialDistributionFunctionSingletonScore(algebra::Sphere3D cell_sphere,
                                           algebra::Sphere3D nucleus_sphere,
                                           Floats poly_param,
                                           double k);

  //! sets the force constant for pushing particles away from the center 
  //!in kcal/mol/A (negative=pull)
  void set_k(double k) 
  { k_= k; }

  //! returns the force constant for pushing particles away from the center
  //!in kcal/mol/A (negative=pull)
  double get_k() const 
  { return k_; }

  //! sets the cell sphere
  //!
  void set_cell_sphere(algebra::Sphere3D cell_sphere) 
  { cell_sphere_= cell_sphere; }

  //! returns the cell sphere
  //!
  algebra::Sphere3D get_cell_sphere() const 
  { return cell_sphere_; }

  //! sets the nucleus sphere
  //!
  void set_nucleus_sphere(algebra::Sphere3D nucleus_sphere) 
  { nucleus_sphere_= nucleus_sphere; }

  //! returns the nucleus sphere
  //!
  algebra::Sphere3D get_nucleus_sphere() const 
  { return nucleus_sphere_; }

  //! sets the coefficients for polynomial fitting on RDF
  //!
  void set_poly_param(Floats poly_param)
  { poly_param_= poly_param; }

  //! returns the coefficients for polynomial fitting on RDF
  //!
  Floats get_poly_param() const
  { return poly_param_;}

  virtual double evaluate_index
  ( Model *m, 
    ParticleIndex pi,
    DerivativeAccumulator *da ) const override; // adding derivatives from restraints to the model

  virtual ModelObjectsTemp do_get_inputs
  ( Model *m,
    const ParticleIndexes &pis ) const override; //tell IMP which particles our restraint acts on

  IMP_SINGLETON_SCORE_METHODS(RadialDistributionFunctionSingletonScore);
  IMP_OBJECT_METHODS(RadialDistributionFunctionSingletonScore);
};
           
IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_RADIAL_DISTRIBUTION_FUNCTION_SINGLETON_SCORE_H */
 