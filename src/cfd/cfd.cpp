#include "cfd.h"

CFD::CFD(int w, int h, int d)
    : width(w), height(h), depth(d)
{
    data.resize((w+2)*(h+2)*(d+2));
    tmpDvData.resize((w+2)*(h+2)*(d+2));
    // TODO: zero edges
}

void CFD::iterate(double dt) {
    int stepY = (width+2)*(depth+2);
    int stepZ = (width+2);
    vec3 g = vec3(0.0, -9.81, 0.0);
    double viscosity = 0.0;
    double rho = 1.0;
    double rho_recip = 1.0 / rho;
    constexpr int stepX = 1;
    for(int y=1; y<height+1; ++y) {
        for(int z=1; z<depth+1; ++z) {
            for(int x=1; x<width+1; ++x) {
                int curIx = y * stepY + z * stepZ + x;
                //auto& curData = data[curIx];

                vec3 dv1(
                        data[curIx + stepX].velocity.X() - data[curIx].velocity.X(),
                        data[curIx + stepY].velocity.Y() - data[curIx].velocity.Y(),
                        data[curIx + stepZ].velocity.Z() - data[curIx].velocity.Z());
                vec3 dv0(
                        data[curIx].velocity.X() - data[curIx-stepX].velocity.X(),
                        data[curIx].velocity.Y() - data[curIx-stepY].velocity.Y(),
                        data[curIx].velocity.Z() - data[curIx-stepZ].velocity.Z());
                vec3 dv = (dv1 + dv0) * 0.5;
                vec3 d2v = (dv1 - dv0) * 0.5;
                vec3 convection = vec3::dot(dv, data[curIx].velocity) * rho;
                vec3 diffusion = d2v * viscosity;
                vec3 internal(0.0, 0.0, 0.0);

                vec3 acc = (diffusion - convection - internal + g) * rho_recip;
                tmpDvData[curIx] = acc;
            }
        }
    }
    for(int y=1; y<height+1; ++y) {
        for(int z=1; z<depth+1; ++z) {
            for(int x=1; x<width+1; ++x) {
                int curIx = y * stepY + z * stepZ + x;
                data[curIx].velocity += tmpDvData[curIx] * dt;
            }
        }
    }
}

std::vector<CFD::ElemState> CFD::getXYPlaneData(int z) {
    int stepY = (width+2)*(depth+2);
    int stepZ = (width+2);
    std::vector<CFD::ElemState> result;
    result.resize((width+2)*(height+2));
    for(int y=0;y<height+2; ++y) {
        for(int x=0;x<width+2; ++x) {
            int curIx = y * stepY + z * stepZ + x;
            int resultIx = x + (width+2) * y;
            result[resultIx] = data[curIx];
        }
    }
    return result;
}
