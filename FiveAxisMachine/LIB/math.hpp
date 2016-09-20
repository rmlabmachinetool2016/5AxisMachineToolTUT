#ifndef MATH_HPP
#define MATH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric::ublas;

namespace math {
	// invert matrix
	template <class M, class MI> void invert(const M& m, MI& mi);
	// determinant
	template <class M> double determinant(const M& m);
}

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
	//mi.assign_temporary(rhs);
}

template <class M>
double math::determinant(const M& m)
{
	namespace ublas = boost::numeric::ublas;

	BOOST_UBLAS_CHECK(m.size1() == m.size2(), ublas::external_logic());

	ublas::matrix<double>       lu(m);
	ublas::permutation_matrix<> pm(m.size1());

	ublas::lu_factorize(lu, pm);

	double det(1);

	typedef ublas::permutation_matrix<>::size_type size_type;

	for (size_type i = 0; i < pm.size(); ++i) {
		det *= (i == pm(i)) ? +lu(i, i) : -lu(i, i);
	}

	return det;
}

namespace numeric {
	namespace ublas {
		template <class OP, class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, OP>::result_type
		apply_to_all(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, OP>::expression_type expression_type;

			return expression_type(e());
		}


		template <class OP, class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, OP>::result_type
		apply_to_all(const boost::numeric::ublas::vector_expression<E>& e, const OP&)
		{ return apply_to_all<OP, E>(e); }


		template <class OP, class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, OP>::result_type
		apply_to_all(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, OP>::expression_type expression_type;

			return expression_type(e());
		}


		template <class OP, class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, OP>::result_type
		apply_to_all(const boost::numeric::ublas::matrix_expression<E>& e, const OP&)
		{ return apply_to_all<OP, E>(e); }


		template <class T>
		struct scalar_abs : boost::numeric::ublas::scalar_unary_functor<T> {
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::value_type    value_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::argument_type argument_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::result_type   result_type;

			static BOOST_UBLAS_INLINE result_type apply(argument_type t)
			{ return boost::numeric::ublas::type_traits<value_type>::type_abs(t); }
		};


		template <class T>
		struct scalar_sqrt : boost::numeric::ublas::scalar_unary_functor<T> {
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::value_type    value_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::argument_type argument_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::result_type   result_type;

			static BOOST_UBLAS_INLINE result_type apply(argument_type t)
			{ return boost::numeric::ublas::type_traits<value_type>::type_sqrt(t); }
		};


		template <class T>
		struct scalar_square : boost::numeric::ublas::scalar_unary_functor<T> {
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::value_type    value_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::argument_type argument_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::result_type   result_type;

			static BOOST_UBLAS_INLINE result_type apply(argument_type t)
			{ return t * t; }
		};


		template <class T>
		struct scalar_log : boost::numeric::ublas::scalar_unary_functor<T> {
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::value_type    value_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::argument_type argument_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::result_type   result_type;

			static BOOST_UBLAS_INLINE result_type apply(argument_type t) {
				using std::log;

				return log(t);
			}
		};


		template <class T>
		struct scalar_log10 : boost::numeric::ublas::scalar_unary_functor<T> {
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::value_type    value_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::argument_type argument_type;
			typedef typename boost::numeric::ublas::scalar_unary_functor<T>::result_type   result_type;

