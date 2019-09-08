//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ClSignal.h"
#include <stdlib.h>
#include <math.h>
//---------------------------------------------------------------------------
#define SWAP(a, b) tempr = (a);	(a) = (b); (b) = tempr;
//---------------------------------------------------------------------------
//Sort function (not in Signal class)
//---------------------------------------------------------------------------
int abs_sort_ascending(const void *a, const void *b)
{
    complex<double> aa = *(complex<double> *) a;
    complex<double> bb = *(complex<double> *) b;
    if(abs(aa) == abs(bb)) return 0;
    else if(abs(aa) > abs(bb)) return 1;
    else return -1;
}
//---------------------------------------------------------------------------
int abs_sort_descending(const void *a, const void *b)
{
    complex<double> aa = *(complex<double> *) a;
    complex<double> bb = *(complex<double> *) b;
    if(abs(aa) == abs(bb)) return 0;
    else if(abs(aa) > abs(bb)) return -1;
    else return 1;
}
//---------------------------------------------------------------------------
int real_sort_ascending(const void *a, const void *b)
{
    complex<double> aa = *(complex<double> *) a;
    complex<double> bb = *(complex<double> *) b;
    if(real(aa) == real(bb)) return 0;
    else if(real(aa) > real(bb)) return 1;
    else return -1;
}
//---------------------------------------------------------------------------
int real_sort_descending(const void *a, const void *b)
{
    complex<double> aa = *(complex<double> *) a;
    complex<double> bb = *(complex<double> *) b;
    if(real(aa) == real(bb)) return 0;
    else if(real(aa) > real(bb)) return -1;
    else return 1;
}
//---------------------------------------------------------------------------
//Constructor
//---------------------------------------------------------------------------
BSignal::BSignal(void)
{
    Point = NULL;
    NumPoints = 0;
    FrequencySampling = 1;
}
//---------------------------------------------------------------------------
BSignal::BSignal(int nPoints)
{
    NumPoints = 0;
    Point = NULL;
    SetNumPoints(nPoints);
    FrequencySampling = 1;
}
//---------------------------------------------------------------------------
BSignal::BSignal(const BSignal& s)
{
    NumPoints = 0;
    Point = NULL;
    *this = s;
}
//---------------------------------------------------------------------------
BSignal::BSignal(const BSignal& s, int count)
{
    NumPoints = 0;
    Point = NULL;
    SetNumPoints(count);
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = s.Point[i];
    }
    FrequencySampling = s.FrequencySampling;
}
//---------------------------------------------------------------------------
BSignal::BSignal(const BSignal& s, int start, int count)
{
    NumPoints = 0;
    Point = NULL;
    SetNumPoints(count);
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = s.Point[start + i];
    }
    FrequencySampling = s.FrequencySampling;
}
//---------------------------------------------------------------------------
//Destructor
//---------------------------------------------------------------------------
BSignal::~BSignal(void)
{
    if(Point != NULL) delete[] Point;
}
//---------------------------------------------------------------------------
//Operators
//---------------------------------------------------------------------------
complex<double>& BSignal::operator () (int index)
{
    if(Point == NULL)
    {
        throw;
    }
    return Point[index];
}
//---------------------------------------------------------------------------
const complex<double>& BSignal::operator () (int index) const
{
    if(Point == NULL)
    {
        throw;
    }
    return Point[index];
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator = (const BSignal& s)
{
    SetNumPoints(s.NumPoints);
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i]  = s.Point[i];
    }
    FrequencySampling = s.FrequencySampling;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator = (complex<double> d)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = d;
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator += (const BSignal& s)
{
    if(NumPoints != s.NumPoints)
    {
        throw;
    }
    *this = *this + s;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator += (complex<double> d)
{
    *this = *this + d;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator -= (const BSignal& s)
{
    if(NumPoints != s.NumPoints)
    {
        throw;
    }
    *this = *this - s;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator -= (complex<double> d)
{
    *this = *this - d;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator *= (const BSignal& s)
{
    if(NumPoints != s.NumPoints)
    {
        throw;
    }
    *this = *this * s;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator *= (complex<double> d)
{
    *this = *this * d;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::operator /= (complex<double> d)
{
    if(d == 0.0)
    {
        throw;
    }
    *this = *this / d;
    return *this;
}
//---------------------------------------------------------------------------
bool operator == (const BSignal& s1, const BSignal& s2)
{
    if(s1.NumPoints != s2.NumPoints) return false;
    for(int i = 0; i < s1.NumPoints; i++)
    {
        if(s1.Point[i] != s2.Point[i]) return false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool operator != (const BSignal& s1, const BSignal& s2)
{
    if(s1.NumPoints != s2.NumPoints) return true;
    for(int i = 0; i < s1.NumPoints; i++)
    {
        if(s1.Point[i] != s2.Point[i]) return true;
    }
    return false;
}
//---------------------------------------------------------------------------
BSignal operator + (const BSignal& s1, const BSignal& s2)
{
    if(s1.NumPoints != s2.NumPoints)
    {
        throw;
    }
    BSignal sout(s1.NumPoints);

    for(int i = 0; i < s1.NumPoints; i++)
    {
        sout.Point[i] = s1.Point[i] + s2.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator + (const BSignal& s, complex<double> d)
{
    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] + d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator + (complex<double> d, const BSignal& s)
{
    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] + d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator - (const BSignal& s)
{
    BSignal sout(s);

    for(int i = 0; i < sout.NumPoints; i++)
    {
        sout.Point[i] = -sout.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator - (const BSignal& s1, const BSignal& s2)
{
    if(s1.NumPoints != s2.NumPoints)
    {
        throw;
    }

    BSignal sout(s1.NumPoints);

    for(int i = 0; i < s1.NumPoints; i++)
    {
        sout.Point[i] = s1.Point[i] - s2.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator - (const BSignal& s, complex<double> d)
{
    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] - d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator - (complex<double> d, const BSignal& s)
{
    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] - d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator * (const BSignal& s1, const BSignal& s2)
{
    if((s1.Point == NULL) || (s2.Point == NULL))
    {
        throw;
    }
    if(s1.NumPoints != s2.NumPoints)
    {
        throw;
    }

    BSignal sout(s1.NumPoints);

    for(int i = 0; i < s1.NumPoints; i++)
    {
        sout.Point[i] = s1.Point[i] * s2.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator * (const BSignal& s, complex<double> d)
{
    if(s.Point == NULL)
    {
        throw;
    }

    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] * d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator * (complex<double> d, const BSignal& s)
{
    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] * d;
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal operator / (const BSignal& s, complex<double> d)
{
    if(s.Point == NULL)
    {
        throw;
    }
    if(d == 0.0)
    {
        throw;
    }

    BSignal sout(s.NumPoints);

    for(int i = 0; i < s.NumPoints; i++)
    {
        sout.Point[i] = s.Point[i] / d;
    }
    return sout;
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
double BSignal::GetFrequencySampling(void) const
{
    return FrequencySampling;
}
//---------------------------------------------------------------------------
int BSignal::GetNumPoints(void) const
{
    return NumPoints;
}
//---------------------------------------------------------------------------
void BSignal::Set(float* pt)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i]  = pt[i];
    }
}
//---------------------------------------------------------------------------
void BSignal::Set(double* pt)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i]  = pt[i];
    }
}
//---------------------------------------------------------------------------
void BSignal::Set(complex<double>* pt)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i]  = pt[i];
    }
}
//---------------------------------------------------------------------------
void BSignal::SetFrequencySampling(double d)
{
    FrequencySampling = d;
}
//---------------------------------------------------------------------------
inline void BSignal::SetNumPoints(int n)
{
    if(NumPoints != n)
    {
        if(n > NumPoints)
        {
            delete[] Point;
            Point = new complex<double>[n];
        }
        if(n > 0)
        {
            NumPoints = n;
        }
        else
        {
            delete[] Point;
            Point = NULL;
            NumPoints = 0;
        }
    }
}
//---------------------------------------------------------------------------
BSignal BSignal::SubSignal(int start, int lenght) const
{
    BSignal stemp(lenght);

    stemp.FrequencySampling = FrequencySampling;
    for(int i = 0; i < lenght; i++)
    {
        stemp.Point[i] = Point[start + i];
    }
    return stemp;
}
//---------------------------------------------------------------------------
//Statistic
//---------------------------------------------------------------------------
double BSignal::AbsMaximum(void) const
{
    double dMax = 0;

    if(NumPoints > 0)
    {
        dMax = abs(Point[0]);
        for(int i = 1; i < NumPoints; i++)
        {
            if(abs(Point[i]) > dMax) dMax = abs(Point[i]);
        }
    }
    else
    {
        throw;
    }
    return dMax;
}
//---------------------------------------------------------------------------
double BSignal::AbsMean(void) const
{
    double dMean = 0;

    if(NumPoints > 0)
    {
        for(int i = 0; i < NumPoints; i++)
        {
            dMean += abs(Point[i]);
        }
        dMean /= NumPoints;
    }
    else
    {
        throw;
    }
    return dMean;
}
//---------------------------------------------------------------------------
double BSignal::AbsMeanPeak(int step) const
{
    double dMaxPeak;
    double dMeanPeak = 0;
    int count = 0;

    if(NumPoints > 0)
    {
        dMaxPeak = abs(Point[0]);
        for(int i = 0; i < NumPoints; i++)
        {
            if(count == step)
            {
                count = 0;
                dMeanPeak += dMaxPeak;
                dMaxPeak = abs(Point[i]);
            }
            else
            {
                if(abs(Point[i]) > dMaxPeak) dMaxPeak = abs(Point[i]);
            }
            count++;
        }
        dMeanPeak /= ((double)NumPoints / step);
    }
    return dMeanPeak;
}
//---------------------------------------------------------------------------
double BSignal::AbsMedian(void) const
{
    if(NumPoints == 0)
    {
        throw;
    }
    int index;
    BSignal stemp(*this);

    stemp.AbsSortAscending();
    index = stemp.NumPoints / 2;
    if((stemp.NumPoints % 2) == 0)
    {
        return 0.5 * abs(stemp.Point[index]) + abs(stemp.Point[index + 1]);
    }
    else
    {
        return abs(stemp.Point[index]);
    }
}
//---------------------------------------------------------------------------
double BSignal::AbsMinimum(void) const
{
    double dMin = 0;

    if(NumPoints > 0)
    {
        dMin = abs(Point[0]);
        for(int i = 1; i < NumPoints; i++)
        {
            if(abs(Point[i]) < dMin) dMin = abs(Point[i]);
        }
    }
    else
    {
        throw;
    }
    return dMin;
}
//---------------------------------------------------------------------------
double BSignal::AbsMoment(int order) const
{
    if(order < 1)
    {
        throw;
    }

    double moment = 0;
    double ave = AbsMean();

    for(int i = 0; i < NumPoints; i++)
    {
        moment += pow(abs(Point[i]) - ave, order);
    }
    return moment / (double)NumPoints;
}
//---------------------------------------------------------------------------
double BSignal::AbsStdDev(void) const
{
    return sqrt(AbsVariance());
}
//---------------------------------------------------------------------------
double BSignal::AbsVariance(void) const
{
    double var = 0;
    double ave = AbsMean();

    for(int i = 0; i < NumPoints; i++)
    {
        var += square(abs(Point[i]) - ave);
    }
    return var / (double)NumPoints;
}
//---------------------------------------------------------------------------
double BSignal::RealMaximum(void) const
{
    double dMax = 0;

    if(NumPoints > 0)
    {
        dMax = real(Point[0]);
        for(int i = 1; i < NumPoints; i++)
        {
            if(real(Point[i]) > dMax) dMax = real(Point[i]);
        }
    }
    else
    {
        throw;
    }
    return dMax;
}
//---------------------------------------------------------------------------
double BSignal::RealMean(void) const
{
    double dMean = 0;

    if(NumPoints > 0)
    {
        for(int i = 0; i < NumPoints; i++)
        {
            dMean += real(Point[i]);
        }
        dMean /= NumPoints;
    }
    else
    {
        throw;
    }
    return dMean;
}
//---------------------------------------------------------------------------
double BSignal::RealMeanPeak(int step) const
{
    double dMaxPeak;
    double dMeanPeak = 0;
    int count = 0;

    if(NumPoints > 0)
    {
        dMaxPeak = real(Point[0]);
        for(int i = 0; i < NumPoints; i++)
        {
            if(count == step)
            {
                count = 0;
                dMeanPeak += dMaxPeak;
                dMaxPeak = real(Point[i]);
            }
            else
            {
                if(real(Point[i]) > dMaxPeak) dMaxPeak = real(Point[i]);
            }
            count++;
        }
        dMeanPeak /= ((double)NumPoints / step);
    }
    return dMeanPeak;
}
//---------------------------------------------------------------------------
double BSignal::RealMedian(void) const
{
    if(NumPoints == 0)
    {
        throw;
    }
    int index;
    BSignal stemp(*this);

    stemp.RealSortAscending();
    index = stemp.NumPoints / 2;
    if((stemp.NumPoints % 2) == 0)
    {
        return 0.5 * real(stemp.Point[index]) + real(stemp.Point[index + 1]);
    }
    else
    {
        return real(stemp.Point[index]);
    }
}
//---------------------------------------------------------------------------
double BSignal::RealMinimum(void) const
{
    double dMin = 0;

    if(NumPoints > 0)
    {
        dMin = real(Point[0]);
        for(int i = 1; i < NumPoints; i++)
        {
            if(real(Point[i]) < dMin) dMin = real(Point[i]);
        }
    }
    else
    {
        throw;
    }
    return dMin;
}
//---------------------------------------------------------------------------
double BSignal::RealMoment(int order) const
{
    if(order < 1)
    {
        throw;
    }

    double moment = 0;
    double ave = RealMean();

    for(int i = 0; i < NumPoints; i++)
    {
        moment += pow(real(Point[i]) - ave, order);
    }
    return moment / (double)NumPoints;
}
//---------------------------------------------------------------------------
double BSignal::RealStdDev(void) const
{
    return sqrt(RealVariance());
}
//---------------------------------------------------------------------------
double BSignal::RealVariance(void) const
{
    double var = 0;
    double ave = RealMean();

    for(int i = 0; i < NumPoints; i++)
    {
        var += square(real(Point[i]) - ave);
    }
    return var / (double)NumPoints;
}
//---------------------------------------------------------------------------
double BSignal::RMS(void) const
{
    double dRMS = 0;

    if(NumPoints > 0)
    {
        for(int i = 0; i < NumPoints; i++)
        {
            dRMS += norm(Point[i]);
        }
        dRMS = sqrt(dRMS / (double)NumPoints);
    }
    else
    {
        throw;
    }
    return dRMS;
}
//---------------------------------------------------------------------------
//Sort
//---------------------------------------------------------------------------
BSignal& BSignal::AbsSortAscending(void)
{
    if(NumPoints > 0)
    {
        qsort((void *) Point, NumPoints, sizeof(complex<double>), abs_sort_ascending);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::AbsSortDescending(void)
{
    if(NumPoints > 0)
    {
        qsort((void *) Point, NumPoints, sizeof(complex<double>), abs_sort_descending);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::RealSortAscending(void)
{
    if(NumPoints > 0)
    {
        qsort((void *) Point, NumPoints, sizeof(complex<double>), real_sort_ascending);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::RealSortDescending(void)
{
    if(NumPoints > 0)
    {
        qsort((void *) Point, NumPoints, sizeof(complex<double>), real_sort_descending);
    }
    return *this;
}
//---------------------------------------------------------------------------
//Time domain
//---------------------------------------------------------------------------
BSignal& BSignal::AutoConvolve(void)
{
    if (NumPoints == 0)
    {
        throw;
    }
    FFT();
    for (int i = 0; i < NumPoints; i++)
    {
        Point[i] = Point[i] * Point[i];
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::AutoCorrelate(void)
{
    if (NumPoints == 0)
    {
        throw;
    }
    FFT();
    for (int i = 0; i < NumPoints; i++)
    {
        Point[i] = Point[i] * conj(Point[i]);
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal Convolve(const BSignal& s1, const BSignal& s2)
{
    if((s1.NumPoints == 0) || (s2.NumPoints == 0))
    {
        throw;
    }
    if(s2.NumPoints > s1.NumPoints)
    {
        throw;
    }
    int nPoints1 = s1.NumPoints;
    int nPoints2 = s2.NumPoints;
    BSignal stemp1(s1);
    BSignal stemp2(nPoints1);

    stemp2 = 0;
    for(int i = 0; i < nPoints2; i++)
    {
        stemp2.Point[i] = s2.Point[i];
    }
	for (int i = 0; i < (nPoints2 - 1) / 2; i++)
    {
        stemp2.Point[nPoints1 - i - 1] = stemp2.Point[nPoints2 - i - 1];
    }
    stemp1.FFT();
    stemp2.FFT();
    BSignal sout = stemp1 * stemp2;
    sout.InverseFFT();
    return sout;
}
//---------------------------------------------------------------------------
BSignal Correlate(const BSignal& s1, const BSignal& s2)
{
    if((s1.NumPoints == 0) || (s2.NumPoints == 0))
    {
        throw;
    }
    if(s2.NumPoints != s1.NumPoints)
    {
        throw;
    }
    BSignal stemp1(s1);
    BSignal stemp2(s2);
    BSignal sout(s1.NumPoints);

    stemp1.FFT();
    stemp2.FFT();
    for(int i = 0; i < stemp1.NumPoints; i++)
    {
        sout.Point[i] = stemp1.Point[i] * conj(stemp2.Point[i]);
    }
    sout.InverseFFT();
    return sout;
}
//---------------------------------------------------------------------------
BSignal Deconvolve(const BSignal& s1, const BSignal& s2)
{
    if((s1.NumPoints == 0) || (s2.NumPoints == 0))
    {
        throw;
    }
    if(s2.NumPoints > s1.NumPoints)
    {
        throw;
    }
    int nPoints1 = s1.NumPoints;
    int nPoints2 = s2.NumPoints;
    BSignal stemp1(s1);
    BSignal stemp2(nPoints1);
    BSignal sout(nPoints1);

    stemp2 = 0;
    for(int i = 0; i < nPoints2; i++)
    {
        stemp2.Point[i] = s2.Point[i];
    }
	for (int i = 0; i < (nPoints2 - 1) / 2; i++)
    {
        stemp2.Point[nPoints1 - i - 1] = stemp2.Point[nPoints2 - i - 1];
    }
    stemp1.FFT();
    stemp2.FFT();
    for(int i = 0; i < stemp1.NumPoints; i++)
    {
        double ampl = abs(stemp2.Point[i]);

        if(ampl == 0)
        {
            throw;
        }
        ampl = ampl * ampl;
        sout.Point[i] = stemp1.Point[i] * conj(stemp2.Point[i]) / ampl;
    }
    sout.InverseFFT();
    return sout;
}
//---------------------------------------------------------------------------
//Frequency domain
//---------------------------------------------------------------------------
BSignal& BSignal::AutoPowerSpectrum(void)
{
    if(NumPoints == 0)
    {
        throw;
    }
    FFT();
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] *= conj(Point[i]);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::Cepstrum(void)
{
    FFT().FFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal CrossPowerSpectrum(const BSignal& s1, const BSignal& s2)
{
    if((s1.NumPoints == 0) || (s2.NumPoints == 0))
    {
        throw;
    }
    if(s2.NumPoints != s1.NumPoints)
    {
        throw;
    }
    BSignal stemp1(s1);
    BSignal stemp2(s2);
    BSignal sout(s1.NumPoints);

    stemp1.FFT();
    stemp2.FFT();
    for(int i = 0; i < stemp1.NumPoints; i++)
    {
        sout.Point[i] = stemp1.Point[i] * stemp2.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal CrossSpectrum(const BSignal& s1, const BSignal& s2)
{
    if((s1.NumPoints == 0) || (s2.NumPoints == 0))
    {
        throw;
    }
    if(s2.NumPoints != s1.NumPoints)
    {
        throw;
    }
    BSignal stemp1(s1);
    BSignal stemp2(s2);
    BSignal sout(s1.NumPoints);

    stemp1.FFT();
    stemp2.FFT();
    for(int i = 0; i < stemp1.NumPoints; i++)
    {
        sout.Point[i] = conj(stemp1.Point[i]) * stemp2.Point[i];
    }
    return sout;
}
//---------------------------------------------------------------------------
BSignal FFT(const BSignal& s)
{
    BSignal sout(s);
    sout.FFT();
    return sout;
}
//---------------------------------------------------------------------------
BSignal InverseFFT(const BSignal& s)
{
    BSignal sout(s);
    sout.InverseFFT();
    return sout;
}
//---------------------------------------------------------------------------
BSignal& BSignal::FFT(void)
{
    if(NumPoints == 0)
    {
        throw;
    }
	double escal;

	escal = double(NumPoints) / 2;
	if ( fabs((pow(2., log10(NumPoints) / log10(2.) ) - NumPoints )) >= 0.01 )
    {
		throw;
    }
    double* data = new double[2 * NumPoints];

    for(int i = 0; i < NumPoints; i++)
    {
        data[2 * i] = real(Point[i]);
        data[2 * i + 1] = imag(Point[i]);
    }
	four1(data, NumPoints, 1);
    for(int i = 0; i < NumPoints; i++)
    {
        complex<double> value(data[2 * i], data[2 * i + 1]);
        Point[i] = value;
    }
	for(int i = 0; i < NumPoints; i++)
    {
	    Point[i] /= escal;
	}
    delete data;
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::InverseFFT(void)
{
    if(NumPoints == 0)
    {
        throw;
    }
	if ( fabs((pow(2., log10(NumPoints) / log10(2.) ) - NumPoints )) >= 0.01 )
    {
		throw;
    }
    double* data = new double[2 * NumPoints];

    for(int i = 0; i < NumPoints; i++)
    {
        data[2 * i] = real(Point[i]);
        data[2 * i + 1] = imag(Point[i]);
    }
	four1(data, NumPoints, -1);
    for(int i = 0; i < NumPoints; i++)
    {
        complex<double> value(data[2 * i], data[2 * i + 1]);
        Point[i] = value / 2.0;
    }
    delete data;
    return *this;
}
//---------------------------------------------------------------------------
// Others
//---------------------------------------------------------------------------
BSignal& BSignal::Decimate(int factor, bool average)
{
    if(factor <= 0)
    {
        throw;
    }
    int size = 1 + (NumPoints - 1) / factor;
    BSignal stemp(*this);

    FrequencySampling /= factor;
    SetNumPoints(size);
    if(average)
    {
        for(int i = 0; i < NumPoints; i++)
        {
            Point[i] = 0;
            for(int j = 0; j < factor; j++)
            {
                Point[i] += stemp.Point[i * factor + j];
            }
            Point[i] /= factor;
        }
    }
    else
    {
        for(int i = 0; i < NumPoints; i++)
        {
            Point[i] = stemp.Point[i * factor];
        }
    }
    return *this;
}
//---------------------------------------------------------------------------
//Filters
//---------------------------------------------------------------------------
BSignal& BSignal::BandPassFilter(double dFreq1, double dFreq2)
{
    int iStart = dFreq1 * NumPoints / FrequencySampling;
    int iEnd = dFreq2 * NumPoints / FrequencySampling;

    FFT();
    for(int i = 0; i < iStart; i++)
    {
        Point[i] = 0;
    }
    for(int i = iEnd + 1; i < NumPoints - iEnd; i++)
    {
        Point[i] = 0;
    }
    for(int i = NumPoints - iStart + 1; i < NumPoints; i++)
    {
        Point[i] = 0;
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::BandStopFilter(double dFreq1, double dFreq2)
{
    int iStart = dFreq1 * NumPoints / FrequencySampling;
    int iEnd = dFreq2 * NumPoints / FrequencySampling;

    FFT();
    for(int i = iStart + 1; i < iEnd; i++)
    {
        Point[i] = 0;
    }
    for(int i = NumPoints - iEnd; i < NumPoints - iStart; i++)
    {
        Point[i] = 0;
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::HighPassFilter(double dFreq)
{
    int iCutoff = dFreq * NumPoints / FrequencySampling;

    FFT();
    for(int i = 0; i < iCutoff; i++)
    {
        Point[i] = 0;
    }
    for(int i = NumPoints - iCutoff; i < NumPoints; i++)
    {
        Point[i] = 0;
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::LowPassFilter(double dFreq)
{
    int iCutoff = dFreq * NumPoints / FrequencySampling;

    FFT();
    for(int i = iCutoff + 1; i < (NumPoints - iCutoff); i++)
    {
        Point[i] = 0;
    }
    InverseFFT();
    return *this;
}
//---------------------------------------------------------------------------
/*
BSignal& BSignal::EllipticBandPass(double dFreq1, double dFreq2)
{

}
//---------------------------------------------------------------------------
BSignal& BSignal::EllipticBandStop(double dFreq1, double dFreq2)
{

}
//---------------------------------------------------------------------------
BSignal& BSignal::EllipticHighPass(double dFreq)
{

}
//---------------------------------------------------------------------------
BSignal& BSignal::EllipticLowPass(double dFreq)
{

}
*/
//---------------------------------------------------------------------------
//Windows
//---------------------------------------------------------------------------
BSignal& BSignal::BlackmanWindow(void)
{
    double aux = 2 * M_PI / NumPoints;

    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] *= (0.42 - 0.5 * cos(aux * i) + 0.08 * cos(2 * aux * i));
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::FlatTopWindow(void)
{
    double a0 = 0.2810639;
    double a1 = 0.5208972;
    double a2 = 0.1980399;

    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] *= (a0 - a1 * cos(2 * M_PI * i / NumPoints) + a2 * cos(4 * M_PI * i / NumPoints));
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::HammingWindow(void)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] *= (0.54 - 0.46 * cos(2 * M_PI * i / NumPoints));
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::HanningWindow(void)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] *= (0.5 - 0.5 * cos(2 * M_PI * i / NumPoints));
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::KaiserWindow(double beta)
{
    double aux;

    for(int i = 0; i < NumPoints; i++)
    {
        aux = fabs(1 - 2 * (double)i / NumPoints);
        Point[i] *= (besselI0(beta * sqrt(1 - aux * aux)) / besselI0(beta));
     }
     return *this;
}
//---------------------------------------------------------------------------
//Waves
//---------------------------------------------------------------------------
BSignal& BSignal::ImpulseWave(double ampl, int index)
{
    for(int i = 0; i < NumPoints; i++)
    {
        if(i == index)
        {
            Point[i] = ampl;
        }
        else
        {
            Point[i] = 0;
        }
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::PulseWave(double ampl, int delay, int width)
{
    for(int i = 0; i < NumPoints; i++)
    {
        if((i >= delay) && (i < (delay + width)))
        {
            Point[i] = ampl;
        }
        else
        {
            Point[i] = 0;
        }
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::RampWave(double ampl, double first, double last)
{
    if(NumPoints == 0)
    {
        return *this;
    }
    if(NumPoints == 1)
    {
        Point[0] = first;
        return *this;
    }
    double dx = (last - first) / (NumPoints - 1);
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = first + (i * dx);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::SawtoothWave(double ampl, double freq, double phase)
{
    double f;

    for(int i = 0; i < NumPoints; i++)
    {
        int p = phase + (freq * 360.0 * i);

        if ((p % 360) < 180)
        {
            f = double(p % 360) / 180;
        }
        else
        {
            f = (double(p % 360) / 180) - 2;
        }
        Point[i] = ampl * f;
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::SquareWave(double ampl, double freq, double phase)
{
    for(int i = 0; i < NumPoints; i++)
    {
        double f;
        int p = phase + (freq * 360.0 * i);

        if ((p % 360) < 180)
        {
            f = 1;
        }
        else
        {
            f = -1;
        }
        Point[i] = ampl * f;
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::SineWave(double ampl)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = ampl * sin(2 * M_PI * i / NumPoints);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::SineWave(double ampl, double freq, double phase)
{
    for(int i = 0; i < NumPoints; i++)
    {
        Point[i] = ampl * sin(freq * i + phase);
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::TriangularWave(double ampl)
{
    for(int i = 0; i < NumPoints; i++)
    {
        if(NumPoints % 2)
        {
            Point[i] = ampl * (1 - abs(2 * i - NumPoints + 1)) / NumPoints;
        }
        else
        {
            Point[i] = ampl * (1 - abs(2 * i - NumPoints)) / NumPoints;
        }
    }
    return *this;
}
//---------------------------------------------------------------------------
BSignal& BSignal::TriangularWave(double ampl, double freq, double phase)
{
    for(int i = 0; i < NumPoints; i++)
    {
        double f;
        int p = phase + (freq * 360.0 * i);

        if ((p % 360) < 90)
        {
            f = 2 * (double)(p % 360) / 180;
        }
        else if ((p % 360) < 270)
        {
            f = 2 * (1 - (double)(p % 360) / 180);
        }
        else
        {
            f = 2 * ((double)(p % 360) / 180 - 2);
        }
        Point[i] = ampl * f;
    }
    return *this;
}
//---------------------------------------------------------------------------
//Protected functions
//---------------------------------------------------------------------------
double BSignal::besselI0(double x)
{
	double ax, ans;
	double y;

	if ((ax = fabs(x)) < 3.75)
    {
		y = x / 3.75;
		y *= y;
		ans = 1.0 + y * (3.5156229 + y * (3.0899424 +
                                     y * (1.2067492 +
                                     y * (0.2659732 +
                                     y * (0.360768e-1 +
                                     y * 0.45813e-2)))));
	}
    else
    {
		y = 3.75 / ax;
		ans = (exp(ax) / sqrt(ax)) *
            (0.39894228 + y * (0.1328592e-1 +
                          y * (0.225319e-2 +
                          y * (-0.157565e-2 +
                          y * (0.916281e-2 +
                          y * (-0.2057706e-1 +
                          y * (0.2635537e-1 +
                          y * (-0.1647633e-1 +
                          y * 0.392377e-2))))))));
	}
	return ans;
}
//---------------------------------------------------------------------------
void BSignal::four1(double* data, unsigned long nn, int isign)
/*
	Substitui  data[2*nn] pela sua Transformada Discreta de Fourier,
    se "isign" eh 1; ou substitui data[2*nn] por "nn" vezes sua
    Transformada Inversa Discreta, se "isign" eh igual a -1.

	data e' um vetor complexo de tamanho "nn" ou, equivalentemente,
    um vetor real de tamanho "2*nn". "nn" DEVE ser um inteiro,
    potencia de 2 ( isso nao eh verificado ).
*/
{
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;

    n = nn << 1;
    j = 1;
    // Secao bit-reversal
    for ( i = 1; i < n; i+=2 )
    {
        if ( j > i )
        {
            // Troca 2 numeros complexos
            SWAP(data[j - 1], data[i - 1]);
            SWAP(data[j], data[i]);
        }
        m = n>>1;
        while ( (m >= 2) && (j > m))
        {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    // loop externo, executado log2 vezes
    while ( n > mmax )
    {
        istep = mmax << 1;
        // Inicia recorrencia trigonométrica
        theta = isign * (6.28318530717959 / mmax);
        wtemp = sin(0.5 * theta);
        wpr = -2.0 * wtemp * wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for ( m = 1; m < mmax; m += 2)
        {
            // Formula Danielson-Lanczos
            for ( i = m; i < n; i+=istep)
            {
                j = i + mmax;
                tempr = (float)(wr * data[j - 1]) - (float)(wi * data[j]);
                tempi = (float)(wr * data[j]) + (float)(wi * data[j - 1]);
                data[j - 1] = data[i - 1] - tempr;
                data[j] = data[i] - tempi;
                data[i - 1] += tempr;
                data[i] += tempi;
            }
            // recorrencia trigonometrica
            wr = (wtemp = wr) * wpr - wi * wpi + wr;
            wi = wi * wpr + wtemp * wpi + wi;
        }
        mmax = istep;
    }
}
//---------------------------------------------------------------------------
inline template<class T> T BSignal::square(T a)
{
    return a * a;
}
//---------------------------------------------------------------------------
#undef SWAP
//---------------------------------------------------------------------------

