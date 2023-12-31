/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itk_H5Cpp_h
#define itk_H5Cpp_h

/* Use the hdf5 library configured for ITK.  */
/* #undef ITK_USE_SYSTEM_HDF5 */
#ifdef ITK_USE_SYSTEM_HDF5
# include <H5Cpp.h>
#else
# include "itkhdf5/cpp/H5Cpp.h"
#endif

#endif
