//
// File: Node.h
// Created by: Julien Dutheil
// Created on: Thu Mar 13 12:03:18 2003
//

/*
Copyright ou � ou Copr. Julien Dutheil, (16 Novembre 2004) 

Julien.Dutheil@univ-montp2.fr

Ce logiciel est un programme informatique servant � fournir des classes
pour l'analyse de donn�es phylog�n�tiques.

Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA 
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilit� au code source et des droits de copie,
de modification et de redistribution accord�s par cette licence, il n'est
offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les conc�dants successifs.

A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
associ�s au chargement,  � l'utilisation,  � la modification et/ou au
d�veloppement et � la reproduction du logiciel par l'utilisateur �tant 
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe � 
manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
logiciel � leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement, 
� l'utiliser et l'exploiter dans les m�mes conditions de s�curit�. 

Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez 
pris connaissance de la licence CeCILL, et que vous en avez accept� les
termes.
*/

/*
Copyright or � or Copr. Julien Dutheil, (November 16, 2004)

Julien.Dutheil@univ-montp2.fr

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

#ifndef _NODE_H_
#define _NODE_H_

#include "TreeExceptions.h"

// From the STL:
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

// From Utils:
#include <Utils/Clonable.h>

/**
 * @brief <p>The phylogenetic node class.</p>
 * <p>This class is part of the object implementation of phylogenetic trees. Tree are made
 * made of nodes, instances of this class.</p>
 * <p>Since trees are oriented (rooted), each node has one <i>father node</i> and possibly
 * many <i>son nodes</i>. Leaves are nodes without descendant and root is defined has the without
 * father. Inner nodes will generally contain two descendants (the tree is then called
 * <i>bifurcating</i>), but mutlifurcating trees are also allowed with this kind of description.
 * In the rooted case, each inner node also defines a <i>subtree</i>.
 * This allows to work recursively on trees, which is very convenient in most cases.</p>
 * <p>This class is made the more general as possible, while keeping it very simple. It contains:</p>
 * <ul>
 * <li>An identity tag, to identity it in the tree;</li>
 * <li>A name, necessary for leaf nodes, optionnal else;</li>
 * <li>A pointer toward the father node;</li>
 * <li>A vector of pointer toward son nodes;</li>
 * <li>The distance from the father node:</li>
 * <li>A property map, that may contain any information to link to each node, e.g. bootastrap
 * value or GC content.</li>
 * </ul>
 * @see Tree
 */

class Node {
			
	protected:
		
		int                             _id;
		string                        * _name;
		vector<Node *>                  _sons;
		Node                          * _father;
		double                        * _distanceToFather;
		mutable map<string, Clonable *> _properties;

	public: // Class constructor and destructor:
	
		/**	i
		 * @brief Build a new void Node object.
		 */
		Node() : _id(0), _name(NULL), _father(NULL), _distanceToFather(NULL) {}
			
		/**
		 * @brief Build a new Node with specified id.
		 */
		Node(int id) : _id(id), _name(NULL), _father(NULL), _distanceToFather(NULL) {}

		/**
		 * @brief Build a new Node with specified name.
		 */
		Node(const string & name) : _id(0), _name(new string(name)), _father(NULL), _distanceToFather(NULL) {}

		/**
		 * @brief Build a new Node with specified id and name.
		 */
		Node(int id, const string & name) : _id(id), _name(new string(name)), _father(NULL), _distanceToFather(NULL) {}

		/**
		 * @brief Copy constructor.
		 * 
		 * @param node The node to copy.
		 */
		Node(const Node & node);

		/**
		 * @brief Assignation operator.
		 *
		 * @param node the node to copy.
		 * @return A reference toward this node.
		 */
		Node & operator=(const Node & node);

		virtual ~Node() {	delete _name;	delete _distanceToFather;	}

	public:				
				
		/**
		 * @name Identity
		 *
		 * @{
		 */
			
		/**
		 * @brief Get the node's id.
		 *
		 * @return The identity tag of this node.
		 */
		virtual int getId() const { return _id; }
		
		/**
		 * @brief Set this node's id.
		 *
		 * @param id The new identity tag.
		 */
		virtual void setId(int id) { _id = id; }

		virtual vector<int> getSonsId() const
		{
			vector<int> sonsId(_sons.size());
			for(unsigned int i = 0; i < _sons.size(); i++) {
				sonsId[i] = _sons[i] -> getId();
			}
			return sonsId;
		}

		/** @} */

		/**
		 * @name Name:
		 *
		 * @{
		 */
			
		/**
		 * @brief Get the name associated to this node, if there is one, 
		 * otherwise throw a NodeException.
		 * 
		 * @return The name associated to this node.
		 */
		virtual string getName() const throw (NodeException)
		{
			if(!hasName()) throw NodeException("Node::getName: no name associated to this node.", this);
			return * _name;
		}
				
		/**
		 * @brief Give a name or update the name associated to the node.
		 * 
		 * @param name The name to give to the node.
		 */
		virtual void setName(string & name) { delete _name; _name = new string(name); }
		
		/**
		 * @brief Delete the name associated to this node (do nothing if there is no name).
		 */
		virtual void deleteName() { delete _name; _name = NULL; }
		
