#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>



int main() {
    const int N_membrane = 120;
    const int N_interior = 120;
    const double PI = 3.141592653589793;

    const double R_membrane = 1.0;
    const double R_interior_max = 0.95;

    const double random_step_max = 0.001;

    // Euler motion parameters
    const int N_steps = 1000000;
    const int output_every = 100000;
   

    std::vector<double> membraneX, membraneY, membraneZ;     // Vectors for membrane node positions
    std::vector<double> interiorX, interiorY, interiorZ;     // Vectors for interior node positions

    std::ofstream membraneFile("membrane.dat");
    std::ofstream interiorFile("interior.dat");

    // Random number generator for interior nodes
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> angleDist(0.0, 2.0 * PI);
    std::uniform_real_distribution<double> radiusDist(0.0, 1.0);
    std::uniform_real_distribution<double> randomLengthDist(0.0, random_step_max);

    // Create cell membrane
    for (int i = 0; i < N_membrane; i++) {
        double theta = 2.0 * PI * i / N_membrane;

        double x = R_membrane * std::cos(theta);
        double y = R_membrane * std::sin(theta);
        double z = 0.0;

        membraneX.push_back(x);
        membraneY.push_back(y);
        membraneZ.push_back(z);
    }
    membraneFile << "\n\n";

    // Create interior nodes
    for (int i = 0; i < N_interior; i++) {
        double theta = angleDist(gen);

        // Generate radius strictly inside the membrane
        double r = R_interior_max * std::sqrt(radiusDist(gen));

        double x = r * std::cos(theta);
        double y = r * std::sin(theta);
        double z = 0.0;

        interiorX.push_back(x);
        interiorY.push_back(y);
        interiorZ.push_back(z);
    }
    interiorFile << "\n\n";

    // Time stepping loop
    for (int step = 0; step < N_steps; step++) {
        for (int i = 0; i < N_membrane; i++) {
            double theta_random = angleDist(gen);
            double random_length = randomLengthDist(gen);

            double dx = random_length * std::cos(theta_random);
            double dy = random_length * std::sin(theta_random);
            double dz = 0;

            membraneX[i] += dx;
            membraneY[i] += dy;
            membraneZ[i] += dz;
        }

        for (int i = 0; i < N_interior; i++) {
            double theta_random = angleDist(gen);
            double random_length = randomLengthDist(gen);

            double dx = random_length * std::cos(theta_random);
            double dy = random_length * std::sin(theta_random);
            double dz = 0;

            interiorX[i] += dx;
            interiorY[i] += dy;
            interiorZ[i] += dz;
        }

        if (step % output_every == 0) {
            for (int i = 0; i < N_membrane; i++) {
                membraneFile << membraneX[i] << " "
                             << membraneY[i] << " "
                             << membraneZ[i] << "\n";
            }
            membraneFile << "\n\n";

            for (int i = 0; i < N_interior; i++) {
                interiorFile << interiorX[i] << " "
                             << interiorY[i] << " "
                             << interiorZ[i] << "\n";
            }
            interiorFile << "\n\n";
        }
    }
    membraneFile.close();
    interiorFile.close();

    std::cout << "Created membrane.dat and interior.dat\n";

    return 0;
}