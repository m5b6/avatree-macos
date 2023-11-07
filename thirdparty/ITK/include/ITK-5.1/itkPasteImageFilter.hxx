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
#ifndef itkPasteImageFilter_hxx
#define itkPasteImageFilter_hxx

#include "itkPasteImageFilter.h"
#include "itkObjectFactory.h"
#include "itkTotalProgressReporter.h"
#include "itkImageAlgorithm.h"

namespace itk
{

template <typename TInputImage, typename TSourceImage, typename TOutputImage>
PasteImageFilter<TInputImage, TSourceImage, TOutputImage>::PasteImageFilter()
{
  // #0 "FixedImage" required
  Self::SetPrimaryInputName("DestinationImage");

  // #2 "SourceImage" required
  Self::AddRequiredInputName("SourceImage");

  this->InPlaceOff();
  m_DestinationIndex.Fill(0);
  this->DynamicMultiThreadingOn();
  this->ThreaderUpdateProgressOff();
}


template <typename TInputImage, typename TSourceImage, typename TOutputImage>
void
PasteImageFilter<TInputImage, TSourceImage, TOutputImage>::GenerateInputRequestedRegion()
{
  // Call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // Get the pointers for the inputs and output
  InputImagePointer  destPtr = const_cast<InputImageType *>(this->GetInput());
  SourceImagePointer sourcePtr = const_cast<SourceImageType *>(this->GetSourceImage());
  OutputImagePointer outputPtr = this->GetOutput();

  if (!destPtr || !sourcePtr || !outputPtr)
  {
    return;
  }

  // Second input must include the SourceRegion
  sourcePtr->SetRequestedRegion(m_SourceRegion);

  // First input must match the output requested region
  destPtr->SetRequestedRegion(outputPtr->GetRequestedRegion());
}

template <typename TInputImage, typename TSourceImage, typename TOutputImage>
void
PasteImageFilter<TInputImage, TSourceImage, TOutputImage>::DynamicThreadedGenerateData(
  const OutputImageRegionType & outputRegionForThread)
{
  // Get the input and output pointers
  const InputImageType *  destPtr = this->GetInput();
  const SourceImageType * sourcePtr = this->GetSourceImage();
  OutputImageType *       outputPtr = this->GetOutput();

  TotalProgressReporter progress(this, outputPtr->GetRequestedRegion().GetNumberOfPixels());

  // What is the region on the destination image would be overwritten by the
  // source?
  // Do we need to use the source image at all for the region generated by this
  // thread?

  bool                  useSource;
  SourceImageRegionType sourceRegionInDestinationImage;
  SourceImageRegionType sourceRegionInDestinationImageCropped;
  sourceRegionInDestinationImage.SetIndex(m_DestinationIndex);
  sourceRegionInDestinationImage.SetSize(m_SourceRegion.GetSize());

  if (sourceRegionInDestinationImage.Crop(outputRegionForThread))
  {
    // Paste region is inside this thread
    useSource = true;
    sourceRegionInDestinationImageCropped = sourceRegionInDestinationImage;
  }
  else
  {
    // Paste region is outside this thread
    useSource = false;
  }

  // If the source image needs to be used to generate the output image, does the
  // destination image need to be used? i.e. will the source region completely
  // overlap the destination region for this thread?
  bool useOnlySource;
  if (useSource && (sourceRegionInDestinationImageCropped == outputRegionForThread))
  {
    // sourceRegionInDestinationImage completely overlaps the output
    // region for this thread, so we'll only copy data from the source
    useOnlySource = true;
  }
  else
  {
    // sourceRegionInDestinationImage only partially overlaps the
    // output region for this thread so we need to copy from both
    // inputs
    useOnlySource = false;
  }

  // If the source needs to be used, what part of the source needs to copied
  // by this thread?
  SourceImageRegionType sourceRegionInSourceImageCropped;
  if (useSource)
  {
    // What is the proposed shift from destination to source?
    Offset<InputImageDimension> originalOffsetFromDestinationToSource;
    originalOffsetFromDestinationToSource = m_SourceRegion.GetIndex() - m_DestinationIndex;

    // Transform the cropped index back into the source image
    InputImageIndexType sourceIndexInSourceImageCropped;
    sourceIndexInSourceImageCropped =
      sourceRegionInDestinationImageCropped.GetIndex() + originalOffsetFromDestinationToSource;

    // Set the values in the region
    sourceRegionInSourceImageCropped.SetIndex(sourceIndexInSourceImageCropped);
    sourceRegionInSourceImageCropped.SetSize(sourceRegionInDestinationImageCropped.GetSize());
  }


  // There are three cases that we need to consider:
  //
  // 1. Source region does not impact this thread, so copy data from
  //    from the destination image to the output
  //
  // 2. Source region completely overlaps the output region for this
  //    thread, so copy data from the source image to the output
  //
  // 3. Source region partially overlaps the output region for this
  //    thread, so copy data as needed from both the source and
  //    destination.
  //
  if (!useSource && !(this->GetInPlace() && this->CanRunInPlace()))
  {
    // Paste region is outside this thread, so just copy the destination
    // input to the output
    ImageAlgorithm::Copy(destPtr, outputPtr, outputRegionForThread, outputRegionForThread);
    progress.Completed(outputRegionForThread.GetNumberOfPixels());
  }
  else if (useOnlySource)
  {
    // Paste region completely overlaps the output region
    // for this thread, so copy data from the second input
    // to the output
    ImageAlgorithm::Copy(sourcePtr, outputPtr, sourceRegionInSourceImageCropped, outputRegionForThread);
    progress.Completed(outputRegionForThread.GetNumberOfPixels());
  }
  else
  {
    // Paste region partially overlaps the output region for the
    // thread, so we need copy data from both inputs as necessary. The
    // following code could be optimized. This case could be
    // decomposed further such the output is broken into a set of
    // regions where each region would get data from either the
    // destination or the source images (but not both). But for the
    // sake of simplicity and running under the assumption that the
    // source image is smaller than the destination image, we'll just
    // copy the destination to the output then overwrite the
    // appropriate output pixels with the source.

    if (!(this->GetInPlace() && this->CanRunInPlace()))
    {
      // Copy destination to output
      ImageAlgorithm::Copy(destPtr, outputPtr, outputRegionForThread, outputRegionForThread);

      progress.Completed(outputRegionForThread.GetNumberOfPixels() -
                         sourceRegionInDestinationImageCropped.GetNumberOfPixels());
    }

    // copy the cropped source region to output
    ImageAlgorithm::Copy(sourcePtr, outputPtr, sourceRegionInSourceImageCropped, sourceRegionInDestinationImageCropped);

    progress.Completed(sourceRegionInDestinationImageCropped.GetNumberOfPixels());
  }
}

template <typename TInputImage, typename TSourceImage, typename TOutputImage>
void
PasteImageFilter<TInputImage, TSourceImage, TOutputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "DestinationIndex: " << m_DestinationIndex << std::endl;
  os << indent << "SourceRegion: " << m_SourceRegion << std::endl;
}
} // end namespace itk

#endif