		/**
		 * @brief Tell is this node has a name.
		 * 
		 * @return True if name != NULL.
		 */
		virtual bool hasName() const { return _name != NULL; }
		
		/** @} */
		
		/**
		 * @name Distances:
		 *
		 * @{
		 */
		
		/**
		 * @brief Get the distance to the father node is there is one,
		 * otherwise throw a NodeException.
		 * 
		 * @return The distance to the father node.
		 */		 
		virtual double getDistanceToFather() const throw (NodeException) 
		{
			if(!hasDistanceToFather()) throw NodeException("Node::getDistanceToFather: Node has no distance." , this);
			return * _distanceToFather;
		}
				
		/**
		 * @brief Set or update the distance toward the father node.
		 * 
		 * @param distance The new distance to the father node.
		 */
		virtual void setDistanceToFather(double distance) { delete _distanceToFather; _distanceToFather = new double(distance); }
		
		/**
		 * @brief Delete the distance to the father node.
		 */
		virtual void deleteDistanceToFather() { delete _distanceToFather; _distanceToFather = NULL; }
				
		/**
		 * @brief Tell is this node has a distance to the father.
		 * 
		 * @return True if distanceToFather != NULL.
		 */
		virtual bool hasDistanceToFather() const { return _distanceToFather != NULL; }

		/** @} */
				
		/**
		 * @name Father:
		 *
		 * @{
		 */
			
		/**
		 * @brief Get the father of this node is there is one.
		 * 
		 * @return A pointer toward the father node, NULL if there is not.
		 */		 
		virtual const Node * getFather() const { return _father; }
				
		/**
		 * @brief Get the father of this node is there is one.
		 * 
		 * @return A pointer toward the father node, NULL if there is not.
		 */		 
		virtual Node * getFather() { return _father; }
		
		virtual int getFatherId() const { return _father -> getId(); }
				
		/**
		 * @brief Set the father node of this node.
		 * 
		 * @param node The father node.
		 */
		virtual void setFather(Node & node) { _father = & node; }
				
		/**
		 * @brief Remove the father of this node.
		 */
		virtual Node * removeFather() { Node * f = _father; _father = NULL; return f; }
				
		/**
		 * @brief Tell if this node has a father node.
		 */
		virtual bool hasFather() const { return _father != NULL; }

		/** @} */

		/**
		 * @name Sons:
		 *
		 * @{
		 */
				 
		virtual unsigned int getNumberOfSons() const { return _sons.size(); }

		virtual const Node * getSon(unsigned int i) const { return _sons[i]; }
				
		virtual Node * getSon(unsigned int i) { return _sons[i]; }
				
		virtual void addSon(unsigned int pos, Node & node)
		{
			_sons.insert(_sons.begin() + pos, & node);
			node._father = this;
		}

		virtual void addSon(Node & node)
		{
			_sons.push_back(& node);
			node._father = this;
		}

		virtual void setSon(unsigned int pos, Node & node) throw (NodeException)
		{
			if(pos >= _sons.size()) throw NodeException("Node::setSon(). Invalid node position.", & node);
			_sons[pos] = & node;
			node._father = this;
		}
				
		virtual void removeSon(unsigned int i)
	  {
			Node * node = _sons[i];
			_sons.erase(_sons.begin() + i);
			node -> removeFather();
		}
		
		virtual void removeSon(Node & node)
		{
			for(unsigned int i = 0; i < _sons.size(); i++) if(* _sons[i] == node) _sons.erase(_sons.begin() + i);
			node.removeFather();
		}
		
		virtual void removeSons() {	while(_sons.size() != 0) removeSon(0); }
				
		virtual void swap(unsigned int branch1, unsigned int branch2);

		/** @} */

		// These functions must not be declared as virtual!!
		
		vector<const Node *> getNeighbors() const;
		
		vector<Node *> getNeighbors();

		virtual unsigned int degree() const { return getNumberOfSons() + (hasFather() ? 1 : 0); }
		
		/**
		 * @name Operators:
		 * - a positive value send the corresponding son
		 * - a negative value send the father.
		 *
		 * @{
		 */
				 
		Node * operator[](int i) { return (i < 0) ? _father : _sons[i]; }
				
		const Node * operator[](int i) const { return (i < 0) ? _father : _sons[i]; }
		
		/** @} */
		
		/**
		 * @name Properties:
		 *
		 * @{
		 */
				
		virtual void setProperty(const string & name, Clonable * property) { _properties[name] = property; }
				
		virtual Clonable * getProperty(const string & name) { return _properties[name]; }
				
		virtual const Clonable * getProperty(const string & name) const { return const_cast<const Clonable *>(_properties[name]); }
				
		virtual Clonable * removeProperty(const string & name)
		{
			Clonable * removed = _properties[name];
			_properties.erase(name);
			return removed;
		}	
				
		virtual bool hasProperty(const string & name) const { return _properties.find(name) != _properties.end(); }
		
		/** @} */
		
		// Equality operator:

		virtual bool operator==(const Node & node) const { return _id == node._id; }	
				
		// Tests:

		virtual bool isLeaf() const { return degree() == 1; }
			
//	friend class TreeTemplate<Node>;
};

#endif	//_NODE_H_
