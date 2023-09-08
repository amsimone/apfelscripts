#include <apfel/apfelxx.h>
#include <LHAPDF/LHAPDF.h>

int main()
{
  // Open LHAPDF set
  const std::vector<LHAPDF::PDF*> fv = LHAPDF::mkPDFs("CT18NNLO");
  
  // APFEL++ EvolutionSetup object
  apfel::EvolutionSetup es;

  // Evolution parameters
  es.Q0                = fv[0]->qMin();
  es.PerturbativeOrder = fv[0]->orderQCD();
  es.QQCDRef           = 91.1876;
  es.AlphaQCDRef       = fv[0]->alphasQ(es.QQCDRef);
  es.Thresholds        = {0, 0, 0, fv[0]->quarkThreshold(4), fv[0]->quarkThreshold(5)};
  es.Masses            = {0, 0, 0, fv[0]->quarkThreshold(4), fv[0]->quarkThreshold(5)};
  es.Qmin              = fv[0]->qMin();
  es.Qmax              = fv[0]->qMax();
  es.name              = "TestPDF";
  es.GridParameters    = {{200, 1e-9, 3}, {100, 1e-1, 3}, {100, 6e-1, 3}, {80, 8e-1, 3}};
  es.InSet.clear();

  // Input functions
  for (auto const& f : fv)
    es.InSet.push_back([=] (double const& x, double const& Q) -> std::map<int, double> { return apfel::PhysToQCDEv(f->xfxQ(x, Q)); });

  // Feed it to the initialisation class of APFEL++ and create a grid
  apfel::InitialiseEvolution evpdf{es, true};

  return 0;
}
