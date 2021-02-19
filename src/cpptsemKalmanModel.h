#ifndef CPPTSEMKALMANMODEL_H
#define CPPTSEMKALMANMODEL_H

#include <RcppArmadillo.h>

// [[Rcpp :: depends ( RcppArmadillo )]]

// cpptsemKalmanModel class

class cpptsemKalmanModel{
  // inherits from cpptsemmodel
public:
  int sampleSize, Tpoints, nlatent, nmanifest;
  Rcpp::List discreteTimeParameterNames;
  arma::mat kalmanData, latentScores, predictedManifestValues;
  std::string name;
  Rcpp::List ctMatrixList;
  Rcpp::List discreteDRIFTUnique;
  Rcpp::List discreteTRAITUnique;
  Rcpp::List DRIFTHASHExponentialUnique;
  Rcpp::List discreteDIFFUSIONUnique;
  Rcpp::List discreteCINTUnique;
  Rcpp::DataFrame parameterTable;
  arma::mat DRIFTValues;
  arma::mat DIFFUSIONValues;
  arma::mat T0VARValues;
  arma::colvec T0MEANSValues;
  arma::mat TRAITVARValues;
  arma::mat MANIFESTVARValues;
  arma::mat LAMBDAValues;
  arma::colvec MANIFESTMEANSValues;
  bool hasDiscreteDRIFTUnique = false,
    hasDiscreteTRAITUnique = false,
    hasDRIFTHASHExponentialUnique = false,
    hasDiscreteDIFFUSIONUnique = false,
    hasDiscreteCINTUnique = false,
    computeWasCalled = false,
    stationaryT0VAR = false,
    stationaryT0MEANS = false;

  double m2LL;

  // constructor
  cpptsemKalmanModel(std::string mName,
                     Rcpp::List mCtMatrixList,
                     Rcpp::DataFrame mParameterTable,
                     bool mStationaryT0VAR,
                     bool mStationaryT0MEANS);

  // setter
  void setParameterValues(Rcpp::NumericVector mParameters, Rcpp::StringVector parameterLabels);
  void setDiscreteDRIFTUnique(Rcpp::List mDiscreteDRIFTUnique);
  void setDiscreteTRAITUnique(Rcpp::List mDiscreteTRAITUnique);
  void setDRIFTHASHExponentialUnique(Rcpp::List mDRIFTHASHExponentialUnique);
  void setDiscreteDIFFUSIONUnique(Rcpp::List mDiscreteDIFFUSIONUnique);
  void setDiscreteCINTUnique(Rcpp::List mDiscreteCINTUnique);

  void setKalmanData(Rcpp::List mKalmanData);
  void setDiscreteTimeParameterNames(Rcpp::List mDiscreteTimeParameterNames);
  void setKalmanMatrices(Rcpp::List mKalmanMatrices);

  // computation
  void computeAndFitKalman();
  Rcpp::NumericVector approxKalmanGradients(double epsilon = .000001);

  // getter
  Rcpp::NumericVector getParameterValues();

};

#endif
