/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::homogeneousMixture

Description
    Foam::homogeneousMixture

SourceFiles
    homogeneousMixture.C

\*---------------------------------------------------------------------------*/

#ifndef homogeneousMixture_H
#define homogeneousMixture_H

#include "basicCombustionMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                     Class homogeneousMixture Declaration
\*---------------------------------------------------------------------------*/

template<class ThermoType>
class homogeneousMixture
:
    public basicCombustionMixture
{

public:

    //- The type of thermodynamics this mixture is instantiated for
    typedef ThermoType thermoType;

    //- The type of mixture
    typedef ThermoType mixtureType;


private:

    // Private Data

        static const int nSpecies_ = 1;
        static const char* specieNames_[1];

        mixtureType reactants_;
        mixtureType products_;

        mutable mixtureType mixture_;

        //- Regress variable
        volScalarField& b_;


public:

    // Constructors

        //- Construct from dictionary, mesh and phase name
        homogeneousMixture(const dictionary&, const fvMesh&, const word&);

        //- Disallow default bitwise copy construction
        homogeneousMixture(const homogeneousMixture<ThermoType>&) = delete;


    //- Destructor
    virtual ~homogeneousMixture()
    {}


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "homogeneousMixture<" + ThermoType::typeName() + '>';
        }

        const mixtureType& mixture(const scalar) const;

        const mixtureType& cellMixture(const label celli) const
        {
            return mixture(b_[celli]);
        }

        const mixtureType& patchFaceMixture
        (
            const label patchi,
            const label facei
        ) const
        {
            return mixture(b_.boundaryField()[patchi][facei]);
        }

        const mixtureType& cellReactants(const label) const
        {
            return reactants_;
        }

        const mixtureType& patchFaceReactants(const label, const label) const
        {
            return reactants_;
        }

        const mixtureType& cellProducts(const label) const
        {
            return products_;
        }

        const mixtureType& patchFaceProducts(const label, const label) const
        {
            return products_;
        }

        //- Read dictionary
        void read(const dictionary&);

        //- Return thermo based on index
        const ThermoType& specieThermo(const label speciei) const;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const homogeneousMixture<ThermoType>&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifdef NoRepository
    #include "homogeneousMixture.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
