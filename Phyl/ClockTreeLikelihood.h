//
// File: ClockTreeLikelihood.h
// Created by: Beno�t Nabholz
// Created on: Fri Apr 06 14:11 2007
//

/*
Copyright or � or Copr. CNRS, (November 16, 2004)

This software is a computer program whose purpose is to provide classes
for phylogenetic data analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef _CLOCKTREELIKELIHOOD_H_
#define _CLOCKTREELIKELIHOOD_H_

#include "HomogeneousTreeLikelihood.h"
#include "TreeTemplate.h"

// From NumCalc:
#include <NumCalc/ParameterList.h>

/**
 *@brief Likelihood computation with a global clock.
 *
 * This class overrides the HomogeneousTreeLikelihood class, and change the branch length parameters
 * which are the heights of the ancestral nodes.
 * Heights are coded as percentage (HeightP) of the height of their father + the total height of the tree (TotalHeight).
 * This parametrization resolve the linear constraint between heights, but has the limitation that the first and second
 * order derivatives for HeightP parameters are not (easilly) computable analytically, and one may wish to use numerical
 * derivatives instead.
 * The tree must be rooted and fully resolved (no multifurcation).
 *
 * Constraint on parameters HeightP are of class IncludingInterval, initially set to [0,1].
 */
class ClockTreeLikelihood:
  public HomogeneousTreeLikelihood
{
  protected:
    IncludingInterval _percentConstraint;

  public:
    /**
     * @brief Build a new ClockTreeLikelihood object.
     *
     * @param tree The tree to use.
     * @param model The substitution model to use.
     * @param rDist The rate across sites distribution to use.
     * @param checkRooted Tell if we have to check for the tree to be rooted.
     * If true, any unrooted tree will throw an exception. If set to false, the
     * tree will be considered rooted, and any basal multifurcation will be
     * considered as a true multifurcation. In the current version of this class
     * however, multifurcation are not supported, so this option is mainly for
     * forward compatibility!
     * @param verbose Should I display some info?
     * @throw Exception in an error occured.
     */
    ClockTreeLikelihood(
      const Tree & tree,
      SubstitutionModel * model,
      DiscreteDistribution * rDist,
      bool checkRooted = true,
      bool verbose = true)
      throw (Exception);
  
    /**
     * @brief Build a new ClockTreeLikelihood object.
     *
     * @param tree The tree to use.
     * @param data Sequences to use.
     * @param model The substitution model to use.
     * @param rDist The rate across sites distribution to use.
     * @param checkRooted Tell if we have to check for the tree to be rooted.
     * If true, any unrooted tree will throw an exception. If set to false, the
     * tree will be considered rooted, and any basal multifurcation will be
     * considered as a true multifurcation. In the current version of this class
     * however, multifurcation are not supported, so this option is mainly for
     * forward compatibility!
     * @param verbose Should I display some info?
     * @throw Exception in an error occured.
     */
    ClockTreeLikelihood(
      const Tree & tree,
      const SiteContainer & data,
      SubstitutionModel * model,
      DiscreteDistribution * rDist,
      bool checkRooted = true,
      bool verbose = true)
      throw (Exception);

    ClockTreeLikelihood * clone() const { return new ClockTreeLikelihood(* this); }

    virtual ~ClockTreeLikelihood() {}

  private:

    /**
     * @brief Method called by constructor.
     */
    void _init();

  public:

    /**
     * @name Re-implementation from the DRHomogeneousTreeLikelihood class:
     *
     * @{
     */
    void applyParameters() throw (Exception);
    void initBranchLengthsParameters();
    ParameterList getDerivableParameters() const throw (Exception);
    ParameterList getNonDerivableParameters() const throw (Exception);
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception) { return 0; } // Not implemented for now.
    /** @} */

  protected:

    /**
     * @brief Update all lengths according to parameter values.
     * 
     * Conflicting heights will be resolved arbitrarily.
     *
     * NB: This is a recursive method.
     * @param node the current node.
     * @param the current height.
     * @throw Exception If something unexpected happened.
     */
    void computeBranchLengthsFromHeights(Node * node, double height) throw (Exception);

};

#endif // _CLOCKTREELIKELIHOOD_H_
