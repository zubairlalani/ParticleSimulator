#include <visualizer/ideal_gas_simulation.h>

using idealgas::visualizer::IdealGasSimulation;

void prepareSettings(IdealGasSimulation::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(IdealGasSimulation, ci::app::RendererGl, prepareSettings);
