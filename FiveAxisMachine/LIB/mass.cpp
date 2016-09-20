#ifndef MATH_HPP_20080914
#define MATH_HPP_20080914

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>


namespace math {
    template <class M, class MI> void invert(const M& m, MI& mi);
}


template <class M, class MI>
void math::invert(const M& m, MI& mi)
{
    namespace ublas = boost::numeric::ublas;

    BOOST_UBLAS_CHECK(m.size1() == m.size2(), ublas::external_logic());

    ublas::matrix<double>       lhs(m);
    ublas::matrix<double>       rhs(ublas::identity_matrix<double>(m.size1()));
    ublas::permutation_matrix<> pm(m.size1());

    ublas::lu_factorize(lhs, pm);
    ublas::lu_substitute(lhs, pm, rhs);

    BOOST_UBLAS_CHECK(rhs.size1() == m.size1(), ublas::internal_logic());
    BOOST_UBLAS_CHECK(rhs.size2() == m.size2(), ublas::internal_logic());

#if BOOST_UBLAS_TYPE_CHECK
    BOOST_UBLAS_CHECK(
        ublas::detail::expression_type_check(
            ublas::prod(m, rhs),
            ublas::identity_matrix<typename M::value_type>(m.size1())
        ),
        ublas::internal_logic()
    );
#endif

    mi.resize(rhs.size1(), rhs.size2(), false);
    mi.assign(rhs);
    // mi.assign_temporary(rhs);
}


#endif
