//---------------------------------------------------------------------------
#ifndef BSignalH
#define BSignalH
//---------------------------------------------------------------------------
#include <complex.h>
//---------------------------------------------------------------------------
class BSignal
{
private:
    int NumPoints;
    complex<double>* Point;
    double FrequencySampling;

protected:
    static double besselI0(double x);
    static template<class T> T square(T a);
    static void four1(double* data, unsigned long nn, int isign);
public:
    //Constructors
    BSignal(void);
    BSignal(int nPoints);
    BSignal(const BSignal& s);
    BSignal(const BSignal& s, int count);
    BSignal(const BSignal& s, int start, int length);
    //Destructor
    ~BSignal(void);
    //Member operators
    complex<double>& operator () (int index);
    const complex<double>& operator () (int index) const;
    BSignal& operator = (const BSignal& s);
    BSignal& operator = (complex<double> d);
    BSignal& operator += (const BSignal& s);
    BSignal& operator += (complex<double> d);
    BSignal& operator -= (const BSignal& s);
    BSignal& operator -= (complex<double> d);
    BSignal& operator *= (const BSignal& s);
    BSignal& operator *= (complex<double> d);
    BSignal& operator /= (complex<double> d);
    //Non-member operators
    friend bool operator == (const BSignal& s1, const BSignal& s2);
    friend bool operator != (const BSignal& s1, const BSignal& s2);
    friend BSignal operator + (const BSignal& s1, const BSignal& s2);
    friend BSignal operator + (const BSignal& s, complex<double> d);
    friend BSignal operator + (complex<double> d, const BSignal& s);
    friend BSignal operator - (const BSignal& s);
    friend BSignal operator - (const BSignal& s1, const BSignal& s2);
    friend BSignal operator - (const BSignal& s, complex<double> d);
    friend BSignal operator - (complex<double> d, const BSignal& s);
    friend BSignal operator * (const BSignal& s1, const BSignal& s2);
    friend BSignal operator * (const BSignal& s, complex<double> d);
    friend BSignal operator * (complex<double> d, const BSignal& s);
    friend BSignal operator / (const BSignal& s, complex<double> d);
    //---------------------------------------------------
    //                                   Member functions
    //---------------------------------------------------
    int GetNumPoints(void) const;
    double GetFrequencySampling(void) const;
    void Set(float* pt);
    void Set(double* pt);
    void Set(complex<double>* pt);
    void SetFrequencySampling(double d);
    void SetNumPoints(int n);
    BSignal SubSignal(int start, int length) const;
    //Statistic
    double AbsMaximum(void) const;
    double AbsMean(void) const;
    double AbsMeanPeak(int step) const;
    double AbsMedian(void) const;
    double AbsMinimum(void) const;
    double AbsMoment(int order = 3) const;
    double AbsStdDev(void) const;
    double AbsVariance(void) const;
    double RealMaximum(void) const;
    double RealMean(void) const;
    double RealMeanPeak(int step) const;
    double RealMedian(void) const;
    double RealMinimum(void) const;
    double RealMoment(int order = 3) const;
    double RealStdDev(void) const;
    double RealVariance(void) const;
    double RMS(void) const;
    //Sort
    BSignal& AbsSortAscending(void);
    BSignal& AbsSortDescending(void);
    BSignal& RealSortAscending(void);
    BSignal& RealSortDescending(void);
    //Frequency domain
    BSignal& AutoPowerSpectrum(void);
    BSignal& Cepstrum(void);
    BSignal& FFT(void);
    BSignal& InverseFFT(void);
    //Time domain
    BSignal& AutoConvolve(void);
    BSignal& AutoCorrelate(void);
    //Others
    BSignal& Decimate(int factor = 2, bool average = false);
    //Filters
    BSignal& BandPassFilter(double dFreq1, double dFreq2);
    BSignal& BandStopFilter(double dFreq1, double dFreq2);
    BSignal& HighPassFilter(double dFreq);
    BSignal& LowPassFilter(double dFreq);
    BSignal& EllipticBandPassFilter(double dFreq1, double dFreq2);
    BSignal& EllipticBandStopFilter(double dFreq1, double dFreq2);
    BSignal& EllipticHighPassFilter(double dFreq);
    BSignal& EllipticLowPassFilter(double dFreq);
    //Windows
    BSignal& BlackmanWindow(void);
    BSignal& FlatTopWindow(void);
    BSignal& HammingWindow(void);
    BSignal& HanningWindow(void);
    BSignal& KaiserWindow(double beta = 4.86);
    //Waves
    BSignal& ImpulseWave(double ampl, int index);
    BSignal& PulseWave(double ampl, int delay, int width);
    BSignal& RampWave(double ampl, double first, double last);
    BSignal& SawtoothWave(double ampl, double freq, double phase);
    BSignal& SquareWave(double ampl, double freq, double phase);
    BSignal& SineWave(double ampl);
    BSignal& SineWave(double ampl, double freq, double phase);
    BSignal& TriangularWave(double ampl);
    BSignal& TriangularWave(double ampl, double freq, double phase);
    //---------------------------------------------------
    //                               Non-member functions
    //---------------------------------------------------
    //Time domain
    friend BSignal Convolve(const BSignal& s1, const BSignal& s2);
    friend BSignal Correlate(const BSignal& s1, const BSignal& s2);
    friend BSignal Deconvolve(const BSignal& s1, const BSignal& s2);
    //Frequency domain
    friend BSignal CrossPowerSpectrum(const BSignal& s1, const BSignal& s2);
    friend BSignal CrossSpectrum(const BSignal& s1, const BSignal& s2);
    friend BSignal FFT(const BSignal& s);
    friend BSignal InverseFFT(const BSignal& s);
};
//---------------------------------------------------------------------------
#endif
