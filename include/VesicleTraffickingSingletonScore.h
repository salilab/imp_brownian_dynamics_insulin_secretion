/**
 *  \file IMP/insulinsecretion/VesicleTraffickingSingletonScore.h
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

#ifndef IMPINSULINSECRETION_VESICLE_TRAFFICKING_SINGLETON_SCORE_H
#define IMPINSULINSECRETION_VESICLE_TRAFFICKING_SINGLETON_SCORE_H

#include <IMP/insulinsecretion/insulinsecretion_config.h>
#include <IMP/enums.h>
#include <IMP/SingletonScore.h>
#include <IMP/singleton_macros.h>
#include <IMP/algebra/Vector3D.h>
#include <limits>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

/**
   A score that pulls vesicles towards the periphery.
*/
class IMPINSULINSECRETIONEXPORT VesicleTraffickingSingletonScore
: public IMP::SingletonScore
{
 private:
  algebra::Vector3D center_; // the sphere center of the score, an underscore suffix defines underlying private member variable for a public property, c++ convention
  double k_; // the force constant 
  
 public:
  /**
     A score that pulls vesicles towards the periphery.

     @param center the sphere center of the score, which is the center 
            of the cell in this case. The direction of the force is 
            vesicle[i].get_coordinates() - center. 
     @param k the magnitude of the radial force vector in units of 
            kcal/mol/A. It is positive for a divergent force and negative 
            for a convergent (gravitation-like) force. 
   */
  VesicleTraffickingSingletonScore
    ( algebra::Vector3D center,
      double k );

  //! sets the force constant for pushing particles away from the center 
  //!in kcal/mol/A (negative=pull)
  void set_k(double k) 
  { k_= k; }

  //! returns the force constant for pushing particles away from the center
  //!in kcal/mol/A (negative=pull)
  double get_k() const 
  { return k_; }
  
  virtual double evaluate_index
  ( Model *m, 
    ParticleIndex pi,
    DerivativeAccumulator *da ) const override; // adding derivatives from restraints to the model

  virtual ModelObjectsTemp do_get_inputs
  ( Model *m,
    const ParticleIndexes &pis ) const override; //tell IMP which particles our restraint acts on

  IMP_SINGLETON_SCORE_METHODS(VesicleTraffickingSingletonScore);
  IMP_OBJECT_METHODS(VesicleTraffickingSingletonScore);
};

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_VESICLE_TRAFFICKING_SINGLETON_SCORE_H */