			static BOOST_UBLAS_INLINE result_type apply(argument_type t) {
				using std::log10;

				return log10(t);
			}
		};


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, scalar_abs<typename E::value_type> >::result_type
		abs(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, scalar_abs<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, scalar_sqrt<typename E::value_type> >::result_type
		sqrt(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, scalar_sqrt<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, scalar_square<typename E::value_type> >::result_type
		square(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, scalar_square<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, scalar_log<typename E::value_type> >::result_type
		log(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, scalar_log<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_unary_traits<E, scalar_log10<typename E::value_type> >::result_type
		log10(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_unary_traits<E, scalar_log10<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_abs<typename E::value_type> >::result_type
		abs(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_abs<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_sqrt<typename E::value_type> >::result_type
		sqrt(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_sqrt<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_square<typename E::value_type> >::result_type
		square(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_square<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_log<typename E::value_type> >::result_type
		log(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_log<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_log10<typename E::value_type> >::result_type
		log10(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_unary1_traits<E, scalar_log10<typename E::value_type> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class V>
		struct vector_norm_2_sq : public boost::numeric::ublas::vector_scalar_real_unary_functor<V> {
			typedef typename boost::numeric::ublas::vector_scalar_real_unary_functor<V>::value_type  value_type;
			typedef typename boost::numeric::ublas::vector_scalar_real_unary_functor<V>::real_type   real_type;
			typedef typename boost::numeric::ublas::vector_scalar_real_unary_functor<V>::result_type result_type;

			template <class E>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::vector_expression<E>& e) {
#ifndef BOOST_UBLAS_SCALED_NORM
				real_type t = real_type();
				typedef typename E::size_type vector_size_type;
				vector_size_type size (e().size());
				for (vector_size_type i = 0; i < size; ++i) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(e()(i)));
					t += u * u;
				}
				return t;
#else
				real_type scale = real_type();
				real_type sum_squares(1);
				size_type size(e().size());
				for (size_type i = 0; i < size; ++i) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(e()(i)));
					if (scale < u) {
						real_type v(scale / u);
						sum_squares = sum_squares * v * v + real_type(1);
						scale = u;
					}
					else {
						real_type v(u / scale);
						sum_squares += v * v;
					}
				}
				return scale * sum_squares;
#endif
			}

			template <class D, class I>
			static BOOST_UBLAS_INLINE result_type apply(D size, I it) {
#ifndef BOOST_UBLAS_SCALED_NORM
				real_type t = real_type();
				while (--size >= 0) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(*it));
					t += u * u;
					++it;
				}
				return t;
#else
				real_type scale = real_type();
				real_type sum_squares(1);
				while (--size >= 0) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(*it));
					if (scale < u) {
						real_type v(scale / u);
						sum_squares = sum_squares * v * v + real_type(1);
						scale = u;
					}
					else {
						real_type v(u / scale);
						sum_squares += v * v;
					}
					++it;
				}
				return scale * sum_squares;
#endif
			}

			template <class I>
			static BOOST_UBLAS_INLINE result_type apply(I it, const I& it_end) {
#ifndef BOOST_UBLAS_SCALED_NORM
				real_type t = real_type();
				while (it != it_end) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(*it));
					t += u * u;
					++it;
				}
				return t;
#else
				real_type scale = real_type();
				real_type sum_squares(1);
				while (it != it_end) {
					real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(*it));
					if (scale < u) {
						real_type v(scale / u);
						sum_squares = sum_squares * v * v + real_type(1);
						scale = u;
					}
					else {
						real_type v(u / scale);
						sum_squares += v * v;
					}
					++it;
				}
				return scale * sum_squares;
#endif
			}
		};


		// norm_2_sq v = sum(v[i] * v[i])
		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::vector_scalar_unary_traits<E, vector_norm_2_sq<E> >::result_type
		norm_2_sq(const boost::numeric::ublas::vector_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::vector_scalar_unary_traits<E, vector_norm_2_sq<E> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class M>
		struct matrix_sum : public boost::numeric::ublas::matrix_scalar_real_unary_functor<M> {
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::value_type  value_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::real_type   real_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::result_type result_type;

			template <class E>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::matrix_expression<E>& e) {
				real_type t = real_type();
				typedef typename E::size_type matrix_size_type;
				matrix_size_type size1(e().size1());
				for (matrix_size_type i = 0; i < size1; ++i) {
					matrix_size_type size2(e().size2());
					for (matrix_size_type j = 0; j < size2; ++j) {
						t += e()(i, j);
					}
				}
				return t;
			}
		};


		template <class M>
		struct matrix_trace : public boost::numeric::ublas::matrix_scalar_real_unary_functor<M> {
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::value_type  value_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::real_type   real_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::result_type result_type;

			template <class E>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::matrix_expression<E>& e) {
				real_type t = real_type();
				typedef typename E::size_type matrix_size_type;
				matrix_size_type size((std::min)(e().size1(), e().size2()));
				for (matrix_size_type i = 0; i < size; ++i) {
					t += e()(i, i);
				}
				return t;
			}
		};


		template <class M>
		struct matrix_diag_prod : public boost::numeric::ublas::matrix_scalar_real_unary_functor<M> {
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::value_type  value_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::real_type   real_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::result_type result_type;

			template <class E>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::matrix_expression<E>& e) {
				real_type t = real_type(1);
				typedef typename E::size_type matrix_size_type;
				matrix_size_type size((std::min)(e().size1(), e().size2()));
				for (matrix_size_type i = 0; i < size; ++i) {
					t *= e()(i, i);
				}
				return t;
			}
		};


		template <class M>
		struct matrix_norm_frobenius_sq : public boost::numeric::ublas::matrix_scalar_real_unary_functor<M> {
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::value_type  value_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::real_type   real_type;
			typedef typename boost::numeric::ublas::matrix_scalar_real_unary_functor<M>::result_type result_type;

			template <class E>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::matrix_expression<E>& e) {
				real_type t = real_type();
				typedef typename E::size_type matrix_size_type;
				matrix_size_type size1(e().size1());
				for (matrix_size_type i = 0; i < size1; ++i) {
					matrix_size_type size2(e().size2());
					for (matrix_size_type j = 0; j < size2; ++j) {
						real_type u(boost::numeric::ublas::type_traits<value_type>::norm_2(e()(i, j)));
						t += u * u;
					}
				}
				return t;
			}
		};


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_sum<E> >::result_type
		sum(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_sum<E> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_trace<E> >::result_type
		trace(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_trace<E> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_diag_prod<E> >::result_type
		diag_prod(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_diag_prod<E> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class E>
		BOOST_UBLAS_INLINE typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_norm_frobenius_sq<E> >::result_type
		norm_frobenius_sq(const boost::numeric::ublas::matrix_expression<E>& e)
		{
			typedef typename boost::numeric::ublas::matrix_scalar_unary_traits<E, matrix_norm_frobenius_sq<E> >::expression_type expression_type;

			return expression_type(e());
		}


		template <class V1, class V2, class TV>
		struct vector_vector_binary_functor {
			typedef typename V1::size_type       size_type;
			typedef typename V1::difference_type difference_type;
			typedef TV                           value_type;
			typedef TV                           result_type;
		};


		template <class V1, class V2, class TV>
		struct vector_cross_prod : vector_vector_binary_functor<V1, V2, TV> {
			typedef typename vector_vector_binary_functor<V1, V2, TV>::size_type       size_type;
			typedef typename vector_vector_binary_functor<V1, V2, TV>::difference_type difference_type;
			typedef typename vector_vector_binary_functor<V1, V2, TV>::value_type      value_type;
			typedef typename vector_vector_binary_functor<V1, V2, TV>::result_type     result_type;

			template <class C1, class C2>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::vector_container<C1>& c1,
														const boost::numeric::ublas::vector_container<C2>& c2,
														size_type i) {
				return apply(static_cast<const boost::numeric::ublas::vector_expression<C1> >(c1), static_cast<const boost::numeric::ublas::vector_expression<C2> >(c2), i);
			}

			template <class C1, class C2>
			static BOOST_UBLAS_INLINE result_type apply(const boost::numeric::ublas::vector_expression<C1>& c1,
														const boost::numeric::ublas::vector_expression<C2>& c2,
														size_type i) {
				return c1()((i + 1) % 3) * c2()((i + 2) % 3) - c1()((i + 2) % 3) * c2()((i + 1) % 3);
			}

			template <class I1, class I2>
			static BOOST_UBLAS_INLINE result_type apply(difference_type, const I1& it1, const I2& it2, size_type i) {
				return *(it1 + ((i + 1) % 3)) * *(it2 + ((i + 2) % 3)) - *(it1 + ((i + 2) % 3)) * *(it2 + ((i + 1) % 3));
			}

			template <class I1, class I2>
			static BOOST_UBLAS_INLINE result_type apply(const I1& it1, const I1&, const I2& it2, const I2&, size_type i, boost::numeric::ublas::packed_random_access_iterator_tag) {
				return *(it1 + ((i + 1) % 3)) * *(it2 + ((i + 2) % 3)) - *(it1 + ((i + 2) % 3)) * *(it2 + ((i + 1) % 3));
			}

			template <class I1, class I2>
			static BOOST_UBLAS_INLINE result_type apply(I1 it1, const I1&, I2 it2, const I2&, size_type i, boost::numeric::ublas::sparse_bidirectional_iterator_tag) {
				if (i == 0) {
					result_type a(*++it1), c(*++it2);
					return a * *++it2 - *++it1 * c;
				}
				else if (i == 1) {
					result_type b(*it1++), d(*it2++);
					return *++it1 * d - b * *++it2;
				}
				else {
					result_type a(*it1++), c(*it2++);
					return a * *it2 - *it1 * c;
				}
			}
		};


		template <class E1, class E2, class F>
		class vector_vector_binary : public boost::numeric::ublas::vector_expression<vector_vector_binary<E1, E2, F> > {
			typedef E1 expression1_type;
			typedef E2 expression2_type;
			typedef F  functor_type;
			typedef typename E1::const_closure_type expression1_closure_type;
			typedef typename E2::const_closure_type expression2_closure_type;
			typedef vector_vector_binary<E1, E2, F> self_type;
		public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
			using vector_expression<self_type>::operator();
#endif
			static const unsigned complexity = 1;
			typedef typename boost::numeric::ublas::promote_traits<typename E1::size_type, typename E2::size_type>::promote_type size_type;
			typedef typename boost::numeric::ublas::promote_traits<typename E1::difference_type, typename E2::difference_type>::promote_type difference_type;
			typedef typename F::result_type value_type;
			typedef value_type const_reference;
			typedef const_reference reference;
			typedef const self_type const_closure_type;
			typedef const_closure_type closure_type;
			typedef boost::numeric::ublas::unknown_storage_tag storage_category;

			BOOST_UBLAS_INLINE vector_vector_binary(const expression1_type& e1, const expression2_type& e2)
				: e1_(e1), e2_(e2) {}

			BOOST_UBLAS_INLINE size_type size() const {
#ifndef BOOST_UBLAS_USE_FAST_SAME
				using boost::numeric::ublas::same_impl_ex;
#endif

				return BOOST_UBLAS_SAME(e1_.size(), e2_.size());
			}

		private:
			BOOST_UBLAS_INLINE const expression1_closure_type& expression1() const { return e1_; }
			BOOST_UBLAS_INLINE const expression2_closure_type& expression2() const { return e2_; }

		public:
			BOOST_UBLAS_INLINE const_reference operator()(size_type i) const { return functor_type::apply(e1_, e2_, i); }
			BOOST_UBLAS_INLINE const_reference operator[](size_type i) const { return functor_type::apply(e1_, e2_, i); }

			BOOST_UBLAS_INLINE bool same_closure(const vector_vector_binary& vvb) const {
				return (*this).expression1().same_closure(vvb.expression1()) &&
					   (*this).expression2().same_closure(vvb.expression2());
			}

		private:
			typedef typename E1::const_iterator const_subiterator1_type;
			typedef typename E2::const_iterator const_subiterator2_type;
			typedef const value_type* const_pointer;

		public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
			typedef typename boost::numeric::ublas::iterator_restrict_traits<typename const_subiterator1_type::iterator_category,
																			 typename const_subiterator2_type::iterator_category>::iterator_category iterator_category;
			typedef boost::numeric::ublas::indexed_const_iterator<const_closure_type, iterator_category> const_iterator;
			typedef const_iterator iterator;
#else
			class const_iterator;
			typedef const_iterator iterator;
#endif

			BOOST_UBLAS_INLINE const_iterator find(size_type i) const {
				const_subiterator1_type it1(e1_.find(i));
				const_subiterator1_type it1_end(e1_.find(size()));
				const_subiterator2_type it2(e2_.find(i));
				const_subiterator2_type it2_end(e2_.find(size()));
				i = (std::min)(it1 != it1_end ? it1.index() : size(), it2 != it2_end ? it2.index() : size());
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
				return const_iterator(*this, i);
#else
				return const_iterator(*this, i, it1, it1_end, it2, it2_end);
#endif
			}

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
			class const_iterator : public boost::numeric::ublas::container_const_reference<vector_vector_binary>,
								   public boost::numeric::ublas::iterator_base_traits<typename boost::numeric::ublas::iterator_restrict_traits<typename E1::const_iterator::iterator_category,
																																			   typename E2::const_iterator::iterator_category>::iterator_category>::template
																																			   iterator_base<const_iterator, value_type>::type
			{
			public:
				typedef typename boost::numeric::ublas::iterator_restrict_traits<typename E1::const_iterator::iterator_category,
																				 typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
				typedef typename vector_vector_binary::difference_type difference_type;
				typedef typename vector_vector_binary::value_type value_type;
				typedef typename vector_vector_binary::const_reference reference;
				typedef typename vector_vector_binary::const_pointer pointer;

				BOOST_UBLAS_INLINE const_iterator() : boost::numeric::ublas::container_const_reference<self_type>(), i_(), it1_(), it1_end_(), it2_(), it2_end_() {}
				BOOST_UBLAS_INLINE const_iterator(const self_type& vvb, size_type i, const const_subiterator1_type& it1, const const_subiterator1_type& it1_end,
					const const_subiterator2_type& it2, const const_subiterator2_type& it2_end) :
				boost::numeric::ublas::container_const_reference<self_type>(vvb), i_(i), it1_(it1), it1_end_(it1_end), it2_(it2), it2_end_(it2_end) {}

			private:
				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::dense_random_access_iterator_tag)
				{ ++i_; ++it1_; ++it2_; }
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::dense_random_access_iterator_tag)
				{ --i_; --it1_; --it2_; }
				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::dense_random_access_iterator_tag, difference_type n)
				{ i_ += n; it1_ += n; it2_ += n; }
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::dense_random_access_iterator_tag, difference_type n)
				{ i_ -= n; it1_ -= n; it2_ -= n; }
				BOOST_UBLAS_INLINE value_type dereference(boost::numeric::ublas::dense_random_access_iterator_tag) const {
#ifndef BOOST_UBLAS_USE_FAST_SAME
					using boost::numeric::ublas::same_impl_ex;
#endif
					const self_type& vvb = (*this)();
					difference_type size = BOOST_UBLAS_SAME(vvb.expression1().size(), vvb.expression2().size());

					return functor_type::apply(size, it1_().begin(), it2_().begin(), i_);
				}

				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::packed_random_access_iterator_tag) {
					if (it1_ != it1_end_)
						if (it1_.index() <= i_)
							++it1_;
					if (it2_ != it2_end_)
						if (it2_.index() <= i_)
							++it2_;
					++i_;
				}
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::packed_random_access_iterator_tag) {
					if (it1_ != it1_end_)
						if (i_ <= it1_.index())
							--it1_;
					if (it2_ != it2_end_)
						if (i_ <= it2_.index())
							--it2_;
					--i_;
				}
				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::packed_random_access_iterator_tag, difference_type n) {
					while (n > 0) {
						increment(boost::numeric::ublas::packed_random_access_iterator_tag());
						--n;
					}
					while (n < 0) {
						decrement(boost::numeric::ublas::packed_random_access_iterator_tag());
						++n;
					}
				}
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::packed_random_access_iterator_tag, difference_type n) {
					while (n > 0) {
						decrement(boost::numeric::ublas::packed_random_access_iterator_tag());
						--n;
					}
					while (n < 0) {
						increment(boost::numeric::ublas::packed_random_access_iterator_tag());
						++n;
					}
				}
				BOOST_UBLAS_INLINE value_type dereference(boost::numeric::ublas::packed_random_access_iterator_tag) const {
					return functor_type::apply(it1_().begin(), it1_().end(), it2_().begin(), it2_().end(),
						i_, boost::numeric::ublas::packed_random_access_iterator_tag());
				}

				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::sparse_bidirectional_iterator_tag) {
					size_type index1 = (*this)().size();
					if (it1_ != it1_end_) {
						if (it1_.index() <= i_)
							++it1_;
						if (it1_ != it1_end_)
							index1 = it1_.index();
					}
					size_type index2 = (*this)().size();
					if (it2_ != it2_end_) {
						if (it2_.index() <= i_)
							++it2_;
						if (it2_ != it2_end_)
							index2 = it2_.index();
					}
					i_ = (std::min)(index1, index2);
				}
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::sparse_bidirectional_iterator_tag) {
					size_type index1 = (*this)().size();
					if (it1_ != it1_end_) {
						if (i_ <= it1_.index())
							--it1_;
						if (it1_ != it1_end_)
							index1 = it1_.index();
					}
					size_type index2 = (*this)().size();
					if (it2_ != it2_end_) {
						if (i_ <= it2_.index())
							--it2_;
						if (it2_ != it2_end_)
							index2 = it2_.index();
					}
					i_ = (std::max)(index1, index2);
				}
				BOOST_UBLAS_INLINE void increment(boost::numeric::ublas::sparse_bidirectional_iterator_tag, difference_type n) {
					while (n > 0) {
						increment(boost::numeric::ublas::sparse_bidirectional_iterator_tag());
						--n;
					}
					while (n < 0) {
						decrement(boost::numeric::ublas::sparse_bidirectional_iterator_tag());
						++n;
					}
				}
				BOOST_UBLAS_INLINE void decrement(boost::numeric::ublas::sparse_bidirectional_iterator_tag, difference_type n) {
					while (n > 0) {
						decrement(boost::numeric::ublas::sparse_bidirectional_iterator_tag());
						--n;
					}
					while (n < 0) {
						increment(boost::numeric::ublas::sparse_bidirectional_iterator_tag());
						++n;
					}
				}
				BOOST_UBLAS_INLINE value_type dereference(boost::numeric::ublas::sparse_bidirectional_iterator_tag) const {
					return functor_type::apply(it1_().begin(), it1_().end(), it2_().begin(), it2_().end(),
						i_, boost::numeric::ublas::sparse_bidirectional_iterator_tag());
				}

			public:
				BOOST_UBLAS_INLINE const_iterator& operator++() {
					increment(iterator_category());
					return *this;
				}
				BOOST_UBLAS_INLINE const_iterator& operator--() {
					decrement(iterator_category());
					return *this;
				}
				BOOST_UBLAS_INLINE const_iterator& operator+=(difference_type n) {
					increment(iterator_category(), n);
					return *this;
				}
				BOOST_UBLAS_INLINE const_iterator& operator-=(difference_type n) {
					decrement(iterator_category(), n);
					return *this;
				}
				BOOST_UBLAS_INLINE difference_type operator-(const const_iterator& it) const {
					BOOST_UBLAS_CHECK((*this)().same_closure(it()), boost::numeric::ublas::external_logic());
					return index() - it.index();
				}

				BOOST_UBLAS_INLINE const_reference operator*() const
				{ return dereference(iterator_category()); }
				BOOST_UBLAS_INLINE const_reference operator[](difference_type n) const
				{ return *(*this + n); }

				BOOST_UBLAS_INLINE size_type index() const
				{ return i_; }

				BOOST_UBLAS_INLINE const_iterator& operator=(const const_iterator& it) {
					boost::numeric::ublas::container_const_reference<self_type>::assign(&it());
					i_ = it.i_;
					it1_ = it.it1_;
					it1_end_ = it.it1_end_;
					it2_ = it.it2_;
					it2_end_ = it.it2_end_;
					return *this;
				}

				BOOST_UBLAS_INLINE bool operator==(const const_iterator& it) const {
					BOOST_UBLAS_CHECK((*this)().same_closure(it()), boost::numeric::ublas::external_logic());
					return index() == it.index();
				}
				BOOST_UBLAS_INLINE bool operator<(const const_iterator& it) const {
					BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), boost::numeric::ublas::external_logic ());
					return index() < it.index();
				}

			private:
				size_type i_;
				const_subiterator1_type it1_;
				const_subiterator1_type it1_end_;
				const_subiterator2_type it2_;
				const_subiterator2_type it2_end_;
			};
