#include <RcppArmadillo.h>
#include "computeRAMM2LL.h"
// [[Rcpp :: depends ( RcppArmadillo )]]

//' computeGroupM2LL
//' Computes the -2log likelihood in a RAM model for a  group of people with identical missing structure given the sample size, number of non-missing variables (nObservedVariables),
//' observedMeans within this sample, observedCov within this sample, filtered expectedMeans, and filtered expectedCovariance.
//' The implementation closely follows that of Driver, C. C., Oud, J. H. L., & Voelkle, M. C. (2017). Continuous Time Structural Equation Modelling With R Package ctsem. Journal of Statistical Software, 77(5), 1–36. https://doi.org/10.18637/jss.v077.i05
//'
//' @param sampleSize number of persons
//' @param nObservedVariables number of observed variables
//' @param observedMeans means of observed variables
//' @param observedCov observed covariance
//' @param expectedMeans expected means
//' @param expectedCovariance expected covariance
//' @returns double
//' @keywords internal
// [[Rcpp::export]]
double computeGroupM2LL(const int sampleSize,
                        const int nObservedVariables,
                        const arma::colvec& observedMeans,
                        const arma::mat& observedCov,
                        const arma::colvec& expectedMeans,
                        const arma::mat& expectedCovariance){
  double m2LL;
  double Nklog2pi = sampleSize*nObservedVariables*std::log(2*M_PI);
  double NlogDetExpCov = sampleSize*std::log(arma::det(expectedCovariance));
  double NtrSSigma = sampleSize*arma::trace(observedCov * arma::inv(expectedCovariance));
  arma::mat Ndist = sampleSize*arma::trans(observedMeans - expectedMeans)*arma::inv(expectedCovariance)*(observedMeans - expectedMeans);
  m2LL = Nklog2pi +
    NlogDetExpCov +
    NtrSSigma+
    Ndist(0,0); // note: dist is a 1x1 matrix; extraction is necessary for the data type to be compatible
  return(m2LL);
}
