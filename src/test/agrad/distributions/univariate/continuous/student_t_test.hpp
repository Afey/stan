// Arguments: Doubles, Doubles, Doubles, Doubles
#include <stan/prob/distributions/univariate/continuous/student_t.hpp>

#include <stan/math/functions/square.hpp>
#include <stan/math/functions/log1p.hpp>

using std::vector;
using std::numeric_limits;
using stan::agrad::var;

class AgradDistributionsStudentT : public AgradDistributionTest {
public:
  void valid_values(vector<vector<double> >& parameters,
                    vector<double>& log_prob) {
    vector<double> param(4);

    param[0] = 1.0;           // y
    param[1] = 1.0;           // nu
    param[2] = 0.0;           // mu
    param[3] = 1.0;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-1.837877); // expected log_prob

    param[0] = -3.0;          // y
    param[1] = 2.0;           // nu
    param[2] = 0.0;           // mu
    param[3] = 1.0;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-3.596843); // expected log_prob

    param[0] = 2.0;           // y
    param[1] = 1.0;           // nu
    param[2] = 0.0;           // mu
    param[3] = 2.0;           // sigma
    parameters.push_back(param);
    log_prob.push_back(-2.531024); // expected log_prob
  }
 
  void invalid_values(vector<size_t>& index,
                      vector<double>& value) {
    // y
   
    // nu
    index.push_back(1U);
    value.push_back(0.0);

    index.push_back(1U);
    value.push_back(-1.0);

    index.push_back(1U);
    value.push_back(-numeric_limits<double>::infinity());

    // mu

    // sigma
    index.push_back(3U);
    value.push_back(0.0);

    index.push_back(3U);
    value.push_back(-1.0);

    index.push_back(3U);
    value.push_back(-numeric_limits<double>::infinity());
  }

  double num_params() {
    return 4;
  }

  std::vector<double> lower_bounds() {
    std::vector<double> lb;
    lb.push_back(-numeric_limits<double>::infinity()); //y
    lb.push_back(1.0e-300); //nu
    lb.push_back(-numeric_limits<double>::infinity()); //mu
    lb.push_back(1.0e-300); //sigma

    return lb;
  }

  std::vector<std::vector<double> > lower_bound_vals() {
    std::vector<std::vector<double> > lb;
    std::vector<double> lb1;
    std::vector<double> lb2;
    std::vector<double> lb3;
    std::vector<double> lb4;
   
    lb1.push_back(-numeric_limits<double>::infinity()); //y for valid values 1
    lb1.push_back(-numeric_limits<double>::infinity()); //y for valid values 2
    lb1.push_back(-numeric_limits<double>::infinity()); //y for valid values 3
    lb2.push_back(-691.4686); //nu for valid values 1
    lb2.push_back(-692.5673); //nu for valid values 2
    lb2.push_back(-692.1618); //nu for valid values 3
    lb3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 1
    lb3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 2
    lb3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 3
    lb4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 1
    lb4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 2
    lb4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 3

    lb.push_back(lb1);
    lb.push_back(lb2);
    lb.push_back(lb3);
    lb.push_back(lb4);

    return lb;
  }

  std::vector<double> upper_bounds() {
    std::vector<double> ub;
    ub.push_back(numeric_limits<double>::infinity()); //y
    ub.push_back(numeric_limits<double>::infinity()); //nu
    ub.push_back(numeric_limits<double>::infinity()); //mu
    ub.push_back(numeric_limits<double>::infinity()); //sigma

    return ub;
  }

  std::vector<std::vector<double> > upper_bound_vals() {
    std::vector<std::vector<double> > ub;
    std::vector<double> ub1;
    std::vector<double> ub2;
    std::vector<double> ub3;
    std::vector<double> ub4;
   
    ub1.push_back(-numeric_limits<double>::infinity()); //y for valid values 1
    ub1.push_back(-numeric_limits<double>::infinity()); //y for valid values 2
    ub1.push_back(-numeric_limits<double>::infinity()); //y for valid values 3
    ub2.push_back(-numeric_limits<double>::infinity()); //nu for valid values 1
    ub2.push_back(-numeric_limits<double>::infinity()); //nu for valid values 2
    ub2.push_back(-numeric_limits<double>::infinity()); //nu for valid values 3
    ub3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 1
    ub3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 2
    ub3.push_back(-numeric_limits<double>::infinity()); //mu for valid values 3
    ub4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 1
    ub4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 2
    ub4.push_back(-numeric_limits<double>::infinity()); //sigma for valid values 3

    ub.push_back(ub1);
    ub.push_back(ub2);
    ub.push_back(ub3);
    ub.push_back(ub4);

    return ub;
  }

  template <class T_y, class T_dof, class T_loc, class T_scale,
      typename T4, typename T5, typename T6, 
      typename T7, typename T8, typename T9>
  typename stan::return_type<T_y, T_dof, T_loc, T_scale>::type 
  log_prob(const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma,
     const T4&, const T5&, const T6&, const T7&, const T8&, const T9&) {
    return stan::prob::student_t_log(y, nu, mu, sigma);
  }
  
  template <bool propto, 
      class T_y, class T_dof, class T_loc, class T_scale,
      typename T4, typename T5, typename T6, 
      typename T7, typename T8, typename T9>
  typename stan::return_type<T_y, T_dof, T_loc, T_scale>::type 
  log_prob(const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma,
     const T4&, const T5&, const T6&, const T7&, const T8&, const T9&) {
    return stan::prob::student_t_log<propto>(y, nu, mu, sigma);
  }
  
  
  template <class T_y, class T_dof, class T_loc, class T_scale,
      typename T4, typename T5, typename T6, 
      typename T7, typename T8, typename T9>
  var log_prob_function(const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma,
      const T4&, const T5&, const T6&, const T7&, const T8&, const T9&) {
    using std::log;
    using stan::math::square;
    using stan::math::log1p;
    using boost::math::lgamma;
    using stan::prob::include_summand;
    using stan::prob::NEG_LOG_SQRT_PI;
    
    var logp(0);
    if (include_summand<true,T_dof>::value)
      logp += lgamma( (nu + 1.0) / 2.0) - lgamma(nu / 2.0);
    if (include_summand<true>::value)
      logp += NEG_LOG_SQRT_PI;
    if (include_summand<true,T_dof>::value)
      logp -= 0.5 * log(nu);
    if (include_summand<true,T_scale>::value)
      logp -= log(sigma);
    if (include_summand<true,T_y,T_dof,T_loc,T_scale>::value)
      logp -= ((nu + 1.0) / 2.0) 
  * log1p( square(((y - mu) / sigma)) / nu);
    return logp;
  }
};

TEST(ProbDistributionsStudentTCDF,Values) {
    EXPECT_FLOAT_EQ(0.75, stan::prob::student_t_cdf(1.0,1.0,0.0,1.0));
    EXPECT_FLOAT_EQ(0.047732983, stan::prob::student_t_cdf(-3.0,2.0,0.0,1.0));
}
