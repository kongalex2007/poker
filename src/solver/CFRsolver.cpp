#include "CFRsolver.hpp"
#include "Node.hpp"
#include "GameState.hpp"
#include <vector>


class CFRSolver {
public:
    CFRSolver(const GameState& root_state);
    void run_iterations(int n);
    void traverse(Node* node, double reach_prob_p1, double reach_prob_p2);
    void update_strategy(Node* node);
    void compute_exploitability();
    

    inline void compute_strategy(const double* regret_sum, double* out_strategy, int n) {
        double sum_pos = 0.0;
        for (int i=0;i<n;++i) {
            out_strategy[i] = regret_sum[i] > 0 ? regret_sum[i] : 0.0;
            sum_pos += out_strategy[i];
        }
        if (sum_pos > 1e-12) {
            for (int i=0;i<n;++i) out_strategy[i] /= sum_pos;
        } else {
            double inv = 1.0 / n;
            for (int i=0;i<n;++i) out_strategy[i] = inv;
        }
    }

    







    private:

};

