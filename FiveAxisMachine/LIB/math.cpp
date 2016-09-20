//#include "stdafx.h"
#include "math.hpp"
//#include <algorithm>
//#include <vector>
//#include <boost/numeric/ublas/banded.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#define BOOST_NUMERIC_BINDINGS_USE_CLAPACK
//#include <boost/numeric/bindings/lapack/gesvd.hpp>
//#include <boost/numeric/bindings/traits/std_vector.hpp>
//#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
//#undef  BOOST_NUMERIC_BINDINGS_USE_CLAPACK


template <class M, class MI>
void math::invert(const M& m, MI& mi)
{
	BOOST_UBLAS_CHECK(m.size1() == m.size2(), external_logic());

    matrix<double>       lhs(m);
    matrix<double>       rhs(identity_matrix<double>(m.size1()));
    permutation_matrix<> pm(m.size1());

    lu_factorize(lhs, pm);
    lu_substitute(lhs, pm, rhs);

    BOOST_UBLAS_CHECK(rhs.size1() == m.size1(), internal_logic());
    BOOST_UBLAS_CHECK(rhs.size2() == m.size2(), internal_logic());

#if BOOST_UBLAS_TYPE_CHECK
    BOOST_UBLAS_CHECK(
        detail::expression_type_check(prod(m, rhs),
									  identity_matrix<typename M::value_type>(m.size1())),
									  internal_logic()
		);
#endif

    mi.resize(rhs.size1(), rhs.size2(), false);
    mi.assign(rhs);
    // mi.assign_temporary(rhs);
}
