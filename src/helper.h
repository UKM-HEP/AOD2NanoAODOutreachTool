#ifndef HELPER_H
#define HELPER_H

template <typename T>
void subtractInvisible(T g, reco::Candidate::LorentzVector& p4) {
  auto daughters = (*g).daughterRefVector();
  for (auto d = daughters.begin(); d != daughters.end(); d++) {
    const auto pdgId = (*d)->pdgId();
    if (std::abs(pdgId) == 12 || std::abs(pdgId) == 14 ||
        std::abs(pdgId) == 16 || std::abs(pdgId) == 18) {
      p4 = p4 - (*d)->p4();
    }
    subtractInvisible(*d, p4);
  }
}

template <typename T>
int findBestVisibleMatch(T& gens, reco::Candidate::LorentzVector& p4) {
  float minDeltaR = 999.0;
  int idx = -1;
  for (auto g = gens.begin(); g != gens.end(); g++) {
    auto tmp_p4 = g->p4();
    subtractInvisible(g, tmp_p4);
    const auto tmp = deltaR(tmp_p4, p4);
    if (tmp < minDeltaR) {
      minDeltaR = tmp;
      idx = g - gens.begin();
    }
  }
  return idx;
}

template <typename T>
int findBestMatch(T& gens, reco::Candidate::LorentzVector& p4) {
  float minDeltaR = 999.0;
  int idx = -1;
  for (auto g = gens.begin(); g != gens.end(); g++) {
    const auto tmp = deltaR(g->p4(), p4);
    if (tmp < minDeltaR) {
      minDeltaR = tmp;
      idx = g - gens.begin();
    }
  }
  return idx;
}

#endif
