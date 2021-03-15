void pscm(double b, double cl=0.95, double step=0.01){
  std::cout << "Expected background set to be          : " <<  b << " events.\n";
  std::cout << "Confidence level set to be             : " << cl << " \n";
  int i=1;
  while(ROOT::Math::poisson_cdf(int(b)+i,b) < cl ) i++;
  int b_max = int(b) + i;
  std::cout << "Poisson(x,b) quintile for CL           : " << b_max << "\n";
  double s_min = step;
  while(ROOT::Math::poisson_cdf_c(b_max,b_max + s_min) < cl ) s_min+=step;
  std::cout << "Minimal signal, which will be detected : " << s_min << "\n";
  std::cout << "                         ( Curie limit : " << 2.706+4.653*sqrt(b) << " )\n";
}
