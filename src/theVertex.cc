#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillVertex(const edm::Event &iEvent){
  // Vertex
  //edm::Handle<VertexCollection> vertices;
  //iEvent.getByLabel(InputTag("offlinePrimaryVertices"), vertices);
  value_ve_n = vertices->size();
  value_ve_x = vertices->begin()->x();
  value_ve_y = vertices->begin()->y();
  value_ve_z = vertices->begin()->z();
  math::XYZPoint pv(vertices->begin()->position());
}
