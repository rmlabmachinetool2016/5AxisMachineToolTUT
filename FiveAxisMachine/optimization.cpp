#include "stdafx.h"
#include "optimization.h"
#include "boost/numeric/ublas/matrix_proxy.hpp"
void optimization::swap(double& a,double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

void optimization::shift2(double& a,double& b,double c)
{
	a = b;
	b = c;
}

void optimization::shift3(double& a,double& b,double& c,double d)
{
	a = b;
	b = c;
	c = d;
}

double optimization::sign(double a,double b)
{
	return (b>=0 ? abs(a) : -abs(a));
}

double optimization::fmax(double a,double b)
{
	return (a>b ? a : b);
}



double optimization::golden(double ax,
									double bx,
									vector<double>& co,
									vector<double>& val,
									double (*f)(vector<double>&,vector<double>&),
									double tol,
									double& xmin)
{
	double f1, f2, x0, x1, x2, x3;

	x0 = ax;							// ４点 x0,x1,x2,x3 を更新していく
	x1 = ax + C * (bx - ax);
	x2 = ax + R * (bx - ax); 
	x3 = bx;

	//f1 = (*f)(x1);						// 関数の最初の評価
	//f2 = (*f)(x2);
	val(0) = x1;
	f1 = (*f)(co,val);
	val(0) = x2;
	f2 = (*f)(co,val);

	while(fabs(x3 - x0) > tol * (fabs(x1) + fabs(x2))){	// 収束判定
		if(f2 < f1){								// 場合分けの一方
			SHFT3(x0, x1, x2, R * x1 + C * x3)	// 各点の更新
			val(0)=x2;
			SHFT2(f1, f2, (*f)(co,val))				// 関数を評価x2
		}else{									// 場合分けのもう一方
			SHFT3(x3, x2, x1, R * x2 + C * x0)
			val(0)=x1;
			SHFT2(f2, f1, (*f)(co,val))				// 関数を評価 x1
		}
	}

	if(f1 < f2){				// 完成。最新の２点のうち良い方を返す
		xmin = x1;
		return f1;
	}else{
		xmin = x2;
		return f2;
	}
}

void optimization::mnbrak(
			double &ax,
			double &bx,
			double &cx,
			double &fa,
			double &fb,
			double &fc,
			vector<double>& co,
            vector<double>& val
            )
{
	double ulim,u,r,q,fu,dum;

    //fa = function2d(ax);
    //fb = function2d(bx);
	val(0) = ax;
    fa = function2d(co,val);
	val(0) = bx;
    fb = function2d(co,val);

	if(fb > fa){
		SHFT3(dum,ax,bx,dum)
		SHFT3(dum,fb,fa,dum)
	}
	cx = bx + GOLD*(bx-ax);
	val(0) = cx;
    fc = function2d(co,val);
	while(fb > fc){
		r = (bx - ax)*(fb - fc);
		q = (bx - cx)*(fb - fa);
		u = bx - ((bx-cx)*q-(bx-ax)*r)/(2*sign(fmax(fabs(q-r),TINY),q-r));
		ulim = bx+GLIMIT*(cx-bx);

		if( (bx-u)*(u-cx) > 0 ){
			val(0)=u;
            fu = function2d(co,val);
			if(fu < fc){
				ax=bx;
				bx=u;
				fa=fb;
				fb=fu;
				return;
			}else if(fu > fb){
				cx=u;
				fc=fu;
				return;
			}
			u = cx + GOLD*(cx - bx);
			val(0)=u;
            fu = function2d(co,val);
		}
		else if( (cx-u)*(u-ulim) > 0 ){
			val(0)=u;
            fu=function2d(co,val);
			if(fu < fc){
				SHFT3(bx,cx,u,cx+GOLD*(cx-bx))
				val(0)=u;
                SHFT3(fb,fc,fu,function2d(co,val))
			}
		}
		else if( (ulim-cx)*(u-ulim) >= 0 ){
			u=ulim;
			val(0)=u;
            fu=function2d(co,val);
		}else{
			u=cx+GOLD*(cx-bx);
			val(0)=u;
            fu=function2d(co,val);
		}
		SHFT3(ax,bx,cx,u)
		SHFT3(fa,fb,fc,fu)
	}
}

double optimization::neogolden(
			double ax,
			double bx,
			double cx,
			vector<double>& co,
            vector<double>& val,
			double tol,
			double& xmin)
{
	double f1, f2, x0, x1, x2, x3;

	x0 = ax;							// ４点 x0,x1,x2,x3 を更新していく
	x1 = ax + C * (bx - ax);
	x2 = ax + R * (bx - ax); 
	x3 = cx;

	if(abs(cx-bx) > abs(bx-ax)){
		x1=bx;
		x2=bx + C*(cx-bx);
	}else{
		x2=bx;
		x1=bx - C*(bx-ax);
	}

	val(0) = x1;
    f1 = function2d(co,val);
	val(0) = x2;
    f2 = function2d(co,val);

	while(fabs(x3 - x0) > tol * (fabs(x1) + fabs(x2))){	// 収束判定
		if(f2 < f1){								// 場合分けの一方
			SHFT3(x0, x1, x2, R * x1 + C * x3)	// 各点の更新
			val(0)=x2;
            SHFT2(f1, f2, function2d(co,val))				// 関数を評価x2
		}else{									// 場合分けのもう一方
			SHFT3(x3, x2, x1, R * x2 + C * x0)
			val(0)=x1;
            SHFT2(f2, f1, function2d(co,val))				// 関数を評価 x1
		}
	}

	if(f1 < f2){				// 完成。最新の２点のうち良い方を返す
		xmin = x1;
		return f1;
	}else{
		xmin = x2;
		return f2;
	}
}

double optimization::brent(
			double ax,
			double bx,
			double cx,
			vector<double>& co,
			vector<double>& val,
			double (*f)(vector<double>&,vector<double>&),
			double tol,
			double& xmin)
{
	int iter;
	double a, b, d, etemp, fu, fv, fw, fx, p, q, r, tol1, tol2, u, v, w, x, xm;
	double e = 0.0;						/* 前々回の更新量 */

	if(ax < cx){							/* a < b にする */
		a = ax;
		b = cx;
	}else{
		a = cx;
		b = ax;
	}

	x = w = v = bx;						/* 初期化 */
	fw = fv = fx = (*f)(co,val);

	for(iter = 1; iter <= ITMAX; iter++)	/* 主ループ */
	{
		xm = 0.5 * (a + b);
		tol1 = tol * fabs(x) + ZEPS;
		tol2 = 2.0 * tol1;
		if(fabs(x - xm) <= (tol2 - 0.5 * (b - a)))	/* 収束判定 */
		{
			xmin = x;					/* 最良の値を返す */
			return fx;
		}
		if(fabs(e) > tol1)				/* 放物線補間してみる */
		{
			r = (x - w) * (fx - fv);
			q = (x - v) * (fx - fw);
			p = (x - v) * q - (x - w) * r;
			q = 2.0 * (q - r);
			if(q > 0.0)	p = -p;
			q = fabs(q);
			etemp = e;
			e = d;
			if(fabs(p) >= fabs(0.5 * q * etemp)
				|| p <= q * (a - x)
				|| p >= q * (b - x))	/* 放物線補間の適否の検査 */
			{
				e = (x >= xm)? a - x: b - x;
				d = C * e;			/* 放物線補間は不適。大きい方の区間を */
										/* 黄金分割 */
			}else{
				d = p / q;				/* 放物線補間を採択する */
				u = x + d;
				if(u - a < tol2 || b - u < tol2)	d = sign(tol1, xm - x);
			}
		}else{
			e = (x >= xm)? a - x: b - x;
			d = C * e;
		}
		//u = x + ((fabs(d) >= tol1)? d: sign(tol1, d));
		val(0) = x + ((fabs(d) >= tol1)? d: sign(tol1, d));
		fu = (*f)(co,val);					/* 主ループでの関数値評価はここだけ */
		if(fu <= fx){
			if(u >= x)	a = x;
			else		b = x;
			SHFT3(v, w, x, u);
			SHFT3(fv, fw, fx, fu);
		}else{
			if(u < x)	a = u;
			else		b = u;
			if(fu <= fw || w == x)
			{
				v = w;
				w = u;
				fv = fw;
				fw = fu;
			}
			else if(fu <= fv || v == x || v == w)
			{
				v = u;
				fv = fu;
			}
		}
	}
	//fprintf(stderr, "Error : Too many iterations in brent.\n");
	xmin = x;

	return fx;
}

/*
Nelder-Mead の滑降シンプレックス法による関数 funk(x) の多次元の最小化。
x[ ] は ndim 次元のベクトル。入力する行列 p[ ][ ] の ndim+1 個の行は、出発点
でのシンプレックスの頂点の座標を表す ndim 次元のベクトル。入力するベクトル
ftol は関数値（極小点の座標ではない！）の収束を判定するための相対許容値。
戻り時の p と y は、最終位置での ndim+1 個の頂点の座標と関数値（どの関数値も
最小の関数値との相対的な外れが ftol 以内）。nfunk は関数の評価回数。
*/
void optimization::amoeba(
	matrix<double>& p,
	vector<double>& co,
	vector<double>& y,
	int ndim,
	double ftol,
	double (*funk)(vector<double>& co,vector<double>&),
	int& nfunk)
{
	int i, ihi, ilo, inhi, j, mpts = ndim + 1;
	double rtol, sum, swap, ysave, ytry;
	boost::numeric::ublas::vector<double> psum(ndim);

	for(j = 0; j < mpts; j++){
		double ppp[3];
		ppp[0]=p(j,0);ppp[1]=p(j,1);ppp[2]=p(j,2);
		y(j) = (*funk)(co,static_cast<boost::numeric::ublas::vector<double>>(row(p,j)));
	}
	//psum = vector(ndim);ublas::matrix
	nfunk = 0;
	for(j = 0; j < ndim; j++)
	{
		sum = 0.0;
		for(i = 0; i < mpts; i++)	sum += p(i,j);
		psum[j] = sum;
	}
	for(;;)
	{
		ilo = 0;
/* まずシンプレックスの頂点についてループし、最悪、最悪の次、最良の点を調べる。*/
		if(y(0) > y(1))
		{
			inhi = 1;
			ihi = 0;
		}
		else
		{
			inhi = 0;
			ihi = 1;
		}
		for(i = 0; i < mpts; i++)
		{
			if(y(i) <= y(ilo))	ilo = i;
			if(y(i) > y(ihi))
			{
				inhi = ihi;
				ihi = i;
			}
			else if(y(i) > y(inhi) && i != ihi)	inhi = i;
		}
		rtol = 2.0 * fabs(y(ihi) - y(ilo)) / (fabs(y(ihi)) + fabs(y(ilo)));

/* 関数値の最大の比を求め、これが十分小さいなら終了。*/
		if(rtol < ftol)				/* 戻る際には最良の点を頭に持って行く */
		{
			SWAP(y(i), y(ilo));
			for(i = 0; i < ndim; i++)	SWAP(p(0,i), p(ilo,i));
			break;
		}
		if(nfunk >= NMAX)
		{
			printf("Process Stop : NMAX(=%d) exceeded.\n", NMAX);
			SWAP(y(0), y(ilo));
			for(i = 0; i < ndim; i++)	SWAP(p(0,i), p(ilo,i));
			break;
		}
		nfunk += 2;
/* 新しい反復を始める。まず最悪の点を残りの点の重心の反対側に対称移動する。*/
		ytry = amotry(p,co, y, psum, ndim, funk, ihi, -1.0);
		if(ytry <= y(ilo))
		{
/* 現在の最良の点より良くなったので、さらに２倍だけ進んでみる。*/
			ytry = amotry(p,co, y, psum, ndim, funk, ihi, 2.0);
		}
		else if(ytry >= y(inhi))
		{
/* 対称移動した点は２番目に悪い点よりも悪いので１次元の収縮を試みる。*/
			ysave = y(ihi);
			ytry = amotry(p,co, y, psum, ndim, funk, ihi, 0.5);
			if(ytry >= ysave)
			{
/* それでも良くないなら全体を最良点に向かって収縮。*/
				for(i = 0; i < mpts; i++)
				{
					if(i != ilo)
					{
						for(j = 0; j < ndim; j++)
							p(i,j) = psum[j] = 0.5 * (p(i,j) + p(ilo,j));
						y(i) = (*funk)(co,psum);
					}
				}
				nfunk += ndim;			/* 関数の評価回数を数える。 */
				for(j = 0; j < ndim; j++)		/* psum を再計算。 */
				{
					sum = 0.0;
					for(i = 0; i < mpts; i++)	sum += p(i,j);
					psum[j] = sum;
				}
			}
		}
		else	--nfunk;				/* 評価回数を補正。 */
	}
}

double optimization::amotry(
	matrix<double>& p,
	vector<double>& co,
	vector<double>& y,
	vector<double>& psum,
	int ndim,
	double (*funk)(vector<double>& co,vector<double>&),
	int ihi,
	double fac)
{
	int j;
	double fac1, fac2, ytry;

	boost::numeric::ublas::vector<double> ptry(ndim);
	fac1 = (1.0 - fac) / ndim;
	fac2 = fac1 - fac;

	for(j = 0; j < ndim; j++)
		ptry(j) = psum[j] * fac1 - p(ihi,j) * fac2;

	ytry = (*funk)(co,ptry);				/* 新しい点で関数評価 */
	if(ytry < y(ihi))					/* 新しい点の方が良ければ元の最悪の */
	{									/* 捨てて置き換える。 */
		y(ihi) = ytry;
		for(j = 0; j < ndim; j++)
		{
			psum[j] += ptry(j) - p(ihi,j);
			p(ihi,j) = ptry(j);
		}
	}

	return ytry;
}


double optimization::function2d(vector<double>& co,vector<double>& val)
{
	using namespace define;
	double a[2],ec,time;
	vector<double> wref(2),wrefdot(wref),wrefddot(wref);
    int step;
    double dt;

	time = val(0);
    //control2d::GenerateReference(time,wref,wrefdot,wrefddot);//近似式の作成を
    step = (int)(time/SAMPLING_TIME);
    dt = time-(double)step/SAMPLING_TIME;

    wref(0) = datalogptr[10][step]+dt/SAMPLING_TIME
                *(datalogptr[10][step+1]-datalogptr[10][step]);
    wref(1) = datalogptr[18][step]+dt/SAMPLING_TIME
                *(datalogptr[18][step+1]-datalogptr[18][step]);
    a[0] = wref(0) - co(0);
	a[1] = wref(1) - co(1);
	ec = sqrt( (a[0]*a[0])+(a[1]*a[1]) );

	return ec;
}

double optimization::function3d(vector<double>& co,vector<double>& val)
{
	using namespace define;
	double a[3],ec,time;
	vector<double> wref(NUM_DOF),wrefdot(wref),wrefddot(wref);

	time = val(0);
    //(*control3d::GenR)(time,wref,wrefdot,wrefddot); ////////////errorderukara kesita dake !!!
	a[0] = wref(0) - co(0);
	a[1] = wref(1) - co(1);
	a[2] = wref(2) - co(2);
	ec = sqrt( (a[0]*a[0])+(a[1]*a[1])+(a[2]*a[2]) );

	return ec;
}
optimization::optimization    (std::vector<std::vector<double>> &datalog)
    :datalogptr(datalog){

}