#endif

			BOOST_UBLAS_INLINE const_iterator begin() const { return find(0);      }
			BOOST_UBLAS_INLINE const_iterator end()   const { return find(size()); }

			typedef boost::numeric::ublas::reverse_iterator_base<const_iterator> const_reverse_iterator;

			BOOST_UBLAS_INLINE const_reverse_iterator rbegin() const { return const_reverse_iterator(end());   }
			BOOST_UBLAS_INLINE const_reverse_iterator rend()   const { return const_reverse_iterator(begin()); }

		private:
			expression1_closure_type e1_;
			expression2_closure_type e2_;
		};


		template <class E1, class E2, class F>
		struct vector_vector_binary_traits {
			typedef vector_vector_binary<E1, E2, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
			typedef expression_type result_type;
#else
			typedef typename E1::vector_temporary_type result_type;
#endif
		};


		// cross_prod(v1, v2)[i] = v1[(i + 1) % 3]v2[(i + 2) % 3] - v1[(i + 2) % 3]v2[(i + 1) % 3]
		template <class E1, class E2>
		BOOST_UBLAS_INLINE
		typename vector_vector_binary_traits<E1, E2, vector_cross_prod<E1, E2,
			typename boost::numeric::ublas::promote_traits<typename E1::value_type,
														   typename E2::value_type>::promote_type> >::result_type
		cross_prod(const boost::numeric::ublas::vector_expression<E1>& e1, const boost::numeric::ublas::vector_expression<E2>& e2)
		{
			BOOST_STATIC_ASSERT(E1::complexity == 0 && E2::complexity == 0);

			BOOST_UBLAS_CHECK(e1().size() == 3, boost::numeric::ublas::external_logic());
			BOOST_UBLAS_CHECK(e2().size() == 3, boost::numeric::ublas::external_logic());

			typedef typename vector_vector_binary_traits<E1, E2, vector_cross_prod<E1, E2,
				typename boost::numeric::ublas::promote_traits<typename E1::value_type,
															   typename E2::value_type>::promote_type> >::expression_type expression_type;

			return expression_type(e1(), e2());
		}
	}
}


#endif
