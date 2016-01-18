/// @copyright (c) 2011 CSIRO
/// Australia Telescope National Facility (ATNF)
/// Commonwealth Scientific and Industrial Research Organisation (CSIRO)
/// PO Box 76, Epping NSW 1710, Australia
/// atnf-enquiries@csiro.au
///
/// The ASKAP software distribution is free software: you can redistribute it
/// and/or modify it under the terms of the GNU General Public License as
/// published by the Free Software Foundation; either version 2 of the License,
/// or (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program; if not, write to the Free Software
/// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
///
/// @author Ben Humphreys <ben.humphreys@csiro.au>

#ifndef MULTISCALE_CUDA_H
#define MULTISCALE_CUDA_H

// System includes
#include <vector>
#include <cstddef>

// Cuda includes
#include <cuda_runtime_api.h>

struct Peak {
    float val;
    int pos;
    int scale;
    friend bool operator>(const Peak& a, const Peak& b) {return a.val>b.val;}
    friend bool operator<(const Peak& a, const Peak& b) {return a.val<b.val;}
};

class MultiScaleCuda {
    public:
        MultiScaleCuda(size_t psfSize, size_t n_scale_in, size_t residualSize);
        ~MultiScaleCuda();

        void deconvolve(const std::vector<float>& dirty,
                const size_t dirtyWidth,
                const std::vector<float>* psf,
                const size_t psfWidth,
                const std::vector<float>* cross,
                const size_t crossWidth,
                std::vector<float>& model,
                std::vector<float>* residual);

    private:

        void reportDevice(void);

        float* d_psf_all;
        float* d_residual_all;
        Peak*  d_peaks_all;     // temporary array for per-block peaks
        float* d_cross_all;
        float** d_psf;
        float** d_residual;
        float* d_model;
        Peak** d_peaks;
        float*** d_cross;
        size_t n_scale;
};

#endif
